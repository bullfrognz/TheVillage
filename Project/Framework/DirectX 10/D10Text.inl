//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   D10Text.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <assert.h>


// Local Includes
#include "Defines\Macros.h"


// Implementation


void
CD10Text::SetSize(uint _uiSize)
{
	m_uiFontSize = _uiSize;
}


void
CD10Text::SetColour(float _fRed, float _fGreen, float _fBlue)
{
	assert(_fRed >= 0.0f && _fRed <= 1.0f);
	assert(_fGreen >= 0.0f && _fGreen <= 1.0f);
	assert(_fBlue >= 0.0f && _fBlue <= 1.0f);


	m_tColour.r = _fRed;
	m_tColour.g = _fGreen;
	m_tColour.b = _fBlue;
}


void
CD10Text::SetTransparency(float _fLevel)
{
	assert(_fLevel >= 0.0f && _fLevel <= 1.0f);


	m_tColour.a = _fLevel;
}


void
CD10Text::SetPosition(int _iX, int _iY)
{
	m_tContainer.left = _iX;
	m_tContainer.top = _iY;
	m_tContainer.right = _iX;
	m_tContainer.bottom = _iY;
}


void
CD10Text::SetPositionX(int _iX)
{
	m_tContainer.left = _iX;
	m_tContainer.right = _iX;
}


void
CD10Text::SetPositionY(int _iY)
{
	m_tContainer.top = _iY;
	m_tContainer.bottom = _iY;
}

