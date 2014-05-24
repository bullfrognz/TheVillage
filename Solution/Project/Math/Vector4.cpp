//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   Vector4.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Math\Vector3.h"


// This Include
#include "Vector4.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CVector4 constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector4::CVector4()
: m_fX(0)
, m_fY(0)
, m_fZ(0)
, m_fW(0)
{
	//Empty
}





CVector4::CVector4(const CVector3& _krVector)
: m_fX(_krVector.GetX())
, m_fY(_krVector.GetY())
, m_fZ(_krVector.GetZ())
, m_fW(0)
{
	// Empty
}





CVector4::CVector4(float _fX, float _fY, float _fZ, float _fW)
: m_fX(_fX)
, m_fY(_fY)
, m_fZ(_fZ)
, m_fW(_fW)
{
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CVector4 deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector4::~CVector4()
{
	Deinitialise();
}




/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





void
CVector4::Deinitialise()
{
	//Empty
}