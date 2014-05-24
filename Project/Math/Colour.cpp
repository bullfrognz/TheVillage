//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   Colour.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// This Include
#include "Colour.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CColour constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CColour::CColour()
: m_fRed(0)
, m_fGreen(0)
, m_fBlue(0)
, m_fOpacity(0)
{
	//Empty
}





CColour::CColour(float _fRed, float _fGreen, float _fBlue, float _fOpacity)
: m_fRed(_fRed)
, m_fGreen(_fGreen)
, m_fBlue(_fBlue)
, m_fOpacity(_fOpacity)
{
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CColour deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CColour::~CColour()
{
	// Empty
}




/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/