//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   Village.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Framework\Renderer.h"
#include "Framework\Camera.h"
#include "Library\Object.h"
#include "Scene\Game\Windmill.h"
#include "Scene\Game\Terrain.h"
#include "Scene\Game\Water.h"
#include "Defines\Macros.h"
#include "Math\WorldMatrix.h"
#include "Utilities\MathUtilities.h"


// This Include
#include "Village.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* Village constructors
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVillage::CVillage()
: m_pEffect(0)
, m_pBarn(0)
, m_pPeir(0)
, m_pShop(0)
, m_pTableBasic(0)
, m_pWell(0)
, m_pWoodenCart2(0)
, m_pHouse(0)
, m_pCastleGate(0)
, m_pWindmill(0)
, m_pCathedral(0)
, m_pWater(0)
, m_bPositionsSet(false)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Village deconstructor
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVillage::~CVillage()
{
	Deinitialise();
}





bool
CVillage::Initialise(IRenderer& _rRenderer)
{
	FW_VALIDATE(InitialiseEffect(_rRenderer))
	FW_VALIDATE(InitialiseObjects(_rRenderer))


	return (true);
}





void
CVillage::Process(float _fDeltaTick, CTerrain& _rTerrain)
{
	if (!m_bPositionsSet)
	{
		SetupPositions(_rTerrain);
	}


	m_pWater->Process(_fDeltaTick);
	m_pWindmill->Process(_fDeltaTick);
}





bool
CVillage::DrawUnlit(IRenderer& _rRenderer, CCamera& _rPlayerCamera)
{
	FW_VALIDATE(m_pWater->Draw(_rRenderer, _rPlayerCamera));


	return (true);
}





bool
CVillage::DrawAmbient(IRenderer& _rRenderer, CCamera& _rPlayerCamera, std::vector<CLight*>& _rActiveLights)
{
	// Activate effect & technique
	FW_VALIDATE(_rRenderer.SetActiveEffect(m_pEffect, "DefaultTechnique"));


	return (Draw(_rRenderer, _rPlayerCamera, _rActiveLights));
}





bool
CVillage::DrawShadows(IRenderer& _rRenderer, CCamera& _rPlayerCamera, std::vector<CLight*>& _rActiveLights)
{
	// Activate effect & technique
	FW_VALIDATE(_rRenderer.SetActiveEffect(m_pEffect, "RenderShadow"));


	return (Draw(_rRenderer, _rPlayerCamera, _rActiveLights));
}





bool
CVillage::DrawLit(IRenderer& _rRenderer, CCamera& _rPlayerCamera, std::vector<CLight*>& _rActiveLights)
{
	// Activate effect & technique
	FW_VALIDATE(_rRenderer.SetActiveEffect(m_pEffect, "DefaultTechnique"));


	return (Draw(_rRenderer, _rPlayerCamera, _rActiveLights));
}





/********************************
            Protected
*********************************/





bool
CVillage::Draw(IRenderer& _rRenderer, CCamera& _rPlayerCamera, std::vector<CLight*>& _rActiveLights)
{
	// Set lights
	FW_VALIDATE(m_pEffect->SetLights(_rActiveLights.data(), _rActiveLights.size(), _rPlayerCamera.GetPosition()))


	// Draw objects
	FW_VALIDATE(m_pEffect->SetTransformations(m_pBarn->GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()))
	m_pBarn->Draw(_rRenderer, *m_pEffect);


	FW_VALIDATE(m_pEffect->SetTransformations(m_pPeir->GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()))
	m_pPeir->Draw(_rRenderer, *m_pEffect);


	//FW_VALIDATE(m_pEffect->SetTransformations(m_pShop->GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()))
	//m_pShop->Draw(_rRenderer, *m_pEffect);


	//FW_VALIDATE(m_pEffect->SetTransformations(m_pTableBasic->GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()))
	//m_pTableBasic->Draw(_rRenderer, *m_pEffect);


	FW_VALIDATE(m_pEffect->SetTransformations(m_pWell->GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()))
	m_pWell->Draw(_rRenderer, *m_pEffect);


	FW_VALIDATE(m_pEffect->SetTransformations(m_pWoodenCart2->GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()))
	m_pWoodenCart2->Draw(_rRenderer, *m_pEffect);


	FW_VALIDATE(m_pEffect->SetTransformations(m_pHouse->GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()))
	m_pHouse->Draw(_rRenderer, *m_pEffect);


	FW_VALIDATE(m_pEffect->SetTransformations(m_pCastleGate->GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()))
	m_pCastleGate->Draw(_rRenderer, *m_pEffect);


	FW_VALIDATE(m_pEffect->SetTransformations(m_pCathedral->GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()))
	m_pCathedral->Draw(_rRenderer, *m_pEffect);


	FW_VALIDATE(m_pWindmill->Draw(_rRenderer, _rPlayerCamera, *m_pEffect));


	return (true);
}





