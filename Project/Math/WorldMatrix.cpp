//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   WorldMatrix.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <D3DX10.h>


// Local Includes



// This Include
#include "WorldMatrix.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





CWorldMatrix::CWorldMatrix()
{
	CMatrix::Identity();
}





CWorldMatrix::~CWorldMatrix()
{
	Deinitialise();
}





void
CWorldMatrix::SetScale(float _fX, float _fY, float _fZ)
{
	D3DXMatrixScaling(reinterpret_cast<D3DXMATRIX*>(this), _fX, _fY, _fZ);
}





void
CWorldMatrix::SetOrientation(float _fPitch, float _fRoll, float _fYaw)
{
	CMatrix xTemp;


	D3DXMatrixRotationYawPitchRoll(reinterpret_cast<D3DXMATRIX*>(&xTemp), _fYaw, _fPitch, _fRoll);


	*this *= xTemp;
}




void
CWorldMatrix::LookAt(const CVector3& _kvrTargetPosition)
{

}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





void
CWorldMatrix::Deinitialise()
{
	//Empty
}