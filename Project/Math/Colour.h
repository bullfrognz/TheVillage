//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Colour.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Colour_H__
#define __Colour_H__


// Library Includes


// Local Includes


// Types


// Constants


// Prototypes
class CVector3;


class CColour
{

	// Member Functions
public:


	 CColour();
	 CColour(float _fRed, float _fGreen, float _fBlue, float _fOpacity);
	~CColour();


	// Inline Functions
	inline void AddRed(float _fRed);
	inline void AddGreen(float _fGreen);
	inline void AddBlue(float _fBlue);
	inline void AddOpacity(float _fOpacity);
	inline void Add(float _fRed, float _fGreen, float _fBlue, float _fOpacity);


	inline void SetRed(float _fRed);
	inline void SetGreen(float _fGreen);
	inline void SetBlue(float _fBlue);
	inline void SetOpacity(float _fOpacity);
	inline void Set(float _fRed, float _fGreen, float _fBlue, float _fOpacity);


	inline float GetRed() const;
	inline float GetGreen() const;
	inline float GetBlue() const;
	inline float GetOpacity() const;


protected:


private:


	// Member Variables
protected:


private:


	float m_fRed;
	float m_fGreen;
	float m_fBlue;
	float m_fOpacity;


};


#include "Colour.inl"


#endif //__Colour_H__