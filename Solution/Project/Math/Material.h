//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Material.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Material_H__
#define __Material_H__


// Library Includes


// Local Includes
#include "Math\Colour.h"


// Types


// Prototypes


class CMaterial
{

	// Member Functions
public:


	 CMaterial();
	~CMaterial();


	// Inline Functions
	inline void SetDiffuseR(float _fR);
	inline void SetDiffuseG(float _fG);
	inline void SetDiffuseB(float _fB);
	inline void SetDiffuseA(float _fA);
	inline void SetDiffuse(float _fR, float _fG, float _fB, float _fA);

	inline void SetAmbientR(float _fR);
	inline void SetAmbientG(float _fG);
	inline void SetAmbientB(float _fB);
	inline void SetAmbientA(float _fA);
	inline void SetAmbient(float _fR, float _fG, float _fB, float _fA);

	inline void SetSpecularR(float _fR);
	inline void SetSpecularG(float _fG);
	inline void SetSpecularB(float _fB);
	inline void SetSpecularA(float _fA);
	inline void SetSpecular(float _fR, float _fG, float _fB, float _fA);

	inline void SetEmissiveR(float _fR);
	inline void SetEmissiveG(float _fG);
	inline void SetEmissiveB(float _fB);
	inline void SetEmissiveA(float _fA);
	inline void SetEmissive(float _fR, float _fG, float _fB, float _fA);

	inline void SetSpecularPower(float _fPower);



	inline const CColour& GetDiffuse() const;
	inline const CColour& GetAmbient() const;
	inline const CColour& GetSpecular() const;
	inline const CColour& GetEmissive() const;
	inline float GetSpecularPower() const;


protected:


private:


	// Member Variables
protected:


private:


	CColour m_Diffuse;
	CColour m_Ambient;
	CColour m_Specular;
	CColour m_Emissive;


	float m_fSpecularPower;


};


#include "Material.inl"


#endif //__Material_H__