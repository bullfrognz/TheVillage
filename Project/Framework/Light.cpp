//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   Light.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// This Include
#include "Light.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CLight constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CLight::CLight()
: m_fPadding1(0)
, m_fPadding2(0)
, m_fAttenuation0(0)
, m_fAttenuation1(0)
, m_fAttenuation2(0)
, m_fRange(0)
, m_fTheta(0)
, m_fPhi(0)
, m_fFalloff(0)
, m_eType(INVALID_LIGHTTYPE)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CLight deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CLight::~CLight()
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
CLight::Deinitialise()
{
	//Empty
}