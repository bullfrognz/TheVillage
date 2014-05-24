//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   Game.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Define Includes
#include "Defines\Macros.h"
#include "Defines\Math.h"


// Utility Includes
#include "Utilities\MathUtilities.h"
#include "Utilities\Messenger.h"


// Math Includes
#include "Math\WorldMatrix.h"
#include "Math\ViewMatrix.h"
#include "Math\ProjMatrix.h"


// Library Includes
#include "Library\FPCamera.h"


// Framework Includes
#include "Framework\Renderer.h"
#include "Framework\Text.h"
#include "Framework\Keyboard.h"


// Scene Includes
#include "Scene\Game\Terrain.h"
#include "Scene\Game\Skybox.h"
#include "Scene\Game\DayNightCycle.h"
#include "Scene\Game\Village.h"


// Library Includes


// This Include
#include "Game.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CGame constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CGame::CGame()
: m_pPlayerCamera(0)
, m_pDebugCamera(0)
, m_pSkybox(0)
, m_pTerrain(0)
, m_pDayNightCycle(0)
, m_pVillage(0)
, m_bDrawShadows(true)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CGame deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CGame::~CGame()
{
	Deinitialise();
}





bool
CGame::Initialise(IRenderer& _rRenderer, void* _pData)
{
	FW_VALIDATE(InitialiseCameras(_rRenderer))
	FW_VALIDATE(InitialiseTerrain(_rRenderer))
	FW_VALIDATE(InitialiseAssets(_rRenderer))
	FW_VALIDATE(IntiialiseInfoText(_rRenderer))
	FW_VALIDATE(InitialiseLights())


	Messenger::RegisterObserver(KEY_UP_B, this);
	Messenger::RegisterObserver(KEY_UP_N, this);
	Messenger::RegisterObserver(KEY_UP_M, this);
	Messenger::RegisterObserver(KEY_UP_ESCAPE, this);


	char cBuffer[512];
	sprintf_s(cBuffer, "Look Around: Mouse\nMovement: W, S, A, D\nDay-Night Cycle: E, Q\nDraw Distance: M (Inc), N (Dec)\nQuit: Escape");
	m_pInfo->SetText(cBuffer);
	m_pInfo->SetColour(1.0f, 1.0f, 1.0f);


	return (true);
}





void
CGame::Process(IRenderer& _rRenderer, float _fDeltaTick)
{
	ProcessCameras(_fDeltaTick);
	ProcessSkybox(_fDeltaTick);
	UpdateLights();


	m_pTerrain->UpdatePosition(m_pPlayerCamera->GetPosition());
	m_pTerrain->Process(_rRenderer, _fDeltaTick);
	m_pDayNightCycle->Process(_fDeltaTick, *m_pPlayerCamera);
	m_pVillage->Process(_fDeltaTick, *m_pTerrain);


	const CVector3& kvrPosition = m_pPlayerCamera->GetPosition();
}





void
CGame::Draw(IRenderer& _rRenderer)
{
	bool bWithoutStates = false;


	if (m_pDayNightCycle->GetLightRatio() < 0.64f)
	{
		bWithoutStates = true;
	}

	
	if (!bWithoutStates && 
		m_bDrawShadows)
	{
		DrawAmbient(_rRenderer);
		DrawShadows(_rRenderer);
	}


	DrawLit(_rRenderer, bWithoutStates);
	DrawUnlit(_rRenderer);


	m_pInfo->Draw();
}





void
CGame::NotifyMessage(uint _uiSubject, void* _pDispatcher)
{
	switch (_uiSubject)
	{
	case KEY_UP_B:
		m_bDrawShadows = (m_bDrawShadows) ? false : true;
		break;

	case KEY_UP_M:
		m_pTerrain->IncrementViewRange();
		break;

	case KEY_UP_N:
		m_pTerrain->DerementViewRange();
		break;

	case KEY_UP_ESCAPE:
		CApplication::GetInstance().Quit();
		break;
	}
}





/********************************
            Protected
*********************************/





void
CGame::DrawUnlit(IRenderer& _rRenderer)
{
	_rRenderer.RestoreDefaultStates(IRenderer::STATE_BLEND | IRenderer::STATE_DEPTHSTENCIL | IRenderer::STATE_RASTERIZER);


	// [Render Unlit]
	m_pSkybox->Draw(_rRenderer, *m_pPlayerCamera);
	m_pDayNightCycle->Draw(_rRenderer, *m_pPlayerCamera);
	//m_pTerrain->DrawBoundingBoxes(_rRenderer, *m_pPlayerCamera);
	m_pVillage->DrawUnlit(_rRenderer, *m_pPlayerCamera);
	//m_pInfo->Draw();
}