void
CVillage::SetupPositions(CTerrain& _rTerrain)
{
	float kfHeight = 0.0f;
	bool bHeightFound = false;


	// Barn
	if (_rTerrain.GetMeshHeight(m_pBarn->GetPosition(), kfHeight))
	{
		m_pBarn->SetPositionY(kfHeight);
	}


	// House
	if (_rTerrain.GetMeshHeight(m_pHouse->GetPosition(), kfHeight))
	{
		m_pHouse->SetPositionY(kfHeight);
	}


	// Shop
	if (_rTerrain.GetMeshHeight(m_pShop->GetPosition(), kfHeight))
	{
		m_pShop->SetPositionY(kfHeight);
		m_bPositionsSet = true;
	}

	
	// Castle Gate
	if (_rTerrain.GetMeshHeight(m_pCastleGate->GetPosition(), kfHeight))
	{
		m_pCastleGate->SetPositionY(kfHeight + 32.2f);
	}


	// Well
	if (_rTerrain.GetMeshHeight(m_pWell->GetPosition(), kfHeight))
	{
		m_pWell->SetPositionY(kfHeight);
	}


	// Wooden Cart 2
	if (_rTerrain.GetMeshHeight(m_pWoodenCart2->GetPosition(), kfHeight))
	{
		m_pWoodenCart2->SetPositionY(kfHeight);
	}


	// Pair
	if (_rTerrain.GetMeshHeight(m_pPeir->GetPosition(), kfHeight))
	{
		m_pPeir->SetPositionY(kfHeight + 35.0f);
	}


	// Cathedral
	if (_rTerrain.GetMeshHeight(m_pCathedral->GetPosition(), kfHeight))
	{
		m_pCathedral->SetPositionY(kfHeight);
	}


	// Windmill
	if (_rTerrain.GetMeshHeight(m_pWindmill->GetPosition(), kfHeight))
	{
		m_pWindmill->SetPositionY(kfHeight);
	}


	// Water
	if (_rTerrain.GetMeshHeight(m_pWater->GetPosition(), kfHeight))
	{
		m_pWater->SetPositionY(kfHeight + 32.0f);
	}
}





/********************************
            Private
*********************************/





bool
CVillage::InitialiseEffect(IRenderer& _rRenderer)
{
	IEffect::TDesc tEffectDesc;
	tEffectDesc.kcpEffectFile = "Building.fx";
	tEffectDesc.bTransformationHelper = true;
	tEffectDesc.bLightHelper = true;
	tEffectDesc.bTextureHelper = true;


	// Default technique
	IEffect::TTechnqiue tDefaultTechnique;
	tDefaultTechnique.kcpName = "DefaultTechnique";


	IEffect::TInput tPosition;
	tPosition.kcpName = "POSITION";
	tPosition.eVariableType = IEffect::VARIABLETYPE_FLOAT3;
	tDefaultTechnique.aInputLayout.push_back(tPosition);


	IEffect::TInput tNormal;
	tNormal.kcpName = "NORMAL";
	tNormal.eVariableType = IEffect::VARIABLETYPE_FLOAT3;
	tDefaultTechnique.aInputLayout.push_back(tNormal);


	IEffect::TInput tTexCoords1;
	tTexCoords1.kcpName = "TEXCOORD_ONE";
	tTexCoords1.eVariableType = IEffect::VARIABLETYPE_FLOAT2;
	tDefaultTechnique.aInputLayout.push_back(tTexCoords1);


	// Shadow technique
	IEffect::TTechnqiue tShadowTechnique;
	tShadowTechnique.kcpName = "RenderShadow";
	tShadowTechnique.aInputLayout = tDefaultTechnique.aInputLayout;


	tEffectDesc.aTechniques.push_back(tDefaultTechnique);
	tEffectDesc.aTechniques.push_back(tShadowTechnique);


	FW_VALIDATE(_rRenderer.InstanceEffect(tEffectDesc, m_pEffect));


	return (true);
}





