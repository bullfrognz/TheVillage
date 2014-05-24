//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   Skybox.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <assert.h>


// Local Includes
#include "Defines\Macros.h"
#include "Framework\Effect.h"
#include "Framework\Renderer.h"
#include "Framework\Camera.h"
#include "Library\Object.h"


// This Include
#include "Skybox.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* Skybox constructors
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSkybox::CSkybox()
: m_pSkyboxObj(0)
, m_pEffect(0)
, m_fDiffuse(1.0f, 1.0f, 1.0f)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Skybox deconstructor
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSkybox::~CSkybox()
{
	Deinitialise();
}





bool
CSkybox::Initialise(IRenderer& _rRenderer, EType _eType)
{
	FW_VALIDATE(InitialiseEffect(_rRenderer))
	FW_VALIDATE(InitialiseObject(_rRenderer))


	return (true);
}





void
CSkybox::Process(float _fDeltatick, CCamera& _rPlayerCamera)
{
	m_pSkyboxObj->SetPosition(_rPlayerCamera.GetPosition());


	m_pSkyboxObj->AddRotationY(0.01f * _fDeltatick);


	m_pEffect->SetVariable("g_v4Diffuse", m_fDiffuse);
}





bool
CSkybox::Draw(IRenderer& _rRenderer, CCamera& _rPlayerCamera)
{
	FW_VALIDATE(_rRenderer.SetActiveEffect(m_pEffect, "DefaultTechnique"))


	FW_VALIDATE(m_pEffect->SetTransformations(m_pSkyboxObj->GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()))


	FW_VALIDATE(m_pSkyboxObj->Draw(_rRenderer, *m_pEffect))


	return (true);
}




void
CSkybox::SetBrightness(float _fRatio)
{
	assert(_fRatio >= 0.0f);
	assert(_fRatio <= 1.0f);


	if (_fRatio  < 0.2f)
	{
		_fRatio = 0.2f;
	}


	m_fDiffuse = CVector3(1.0f, 1.0f, 1.0f) * _fRatio;


	if (_fRatio < 1.0f)
	{
		//m_fDiffuse = CVector3(1.0f, 0.8f, 0.0f) * _fRatio;
	}
	else
	{
		//m_fDiffuse.Set(1.0f, 1.0f, 1.0f);
	}
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





bool
CSkybox::InitialiseEffect(IRenderer& _rRenderer)
{
	IEffect::TDesc tEffectDesc;
	tEffectDesc.kcpEffectFile = "Skybox.fx";
	tEffectDesc.bTransformationHelper = true;
	tEffectDesc.bTextureHelper = true;


	// Default technique
	IEffect::TTechnqiue tTechnique;
	tTechnique.kcpName = "DefaultTechnique";


	IEffect::TInput tPosition;
	tPosition.kcpName = "POSITION";
	tPosition.eVariableType = IEffect::VARIABLETYPE_FLOAT3;
	tTechnique.aInputLayout.push_back(tPosition);


	IEffect::TInput tNormal;
	tNormal.kcpName = "NORMAL";
	tNormal.eVariableType = IEffect::VARIABLETYPE_FLOAT3;
	tTechnique.aInputLayout.push_back(tNormal);


	IEffect::TInput tTexCoords1;
	tTexCoords1.kcpName = "TEXCOORD_ONE";
	tTexCoords1.eVariableType = IEffect::VARIABLETYPE_FLOAT2;
	tTechnique.aInputLayout.push_back(tTexCoords1);


	tEffectDesc.aTechniques.push_back(tTechnique);


	// Variables
	tEffectDesc.aVariableNames.push_back("g_v4Diffuse");
	

	FW_VALIDATE(_rRenderer.InstanceEffect(tEffectDesc, m_pEffect));


	return (true);
}





bool
CSkybox::InitialiseObject(IRenderer& _rRenderer)
{
	std::vector<CModel::EInputType> aInputLayout;
	aInputLayout.push_back(CModel::INPUTTYPE_POSITION);
	aInputLayout.push_back(CModel::INPUTTYPE_NORMAL);
	aInputLayout.push_back(CModel::INPUTTYPE_TEXTCOORDS1);

	
	m_pSkyboxObj = new CObject();
	FW_VALIDATE(m_pSkyboxObj->Initialise(_rRenderer, "Assets/Models/Skybox/Skybox.obj", aInputLayout))
	m_pSkyboxObj->SetScale(20.0f, 20.0f, 20.0f);
	

	return (true);
}





void
CSkybox::Deinitialise()
{
	FW_DELETE(m_pSkyboxObj)
	FW_DELETE(m_pEffect)
}