void
CGame::DrawAmbient(IRenderer& _rRenderer)
{
	CColour kvLightDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
	CColour kvLightAmbient(0.3f, 0.3f, 0.3f, 1.0f);
	CColour kvLightSpecular(0.0f, 0.0f, 0.0f, 1.0f);


	// [Render Ambient]
	m_pLights[0]->SetDiffue(0.0f, 0.0f, 0.0f, 1.0f);
	m_pLights[0]->SetAmbient(kvLightAmbient);
	m_pLights[0]->SetSpecular(0.0f, 0.0f, 0.0f, 1.0f);


	m_pTerrain->DrawAmbient(_rRenderer, *m_pPlayerCamera, m_pLights);
	m_pVillage->DrawAmbient(_rRenderer, *m_pPlayerCamera, m_pLights);
}





void
CGame::DrawShadows(IRenderer& _rRenderer)
{
	// [Render Shadows]
	_rRenderer.EnableShadowDrawStates();
	m_pVillage->DrawShadows(_rRenderer, *m_pPlayerCamera, m_pLights);
}





void
CGame::DrawLit(IRenderer& _rRenderer, bool _bWithoutStates)
{
	CColour kvLightDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
	CColour kvLightAmbient(0.3f, 0.3f, 0.3f, 1.0f);
	CColour kvLightSpecular(0.0f, 0.0f, 0.0f, 1.0f);


	// [Render Lit]
	if (!_bWithoutStates &&
		m_bDrawShadows)
	{
		_rRenderer.EnableLitDrawStates();
		m_pLights[0]->SetAmbient(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		m_pLights[0]->SetAmbient(kvLightAmbient);
	}


	m_pLights[0]->SetDiffue(kvLightDiffuse);
	m_pLights[0]->SetSpecular(kvLightSpecular);


	m_pTerrain->DrawLit(_rRenderer, *m_pPlayerCamera, m_pLights);
	m_pVillage->DrawLit(_rRenderer, *m_pPlayerCamera, m_pLights);
}





void
CGame::ProcessCameras(float _fDeltaTick)
{
	m_pPlayerCamera->Process(_fDeltaTick);


	// Force player camera above terrain
	float kfMeshHeight = 0.0f;
	bool bHeightFound = m_pTerrain->GetMeshHeight(m_pPlayerCamera->GetPosition(), kfMeshHeight);
	kfMeshHeight += 3.5f;


	if (bHeightFound &&
		m_pPlayerCamera->GetPosition().GetY() < kfMeshHeight)
	{
		m_pPlayerCamera->SetPositionY(kfMeshHeight);
	}

	
	//m_pDebugCamera->Process(_fDeltaTick);
}





void
CGame::ProcessSkybox(float _fDeltaTick)
{
	m_pSkybox->Process(_fDeltaTick, *m_pPlayerCamera);
	m_pSkybox->SetBrightness(m_pDayNightCycle->GetLightRatio());
}





void
CGame::UpdateLights()
{
	// Set new light position & direction
	m_pLights[0]->SetPosition(m_pDayNightCycle->GetSunPosition());
	m_pLights[0]->SetDirection(m_pDayNightCycle->GetSunDirection());
}





/********************************
            Private
*********************************/





bool
CGame::InitialiseCameras(IRenderer& _rRenderer)
{
	const uint kuiBufferWidth  = _rRenderer.GetBufferWidth();
	const uint kuiBufferHeight = _rRenderer.GetBufferHeight();


	// Player camera
	m_pPlayerCamera = new CFPCamera();
	FW_VALIDATE(m_pPlayerCamera->Initialise(kuiBufferWidth, kuiBufferHeight));
	m_pPlayerCamera->SetPosition(CVector3(-393.0f, 553.0f, -143.0f));


	// Debug camera
	m_pDebugCamera = new CFPCamera();
	FW_VALIDATE(m_pDebugCamera->Initialise(kuiBufferWidth, kuiBufferHeight));
	m_pDebugCamera->SetPosition(CVector3(0.0f, 1040.0f, -50.0f));


	return (true);
}





bool
CGame::InitialiseTerrain(IRenderer& _rRenderer)
{
	CTerrain::TFiles tFiles;
	memset(&tFiles, 0, sizeof(CTerrain::TFiles));


	tFiles.cpHeightmap = "Assets/Terrain/Heightmap.raw";
	tFiles.uiHeightmapWidth  = 4096;
	tFiles.uiHeightmapHeight = 4096;


	tFiles.cpTextures[0] = "Assets/Terrain/Grass.jpg";
	tFiles.cpTextures[1] = "Assets/Terrain/Cliff.jpg";
	tFiles.cpTextures[2] = "Assets/Terrain/Snow.jpg";
	tFiles.cpTextures[3] = "Assets/Terrain/Pebbles.jpg";
	tFiles.cpAlphamap[0] = "Assets/Terrain/GrassAlphamap.raw";
	tFiles.cpAlphamap[1] = "Assets/Terrain/CliffAlphamap.raw";
	tFiles.cpAlphamap[2] = "Assets/Terrain/SnowAlphamap.raw";
	tFiles.cpAlphamap[3] = "Assets/Terrain/PebblesAlphamap.raw";
	

	m_pTerrain = new CTerrain();
	FW_VALIDATE(m_pTerrain->Initialise(_rRenderer, tFiles))


	return (true);
}





bool
CGame::InitialiseAssets(IRenderer& _rRenderer)
{
	// Skybox
	m_pSkybox = new CSkybox();
	FW_VALIDATE(m_pSkybox->Initialise(_rRenderer, CSkybox::TYPE_CLOUDLY))


	// Day night cycle
	m_pDayNightCycle = new CDayNightCycle();
	FW_VALIDATE(m_pDayNightCycle->Initialise(_rRenderer, *m_pPlayerCamera))


	// Village
	m_pVillage = new CVillage();
	FW_VALIDATE(m_pVillage->Initialise(_rRenderer))


	return (true);
}





bool
CGame::IntiialiseInfoText(IRenderer& _rRenderer)
{
	IText::TDesc tTextDesc;
	tTextDesc.bItalic = false;
	tTextDesc.eFamily = IText::FAMILY_ARIAL;
	tTextDesc.eQuality = IText::QUALITY_LOW;
	tTextDesc.uiSize = 18;
	tTextDesc.uiWeight = 1;


	FW_VALIDATE(_rRenderer.InstanceFont(tTextDesc, m_pInfo))


	m_pInfo->SetPosition(10, 40);


	return (true);
}





bool
CGame::InitialiseLights()
{
	// Sun
	CLight* pSun = new CLight();
	pSun->SetType(LIGHTTYPE_DIRECTIONAL);
	pSun->SetDirection(0.0f, -1.0f, 0.5f);
	pSun->SetDiffue(0.8f, 0.8f, 0.8f, 1.0f);
	pSun->SetSpecular(0.0f, 0.0f, 0.0f, 1.0f);
	pSun->SetAmbient(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights.push_back(pSun);


	// Lightbulb
	/*
	CLight* pLightbulb = new CLight();
	pLightbulb->SetType(LIGHTTYPE_POINT);
	pLightbulb->SetAttenuation(0.0f, 0.215f, 0.0f);
	pLightbulb->SetRange(20);
	pLightbulb->SetDiffue(0.0f, 0.0f, 1.0f,1.0f);
	pLightbulb->SetAmbient(1.0f, 1.0f, 1.0f, 1.0f);
	pLightbulb->SetSpecular(0.0f, 0.0f, 1.0f, 1.0f);
	m_pLights.push_back(pLightbulb);


	// Torch
	CLight* pTorch = new CLight();
	pTorch->SetType(LIGHTTYPE_SPOT);
	pTorch->SetDiffue(0.5f, 0.5f, 0.5f, 1.0f);
	pTorch->SetRange(20);
	pTorch->SetAttenuation(0.0f, 0.125f, 0.0f);
	pTorch->SetSpecular(0.0f, 0.0f, 1.0f, 1.0f);
	pTorch->SetPhi(0.6981f);
	pTorch->SetTheta(0.349f);
	pTorch->SetFalloff(1.0f);
	pTorch->SetPosition(0.0f, 4.0f, 0.0f);
	pTorch->SetDirection(0.0f, -1.0f, 0.0f);
	m_pLights.push_back(pTorch);
	*/


	return (true);
}





void
CGame::Deinitialise()
{
	FW_DELETE(m_pTerrain);
	FW_DELETE(m_pPlayerCamera)
	FW_DELETE(m_pDebugCamera)
	FW_DELETE(m_pSkybox)
	FW_DELETE(m_pDayNightCycle)
	FW_DELETE(m_pVillage)
	FW_DELETE(m_pInfo)
	FW_DELETEVECTOR(CLight*, m_pLights);


	Messenger::UnregisterObserver(KEY_UP_B, this);
	Messenger::UnregisterObserver(KEY_UP_N, this);
	Messenger::UnregisterObserver(KEY_UP_M, this);
	Messenger::UnregisterObserver(KEY_UP_ESCAPE, this);
}