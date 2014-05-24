//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   Building.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Framework\Renderer.h"
#include "Framework\Effect.h"
#include "Framework\Camera.h"
#include "Library\Object.h"
#include "Defines\Macros.h"


// This Include
#include "Building.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* Building constructors
*
*---------------------------------------------------------------------------------------------------------------------------*/

CBuilding::CBuilding()
: m_pEffect(0)
, m_pStructure(0)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Building deconstructor
*
*---------------------------------------------------------------------------------------------------------------------------*/

CBuilding::~CBuilding()
{
	Deinitialise();
}





bool
CBuilding::Initialise(IRenderer& _rRenderer, const char* _kcpModelFile)
{
	FW_VALIDATE(InitialiseModel(_rRenderer, _kcpModelFile));
	FW_VALIDATE(InitialiseEffectFile(_rRenderer));


	return (true);
}





bool
CBuilding::DrawShadow(IRenderer& _rRenderer, CCamera& _rActiveCamera, std::vector<CLight*>& _rActiveLights)
{
	FW_VALIDATE(_rRenderer.SetActiveEffect(m_pEffect, "RenderShadow"));


	// Set Transformations
	m_pEffect->SetTransformations(CEntity::GetWorld(), _rActiveCamera.GetView(), _rActiveCamera.GetProjection());


	// Set lights
	m_pEffect->SetLights(&(*_rActiveLights.begin()), _rActiveLights.size(), _rActiveCamera.GetPosition());


	// Draw
	m_pStructure->Draw(_rRenderer, *m_pEffect);


	return (true);
}





bool
CBuilding::Draw(IRenderer& _rRenderer, CCamera& _rActiveCamera, std::vector<CLight*>& _rActiveLights)
{
	FW_VALIDATE(_rRenderer.SetActiveEffect(m_pEffect, "DefaultTechnique"));


	// Set Transformations
	m_pEffect->SetTransformations(CEntity::GetWorld(), _rActiveCamera.GetView(), _rActiveCamera.GetProjection());


	// Set lights
	m_pEffect->SetLights(&(*_rActiveLights.begin()), _rActiveLights.size(), _rActiveCamera.GetPosition());


	// Draw
	m_pStructure->Draw(_rRenderer, *m_pEffect);


	return (true);
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





bool
CBuilding::InitialiseModel(IRenderer& _rRenderer, const char* _kcpModelFile)
{
	std::vector<CModel::EInputType> aInputLayout;
	aInputLayout.push_back(CModel::INPUTTYPE_POSITION);
	aInputLayout.push_back(CModel::INPUTTYPE_NORMAL);
	aInputLayout.push_back(CModel::INPUTTYPE_TEXTCOORDS1);


	m_pStructure = new CObject();
	FW_VALIDATE(m_pStructure->Initialise(_rRenderer, _kcpModelFile, aInputLayout));


	return (true);
}





bool
CBuilding::InitialiseEffectFile(IRenderer& _rRenderer)
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





void
CBuilding::Deinitialise()
{
	FW_DELETE(m_pStructure);
	FW_DELETE(m_pEffect);
}