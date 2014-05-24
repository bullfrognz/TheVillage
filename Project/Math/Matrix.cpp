//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   Matrix.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <D3DX10.h>


// Local Includes


// This Include
#include "Matrix.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Matrix class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMatrix::CMatrix()
{
	ZeroMemory(m_fMatrix, sizeof(float) * 4 * 4);
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Matrix class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMatrix::~CMatrix()
{
	//Empty
}





void
CMatrix::Identity()
{
	D3DXMatrixIdentity(reinterpret_cast<D3DXMATRIX*>(this));
}





void
CMatrix::Inverse(CMatrix& _rTarget) const
{
	float fDeterminant = GetDeterminant();


	D3DXMatrixInverse(reinterpret_cast<D3DXMATRIX*>(&_rTarget), &fDeterminant, reinterpret_cast<const D3DXMATRIX*>(this));
}





float
CMatrix::GetDeterminant() const
{
	float fDeterminant = D3DXMatrixDeterminant(reinterpret_cast<const D3DXMATRIX*>(this));


	return (fDeterminant);
}






bool
CMatrix::operator == (const CMatrix& _krMatrix) const
{
	//Compare memory of the two matrix
	int iMemResult = memcmp(this, &_krMatrix, sizeof(CMatrix));


	return (iMemResult == 0);
}






bool
CMatrix::operator != (const CMatrix& _krMatrix) const
{
	//Compare memory of the two matrix
	int iMemResult = memcmp(this, &_krMatrix, sizeof(CMatrix));


	return (iMemResult != 0);;
}






CMatrix&
CMatrix::operator += (const CMatrix& _krMatrix)
{
	for (uchar ucRow = 0; ucRow < 4; ++ ucRow)
	{
		for (uchar ucColumn = 0; ucColumn < 4; ++ ucColumn)
		{
			m_fMatrix[ucRow][ucColumn] += _krMatrix.GetValue(ucRow, ucColumn);
		}
	}


	return (*this);
}





CMatrix&
CMatrix::operator -= (const CMatrix& _krMatrix)
{
	for (uchar ucRow = 0; ucRow < 4; ++ ucRow)
	{
		for (uchar ucColumn = 0; ucColumn < 4; ++ ucColumn)
		{
			m_fMatrix[ucRow][ucColumn] -= _krMatrix.GetValue(ucRow, ucColumn);
		}
	}


	return (*this);
}






CMatrix&
CMatrix::operator *= (const CMatrix& _krMatrix)
{
	D3DXMatrixMultiply(reinterpret_cast<D3DXMATRIX*>(this), reinterpret_cast<D3DXMATRIX*>(this), reinterpret_cast<const D3DXMATRIX*>(&_krMatrix));


	return (*this);
}






CMatrix
CMatrix::operator + (const CMatrix& _krMatrix) const
{
	CMatrix mtxTempMatrix;

	
	mtxTempMatrix  = *this;
	mtxTempMatrix += _krMatrix;
	

	return (mtxTempMatrix);
}






CMatrix
CMatrix::operator - (const CMatrix& _krMatrix) const
{
	CMatrix mtxTempMatrix;

	
	mtxTempMatrix  = *this;
	mtxTempMatrix -= _krMatrix;
	

	return (mtxTempMatrix);
}






CMatrix
CMatrix::operator * (const CMatrix& _krMatrix) const
{
	CMatrix mtxTempMatrix;

	
	mtxTempMatrix  = *this;
	mtxTempMatrix *= _krMatrix;
	

	return (mtxTempMatrix);
}






/********************************
            Protected
*********************************/





/********************************
            Private
*********************************/