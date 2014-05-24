//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   ViewMatrix.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <D3DX10.h>


// Local Includes


// This Include
#include "ViewMatrix.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





CViewMatrix::CViewMatrix()
{
	CMatrix::Identity();
}





CViewMatrix::~CViewMatrix()
{
	Deinitialise();
}





void
CViewMatrix::LookAtLH(const CVector3& _krPosition, const CVector3& _krTarget)
{
	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);


	D3DXMatrixLookAtLH(	reinterpret_cast<D3DXMATRIX*>(this),
						reinterpret_cast<const D3DXVECTOR3*>(&_krPosition),
						reinterpret_cast<const D3DXVECTOR3*>(&_krTarget),
						&Up);
}





/********************************
            Protected
*********************************/





/********************************
            Private
*********************************/





void
CViewMatrix::Deinitialise()
{
	//Empty
}