bool
CVillage::InitialiseObjects(IRenderer& _rRenderer)
{
	std::vector<CModel::EInputType> aInputLayout;
	aInputLayout.push_back(CModel::INPUTTYPE_POSITION);
	aInputLayout.push_back(CModel::INPUTTYPE_NORMAL);
	aInputLayout.push_back(CModel::INPUTTYPE_TEXTCOORDS1);


	m_pBarn = new CObject();
	FW_VALIDATE(m_pBarn->Initialise(_rRenderer, "Assets/Models/Barn/Barn.obj", aInputLayout));
	m_pBarn->SetPosition(CVector3(-464.0f, 0.0f, 90));
	m_pBarn->SetScale(31, 31, 31);
	m_pBarn->SetRotationY(MathUtilities::DegreesToRadians(-20));


	m_pPeir = new CObject();
	FW_VALIDATE(m_pPeir->Initialise(_rRenderer, "Assets/Models/Pier/Pier.obj", aInputLayout));
	m_pPeir->SetRotationY(MathUtilities::DegreesToRadians(182));
	m_pPeir->SetPosition(CVector3(-447.1f, 0.0f, -196.7f));
	m_pPeir->SetScale(20, 20, 20);


	m_pShop = new CObject();
	FW_VALIDATE(m_pShop->Initialise(_rRenderer, "Assets/Models/Shop/Shop.obj", aInputLayout));
	m_pShop->SetRotationY(MathUtilities::DegreesToRadians(110));
	m_pShop->SetPosition(CVector3(-514.0f, 0.0f, 22.6f));


	//m_pTableBasic = new CObject();
	//FW_VALIDATE(m_pTableBasic->Initialise(_rRenderer, "Assets/Models/Table Basic/TableBasic.obj", aInputLayout));


	m_pWell = new CObject();
	FW_VALIDATE(m_pWell->Initialise(_rRenderer, "Assets/Models/Well/Well.obj", aInputLayout));
	m_pWell->SetPosition(CVector3(-450.0f, 0.0f, -10.0f));
	m_pWell->SetScale(0.13f, 0.13f, 0.13f);


	m_pWoodenCart2 = new CObject();
	FW_VALIDATE(m_pWoodenCart2->Initialise(_rRenderer, "Assets/Models/WoodenCart2/WoodenCart2.obj", aInputLayout));
	m_pWoodenCart2->SetPosition(CVector3(-488.5f, 0.0f, -60.5f));
	m_pWoodenCart2->SetScale(2.4f, 2.4f, 2.4f);
	m_pWoodenCart2->SetRotationY(MathUtilities::DegreesToRadians(250));

	
	m_pHouse = new CObject();
	FW_VALIDATE(m_pHouse->Initialise(_rRenderer, "Assets/Models/House/House.obj", aInputLayout));
	m_pHouse->SetRotationY(MathUtilities::DegreesToRadians(-115));
	m_pHouse->SetPosition(CVector3(-504.0f, 0.0f, -30));
	m_pHouse->SetScale(0.7f, 0.7f, 0.7f);


	m_pCastleGate = new CObject();
	FW_VALIDATE(m_pCastleGate->Initialise(_rRenderer, "Assets/Models/Castle Gate/CastleGate.obj", aInputLayout));
	m_pCastleGate->SetRotationY(MathUtilities::DegreesToRadians(-30));
	m_pCastleGate->SetPosition(CVector3(-377.4f, 0.0f, -179.2f));
	m_pCastleGate->SetScale(12, 12, 12);


	m_pCathedral = new CObject();
	FW_VALIDATE(m_pCathedral->Initialise(_rRenderer, "Assets/Models/Cathedral/Cathedral.obj", aInputLayout));
	m_pCathedral->SetRotationY(MathUtilities::DegreesToRadians(-50));
	m_pCathedral->SetPosition(CVector3(-382.4f, 0.0f, -80.7f));
	m_pCathedral->SetScale(20, 20, 20);


	m_pWindmill = new CWindmill();
	FW_VALIDATE(m_pWindmill->Initialise(_rRenderer));
	m_pWindmill->SetPosition(-420.0f, 0, 28.4f);


	m_pWater = new CWater();
	FW_VALIDATE(m_pWater->Initialise(_rRenderer, 13, 20));
	m_pWater->SetPosition(CVector3(-376, 0.0f, -181));
	m_pWater->SetRotationY(MathUtilities::DegreesToRadians(40));


	return (true);
}





void
CVillage::Deinitialise()
{
	FW_DELETE(m_pEffect)
	FW_DELETE(m_pBarn)
	FW_DELETE(m_pPeir)
	FW_DELETE(m_pShop)
	FW_DELETE(m_pTableBasic)
	FW_DELETE(m_pWell)
	FW_DELETE(m_pWoodenCart2)
	FW_DELETE(m_pHouse)
	FW_DELETE(m_pCastleGate)
	FW_DELETE(m_pCathedral);
	FW_DELETE(m_pWater);
	FW_DELETE(m_pWindmill)
}