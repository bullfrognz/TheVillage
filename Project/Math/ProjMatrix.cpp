//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   ProjMatrix.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <D3DX10.h>
#include <assert.h>


// Local Includes
#include "Math\ViewMatrix.h"
#include "Math\Plane.h"


// This Include
#include "ProjMatrix.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CProjMatrix constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CProjMatrix::CProjMatrix()
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CProjMatrix deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CProjMatrix::~CProjMatrix()
{
	// Empty
}





void
CProjMatrix::SetPerspectiveFovLH(float _fFoV, float _fAspectRatio, float _fMin, float _fMax)
{
	D3DXMatrixPerspectiveFovLH(reinterpret_cast<D3DXMATRIX*>(this), _fFoV, _fAspectRatio, _fMin, _fMax);
}




void
CProjMatrix::GenerateFrustumPlane(const CViewMatrix& _kxrView, EFrustumPlane _eFrustumPlane, CPlane& _rPlane)
{
    D3DXMATRIX mtxViewProjection;
    D3DXMatrixMultiply(&mtxViewProjection, reinterpret_cast<const D3DXMATRIX*>(&_kxrView), reinterpret_cast<const D3DXMATRIX*>(this));


	if (_eFrustumPlane == FRUSTUMPLANE_LEFT)
	{
		// Left plane
		_rPlane.SetA( mtxViewProjection._14 + mtxViewProjection._11 );
		_rPlane.SetB( mtxViewProjection._24 + mtxViewProjection._21 );
		_rPlane.SetC( mtxViewProjection._34 + mtxViewProjection._31 );
		_rPlane.SetD( mtxViewProjection._44 + mtxViewProjection._41 );
	}
	else if (_eFrustumPlane == FRUSTUMPLANE_RIGHT)
	{
		// Right plane
		_rPlane.SetA( mtxViewProjection._14 - mtxViewProjection._11 );
		_rPlane.SetB( mtxViewProjection._24 - mtxViewProjection._21 );
		_rPlane.SetC( mtxViewProjection._34 - mtxViewProjection._31 );
		_rPlane.SetD( mtxViewProjection._44 - mtxViewProjection._41 );
	}
	else if (_eFrustumPlane == FRUSTUMPLANE_TOP)
	{
		// Top plane
		_rPlane.SetA( mtxViewProjection._14 - mtxViewProjection._12 );
		_rPlane.SetB( mtxViewProjection._24 - mtxViewProjection._22 );
		_rPlane.SetC( mtxViewProjection._34 - mtxViewProjection._32 );
		_rPlane.SetD( mtxViewProjection._44 - mtxViewProjection._42 );
	}
	else if (_eFrustumPlane == FRUSTUMPLANE_BOTTOM)
	{
		// Bottom plane
		_rPlane.SetA( mtxViewProjection._14 + mtxViewProjection._12 );
		_rPlane.SetB( mtxViewProjection._24 + mtxViewProjection._22 );
		_rPlane.SetC( mtxViewProjection._34 + mtxViewProjection._32 );
		_rPlane.SetD( mtxViewProjection._44 + mtxViewProjection._42 );
	}
	else if (_eFrustumPlane == FRUSTUMPLANE_NEAR)
	{
		// Near plane
		_rPlane.SetA( mtxViewProjection._13 );
		_rPlane.SetB( mtxViewProjection._23 );
		_rPlane.SetC( mtxViewProjection._33 );
		_rPlane.SetD( mtxViewProjection._43 );
	}
	else if (_eFrustumPlane == FRUSTUMPLANE_FAR)
	{
		// Far plane
		_rPlane.SetA( mtxViewProjection._14 - mtxViewProjection._13 );
		_rPlane.SetB( mtxViewProjection._24 - mtxViewProjection._23 );
		_rPlane.SetC( mtxViewProjection._34 - mtxViewProjection._33 );
		_rPlane.SetD( mtxViewProjection._44 - mtxViewProjection._43 );
	}
	else
	{
		// Unknown frustum plane
		assert(false);
	}


	D3DXPlaneNormalize(reinterpret_cast<D3DXPLANE*>(&_rPlane), reinterpret_cast<const D3DXPLANE*>(&_rPlane));
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/