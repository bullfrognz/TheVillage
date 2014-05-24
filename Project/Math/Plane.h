//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Plane.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Plane_H__
#define __Plane_H__


// Library Includes


// Local Includes


// Types


// Prototypes


class CPlane
{

	// Member Functions
public:


	 CPlane();
	~CPlane();


	// Inline Functions
	inline void SetA(float _fA);
	inline void SetB(float _fB);
	inline void SetC(float _fC);
	inline void SetD(float _fD);
	inline void Set(float _fA, float _fB, float _fC, float _fD);


	inline float GetA() const;
	inline float GetB() const;
	inline float GetC() const;
	inline float GetD() const;


protected:


private:


	// Member Variables
protected:


private:


	float m_fA;
	float m_fB;
	float m_fC;
	float m_fD;


};


#include "Plane.inl"


#endif //__Plane_H__