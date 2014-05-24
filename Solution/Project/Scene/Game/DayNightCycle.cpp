//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   DayNightCycle.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Utilities\Messenger.h"
#include "Framework\Renderer.h"
#include "Framework\Effect.h"
#include "Framework\Camera.h"
#include "Framework\Light.h"
#include "Framework\Keyboard.h"
#include "Library\Object.h"
#include "Defines\Macros.h"
#include "Math\WorldMatrix.h"
#include "Math\ProjMatrix.h"
#include "Math\ViewMatrix.h"
#include "Utilities\MathUtilities.h"


// This Include
#include "DayNightCycle.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* DayNightCycle constructors
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDayNightCycle::CDayNightCycle()
: m_pSunMoon(0)
, m_pSunLight(0)
, m_pEffect(0)
, m_kfSecondsInDay(40.0f)
, m_fCurrentTime(0)
, m_fMoonSunTranslation(500.0f)
, m_bCycleForward(false)
, m_bCycleBackwards(false)
{
	m_fCurrentTime = m_kfSecondsInDay - (m_kfSecondsInDay / 5);
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* DayNightCycle deconstructor
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDayNightCycle::~CDayNightCycle()
{
	Deinitialise();
}





bool
CDayNightCycle::Initialise(IRenderer& _rRenderer, CCamera& _rPlayerCamera)
{
	std::vector<CModel::EInputType> aInputLayout;
	aInputLayout.push_back(CModel::INPUTTYPE_POSITION);
	aInputLayout.push_back(CModel::INPUTTYPE_NORMAL);
	aInputLayout.push_back(CModel::INPUTTYPE_TEXTCOORDS1);


	m_pSunMoon = new CObject();
	FW_VALIDATE(m_pSunMoon->Initialise(_rRenderer, "Assets/Models/SunMoon/SunMoon.obj", aInputLayout));


	FW_VALIDATE(InitialiseEffect(_rRenderer));


	FW_VALIDATE(Messenger::RegisterObserver(KEY_UP_Q, this));
	FW_VALIDATE(Messenger::RegisterObserver(KEY_UP_E, this));
	FW_VALIDATE(Messenger::RegisterObserver(KEY_DWN_Q, this));
	FW_VALIDATE(Messenger::RegisterObserver(KEY_DWN_E, this));


	// First update
	UpdateTime(_rPlayerCamera);


	return (true);
}





void
CDayNightCycle::Process(float _fDeltatick, CCamera& _rPlayerCamera)
{
	bool bProcess = true;


	if (m_bCycleForward && !m_bCycleBackwards)
	{
		m_fCurrentTime += _fDeltatick;
	}
	else if (!m_bCycleForward && m_bCycleBackwards)
	{
		m_fCurrentTime -= _fDeltatick;
	}
	else
	{
		bProcess = false;
	}


	if (bProcess)
	{
		UpdateTime(_rPlayerCamera);
	}
}





bool
CDayNightCycle::Draw(IRenderer& _rRenderer, CCamera& _rPlayerCamera)
{
	_rRenderer.SetActiveEffect(m_pEffect, "DefaultTechnique");


	m_pEffect->SetTransformations(m_pSunMoon->GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection());


	m_pSunMoon->Draw(_rRenderer, *m_pEffect);


	return (true);
}





CVector3
CDayNightCycle::GetSunPosition()
{
	CVector3 vOrienationY;
	m_pSunMoon->GetWorld().GetOrientationY(vOrienationY);





	vOrienationY.Normalise();
	vOrienationY *= 10000.0f;


	return (vOrienationY);
}




CVector3
CDayNightCycle::GetSunDirection()
{
	CVector3 vOrienationY;
	m_pSunMoon->GetWorld().GetOrientationY(vOrienationY);
	vOrienationY.Normalise();


	return (vOrienationY *= -1);
}




float
CDayNightCycle::GetLightRatio()
{
	float fLightRatio = 1.0f;


	float fTime = m_fCurrentTime;


	float fQuaterTime = m_kfSecondsInDay / 4;


	float fEveningStart  = fQuaterTime / 1.5f;
	float fEveningEnd    = fQuaterTime + fQuaterTime / 2;
	float fEveningLength = fEveningEnd - fEveningStart;


	float fDawnStart  = (fQuaterTime * 3) - fQuaterTime / 3;
	float fDawnEnd    = fDawnStart + fQuaterTime / 2;
	float fDawnLength = fDawnEnd - fDawnStart;


	// If in day time
	if (fTime < fEveningStart ||
		fTime > fDawnEnd)
	{
		fLightRatio = 1.0f;
	}


	// If in evening
	else if (fTime > fEveningStart &&
			 fTime < fEveningEnd)
	{
		fLightRatio = 1.0f - ((fTime - fEveningStart) / fEveningLength);
	}


	// If in dawn
	else if (fTime > fDawnStart &&
			 fTime < fDawnEnd)
	{
		fLightRatio = ((fTime - fDawnStart) / fDawnLength);
	}

	// else night
	else
	{
		fLightRatio = 0.0f;
	}


	return (fLightRatio);
}





/********************************
            Protected
*********************************/





void 
CDayNightCycle::UpdateTime(CCamera& _rPlayerCamera)
{
	if (m_fCurrentTime > m_kfSecondsInDay)
	{
		m_fCurrentTime = 0.0f;
	}
	else if (m_fCurrentTime < 0.0f)
	{
		m_fCurrentTime = m_kfSecondsInDay;
	}


	float fSunRotation = MathUtilities::DegreesToRadians(360) * (m_fCurrentTime / m_kfSecondsInDay);


	m_pSunMoon->SetRotationZ(fSunRotation);//MathUtilities::DegreesToRadians(45)
	m_pSunMoon->SetPosition(_rPlayerCamera.GetPosition());
}





/********************************
            Private
*********************************/





bool
CDayNightCycle::InitialiseEffect(IRenderer& _rRenderer)
{
	IEffect::TDesc tEffectDesc;
	tEffectDesc.kcpEffectFile = "DayNightCycle.fx";
	tEffectDesc.bTransformationHelper = true;
	tEffectDesc.bTextureHelper = true;


	// Default technique
	IEffect::TTechnqiue tTechnique;
	tTechnique.kcpName = "DefaultTechnique";


	// Input layout
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


	FW_VALIDATE(_rRenderer.InstanceEffect(tEffectDesc, m_pEffect));


	return (true);
}





void
CDayNightCycle::Deinitialise()
{
	FW_DELETE(m_pSunMoon);
	FW_DELETE(m_pSunLight);
	FW_DELETE(m_pEffect);


	Messenger::UnregisterObserver(KEY_UP_Q, this);
	Messenger::UnregisterObserver(KEY_UP_E, this);
	Messenger::UnregisterObserver(KEY_DWN_Q, this);
	Messenger::UnregisterObserver(KEY_DWN_E, this);
}




void
CDayNightCycle::NotifyMessage(uint _uiSubject, void* _pDispatcher)
{
	switch (_uiSubject)
	{
	case KEY_UP_Q:
		m_bCycleBackwards = false;
		break;

	case KEY_UP_E:
		m_bCycleForward = false;
		break;

	case KEY_DWN_Q:
		m_bCycleBackwards = true;
		break;

	case KEY_DWN_E:
		m_bCycleForward = true;
		break;
	}
}