//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   Vector2.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __BASECRAFT_VECTOR2_H__
#define __BASECRAFT_VECTOR2_H__


// Library Includes


// Local Includes
#include "Defines\DataTypes.h"


// Types


// Constants


// Prototypes
struct D3DXVECTOR2;


class CVector2
{

	// Member Functions
public:


	 CVector2();
	 CVector2(float _fX, float _fY);
	 CVector2(const CVector2& _krRight);
	~CVector2();


	float Magnitude() const;
	float MagnitudeSquare() const;


	float Distance(const CVector2& _kvrTarget) const;
	float DistanceSquare(const CVector2& _kvrTarget) const;


	void Normalise();


	// Operator Overloads
    const CVector2& operator += (const CVector2& _krRight);
	const CVector2& operator -= (const CVector2& _krRight);
    const CVector2& operator *= (float _fValue);
    const CVector2& operator /= (float _fValue);
	
    CVector2 operator + (const CVector2& _krRight) const;
    CVector2 operator - (const CVector2& _krRight) const;
    CVector2 operator * (float _fValue) const;
    CVector2 operator / (float _fValue) const;

    bool operator == (const CVector2& _krRight) const;
    bool operator != (const CVector2& _krRight) const;


	// Inline Functions
	inline void SetX(float _fX);
	inline void SetY(float _fY);
	inline void Set(float _fX, float _fY);

	inline float GetX() const;
	inline float GetY() const;

	inline bool IsZero() const;


protected:


private:


	// Member Variables
protected:


private:


	float m_fX;
	float m_fY;


};


#include "Vector2.inl"


#endif //__BASECRAFT_VECTOR2_H__