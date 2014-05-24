//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   Vector3.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Vector3_H__
#define __Vector3_H__


// Library Includes


// Local Includes
#include "Defines\DataTypes.h"


// Types


// Constants


// Prototypes


class CVector3
{

	// Member Functions
public:


	 CVector3();
	 CVector3(const CVector3& _krRight);
	 CVector3(float _X, float _Y, float _Z);
	~CVector3();


	float Magnitude() const;
	float MagnitudeSquare() const;


	float Distance(const CVector3& _kvrTarget) const;
	float DistanceSquare(const CVector3& _kvrTarget) const;


	float Dot(const CVector3& _krVector) const;
	float DotAngle(const CVector3& _krVector) const;


	void Cross(const CVector3& _krRight, CVector3& _rResult) const;
	CVector3 Cross(const CVector3& _kvrRight) const;


	void Normalise();
	void Normalise(CVector3& _rResult) const;
	CVector3 Normalise() const;


	bool IsZero();


	// Operator Overloads
    const CVector3& operator += (const CVector3& _krRight);
	const CVector3& operator -= (const CVector3& _krRight);
    const CVector3& operator *= (float _fValue);
    const CVector3& operator /= (float _fValue);
	
    CVector3 operator + (const CVector3& _krRight) const;
    CVector3 operator - (const CVector3& _krRight) const;
    CVector3 operator * (float _fValue) const;
    CVector3 operator / (float _fValue) const;

    bool operator == (const CVector3& _krRight) const;
    bool operator != (const CVector3& _krRight) const;


	// Inline Functions
	inline void AddX(float _fX);
	inline void AddY(float _fY);
	inline void AddZ(float _fZ);
	inline void Add(float _fX, float _fY, float _fZ);


	inline void SetX(float _fX);
	inline void SetY(float _fY);
	inline void SetZ(float _fZ);
	inline void Set(float _fX, float _fY, float _fZ);


	inline float GetX() const;
	inline float GetY() const;
	inline float GetZ() const;


protected:


private:


	// Member Variables
protected:


private:


	float m_fX;
	float m_fY;
	float m_fZ;


};


#include "Vector3.inl"


#endif //__Vector3_H__