//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   ProjMatrix.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __ProjMatrix_H__
#define __ProjMatrix_H__


// Library Includes


// Local Includes
#include "Math\Matrix.h"


// Types


// Constants


// Prototypes
class CViewMatrix;
class CPlane;


class CProjMatrix : public CMatrix
{

	// Member Types
public:


	enum EFrustumPlane
	{
		INVALID_FRUSTUMPLANE = -1,

		FRUSTUMPLANE_LEFT,
		FRUSTUMPLANE_RIGHT,	
		FRUSTUMPLANE_TOP,
		FRUSTUMPLANE_BOTTOM,
		FRUSTUMPLANE_NEAR,
		FRUSTUMPLANE_FAR,

		MAX_FRUSTUMPLANE
	};


	// Member Functions
public:


	 CProjMatrix();
	~CProjMatrix();


	void SetPerspectiveFovLH(float _fFoV, float _fAspectRatio, float _fMin, float _fMax);
	void SetOrthFovRH();


	void GenerateFrustumPlane(const CViewMatrix& _kxrView, EFrustumPlane _eFrustumPlane, CPlane& _rPlane);


	// Inline Functions


protected:


private:


	// Member Variables
protected:


private:


};


#endif //__ProjMatrix_H__