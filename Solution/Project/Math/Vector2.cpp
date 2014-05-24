//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   Vector2.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <d3dx9.h>


// Local Includes


// This Include
#include "Vector2.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CVector2 constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2::CVector2()
: m_fX(0.0f)
, m_fY(0.0f)
{
	//Empty
}


CVector2::CVector2(float _fX, float _fY)
: m_fX(_fX)
, m_fY(_fY)
{
}


CVector2::CVector2(const CVector2& _krRight)
: m_fX(_krRight.GetX())
, m_fY(_krRight.GetY())
{
	// Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CVector2 deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2::~CVector2()
{
	//Empty
}





float
CVector2::Magnitude() const
{
	float fMagnitudeSquare = m_fX * m_fX;
	fMagnitudeSquare += m_fY * m_fY;


	return (sqrt(fMagnitudeSquare));
}




float
CVector2::MagnitudeSquare() const
{
	float fMagnitudeSquare = m_fX * m_fX;
	fMagnitudeSquare += m_fY * m_fY;


	return (fMagnitudeSquare);
}





float
CVector2::Distance(const CVector2& _kvrTarget) const
{
	CVector2 vDifference = (*this) - _kvrTarget;


	return (vDifference.Magnitude());
}





float
CVector2::DistanceSquare(const CVector2& _kvrTarget) const
{
	CVector2 vDifference = (*this) - _kvrTarget;


	return (vDifference.MagnitudeSquare());
}






void
CVector2::Normalise()
{
	float fMagnitude = sqrt(m_fX*m_fX + m_fY*m_fY);


	if (fMagnitude)
	{
		m_fX /= fMagnitude;
		m_fY /= fMagnitude;
	}
}





const CVector2&
CVector2::operator += (const CVector2& _krRight)
{
	m_fX += _krRight.GetX();
	m_fY += _krRight.GetY();


	return (*this);
}





const CVector2&
CVector2::operator -= (const CVector2& _krRight)
{
	m_fX -= _krRight.GetX();
	m_fY -= _krRight.GetY();


	return (*this);
}





const CVector2&
CVector2::operator *= (float _fValue)
{
	m_fX *= _fValue;
	m_fY *= _fValue;


	return (*this);
}





const CVector2&
CVector2::operator /= (float _fValue)
{
	m_fX /= _fValue;
	m_fY /= _fValue;


	return (*this);
}





CVector2 
CVector2::operator + (const CVector2& _krRight) const
{
	CVector2 TempVector(m_fX + _krRight.GetX(),
						m_fY + _krRight.GetY());


	return (TempVector);
}





CVector2
CVector2::operator - (const CVector2& _krRight) const
{
	CVector2 TempVector(m_fX - _krRight.GetX(),
						m_fY - _krRight.GetY());


	return (TempVector);
}





CVector2
CVector2::operator * (float _fValue) const
{
	CVector2 TempVector(m_fX * _fValue,
						m_fY * _fValue);


	return (TempVector);
}





CVector2
CVector2::operator / (float _fValue) const
{
	CVector2 TempVector(m_fX / _fValue,
						m_fY / _fValue);


	return (TempVector);
}





bool
CVector2::operator == (const CVector2&_krRight) const
{
	if (m_fX == _krRight.GetX() &&
		m_fY == _krRight.GetY())
	{
		return (true);
	}
	else
	{
		return (false);
	}
}





bool
CVector2::operator != (const CVector2&_krRight) const
{
	if (m_fX != _krRight.GetX() ||
		m_fY != _krRight.GetY())
	{
		return (true);
	}
	else
	{
		return (false);
	}
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/