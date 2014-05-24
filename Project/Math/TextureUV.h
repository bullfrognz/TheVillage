//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   TextureUV.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __TextureUV_H__
#define __TextureUV_H__


// Library Includes


// Local Includes


// Types


// Prototypes


class CTextureUV
{

	// Member Functions
public:


	 CTextureUV();
	~CTextureUV();


	// Inline Functions
	inline void SetU(float _fU);
	inline void SetV(float _fV);


	inline float GetU() const;
	inline float GetV() const;


protected:


private:


	// Member Variables
protected:


private:


	float m_fU;
	float m_fV;


};


#include "TextureUV.inl"


#endif //__TextureUV_H__