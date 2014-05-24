//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Light.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Light_H__
#define __Light_H__


// Library Includes


// Local Includes
#include "Math\Vector3.h"
#include "Math\Colour.h"


// Types
enum ELightType
{
	INVALID_LIGHTTYPE,

	LIGHTTYPE_DIRECTIONAL,
	LIGHTTYPE_POINT,
	LIGHTTYPE_SPOT,

	MAX_LIGHTTYPE
};


// Prototypes


class CLight
{

	// Member Functions
public:


	 CLight();
	~CLight();


	// Inline Functions
	inline void SetType(ELightType _eType);
	inline void SetPosition(float _fX, float _fY, float _fZ);
	inline void SetDirection(float _fX, float _fY, float _fZ);
	inline void SetDiffue(float _fRed, float _fGreen, float _fBlue, float _fAlpha);
	inline void SetAmbient(float _fRed, float _fGreen, float _fBlue, float _fAlpha);
	inline void SetSpecular(float _fRed, float _fGreen, float _fBlue, float _fAlpha);
	inline void SetAttenuation(float _f0, float _f1, float _f2);
	inline void SetAttenuation0(float _fValue);
	inline void SetAttenuation1(float _fValue);
	inline void SetAttenuation2(float _fValue);
	inline void SetRange(float _fValue);
	inline void SetTheta(float _fValue);
	inline void SetPhi(float _fValue);
	inline void SetFalloff(float _fValue);
	inline void SetPosition(const CVector3& _kvrPosition);
	inline void SetDirection(const CVector3& _kvrDirection);
	inline void SetDiffue(const CColour& _kvrDiffuse);
	inline void SetAmbient(const CColour& _kvrAmbient);
	inline void SetSpecular(const CColour& _kvrSpecular);


protected:


private:


	void Deinitialise();


	CLight(const CLight& _krLight);
	CLight& operator = (const CLight& _krLight);


	// Member Variables
protected:


private:


	CVector3	m_vPosition;
	float		m_fPadding1;

	CVector3	m_vDirection;
	float		m_fPadding2;

	CColour		m_vDiffuse;
	CColour		m_vAmbient;
	CColour		m_vSpecular;

	float		m_fAttenuation0;
	float		m_fAttenuation1;
	float		m_fAttenuation2;

	float		m_fRange;
	float		m_fTheta;
	float		m_fPhi;
	float		m_fFalloff;

	ELightType	m_eType;


};


#include "Light.inl"


#endif //__Light_H__