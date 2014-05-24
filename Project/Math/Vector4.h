//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Vector4.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Vector4_H__
#define __Vector4_H__


// Library Includes


// Local Includes


// Types


// Constants


// Prototypes
class CVector3;


class CVector4
{

	// Member Functions
public:


	 CVector4();
	 CVector4(const CVector3& _krVector);
	 CVector4(float _fX, float _fY, float _fZ, float _fW);
	~CVector4();


	// Inline Functions
	inline void AddX(float _fX);
	inline void AddY(float _fY);
	inline void AddZ(float _fZ);
	inline void AddW(float _fW);
	inline void Add(float _fX, float _fY, float _fZ, float _fW);


	inline void SetX(float _fX);
	inline void SetY(float _fY);
	inline void SetZ(float _fZ);
	inline void SetW(float _fW);
	inline void Set(float _fX, float _fY, float _fZ, float _fW);


	inline float GetX() const;
	inline float GetY() const;
	inline float GetZ() const;
	inline float GetW() const;


protected:


private:


	void Deinitialise();


	CVector4(const CVector4& _krVector4);
	CVector4& operator = (const CVector4& _krVector4);


	// Member Variables
protected:


private:


	float m_fX;
	float m_fY;
	float m_fZ;
	float m_fW;


};


#include "Vector4.inl"


#endif //__Vector4_H__