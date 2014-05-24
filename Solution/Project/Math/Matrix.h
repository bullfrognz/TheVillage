//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Matrix.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_MATRIX_H__
#define __IGFEB11_IG500_MATRIX_H__


// Library Includes


// Local Includes
#include "Defines\DataTypes.h"


// Types


// Constants


// Prototypes


class CMatrix
{

	// Member Functions
public:


	 CMatrix();
	~CMatrix();


	void Identity();


	void Inverse(CMatrix& _rTarget)  const;


	float GetDeterminant() const;


    CMatrix& operator += (const CMatrix& _krMatrix);
    CMatrix& operator -= (const CMatrix& _krMatrix);
    CMatrix& operator *= (const CMatrix& _krMatrix);


	CMatrix operator + (const CMatrix& _krMatrix) const;
	CMatrix operator - (const CMatrix& _krMatrix) const;
	CMatrix operator * (const CMatrix& _krMatrix) const;


    bool operator == (const CMatrix& _krMatrix) const;
    bool operator != (const CMatrix& _krMatrix) const;


	// Inline Functions
	inline float GetValue(ushort _usRow, ushort _usColumn) const;


	inline void SetValue(ushort _usRow, ushort _usColumn, float _fValue);


protected:


private:


	// Member Variables
protected:


	float m_fMatrix[4][4];


private:


};


#include "Matrix.inl"


#endif //__IGFEB11_IG500_MATRIX_H__