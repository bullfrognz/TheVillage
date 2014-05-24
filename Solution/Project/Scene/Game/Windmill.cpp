//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   Windmill.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Library\Object.h"
#include "Defines\Macros.h"
#include "Utilities\MathUtilities.h"
#include "Framework\Camera.h"


// This Include
#include "Windmill.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* Windmill constructors
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWindmill::CWindmill()
: m_pBase(0)
, m_pBlade(0)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Windmill deconstructor
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWindmill::~CWindmill()
{
	Deinitialise();
}





bool
CWindmill::Initialise(IRenderer& _rRenderer)
{
	std::vector<CModel::EInputType> aInputLayout;
	aInputLayout.push_back(CModel::INPUTTYPE_POSITION);
	aInputLayout.push_back(CModel::INPUTTYPE_NORMAL);
	aInputLayout.push_back(CModel::INPUTTYPE_TEXTCOORDS1);


	m_pBase = new CObject();
	m_pBase->Initialise(_rRenderer, "Assets/Models/Windmill/WindmilBase.obj", aInputLayout);
	m_pBase->SetRotationY(MathUtilities::DegreesToRadians(90));
	m_pBase->SetScale(2.0f, 2.0f, 2.0f);


	m_pBlade = new CObject();
	m_pBlade->Initialise(_rRenderer, "Assets/Models/Windmill/WindmilBlade.obj", aInputLayout);
	//m_pBlade->SetRotationY(MathUtilities::DegreesToRadians(90));
	m_pBlade->SetPosition(CVector3(0.0f, 12.0f, -2.9f));


	return (true);
}





void
CWindmill::Process(float _fDeltatick)
{
	m_pBlade->AddRotationZ(1.2f * _fDeltatick);
	m_pBase->AddRotationY(0.4f * _fDeltatick);
}





bool
CWindmill::Draw(IRenderer& _rRenderer, CCamera& _rPlayerCamera, IEffect& _rEffect)
{
	FW_VALIDATE(_rEffect.SetTransformations(m_pBase->GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()));
	FW_VALIDATE(m_pBase->Draw(_rRenderer, _rEffect));


	CVector3 vPositionOffset;
	CVector3 vRotationOffset;
	CVector3 vScale;
	m_pBase->GetPosition(vPositionOffset);
	m_pBase->GetRotation(vRotationOffset);
	m_pBase->GetScale(vScale);


	CWorldMatrix xBladeWorld = m_pBlade->GetWorld();
	xBladeWorld *= m_pBase->GetWorld();

	/*
	CWorldMatrix xParentRotation;
	xParentRotation.SetOrientation(vRotationOffset.GetX(),
									vRotationOffset.GetZ(),
									vRotationOffset.GetY());
	xBladeWorld *= xParentRotation;
	*/

	FW_VALIDATE(_rEffect.SetTransformations(xBladeWorld, _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()));
	FW_VALIDATE(m_pBlade->Draw(_rRenderer, _rEffect));


	return (true);
}





void
CWindmill::SetPosition(float _fX, float _fY, float _fZ)
{
	m_pBase->SetPosition(CVector3(_fX, _fY, _fZ));
}





void
CWindmill::SetPosition(const CVector3& _kvrPosition)
{
	m_pBase->SetPosition(_kvrPosition);
}





void 
CWindmill::SetPositionY(float _fY)
{
	m_pBase->SetPositionY(_fY);
}





const CVector3&
CWindmill::GetPosition()
{
	return (m_pBase->GetPosition());
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





void
CWindmill::Deinitialise()
{
	FW_DELETE(m_pBase);
	FW_DELETE(m_pBlade);
}