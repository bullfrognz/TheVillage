//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   Vector3.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <cmath>


// Local Includes


// This Include
#include "Vector3.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CVector3 constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3::CVector3()
: m_fX(0)
, m_fY(0)
, m_fZ(0)
{
	//Empty
}


CVector3::CVector3(float _fX, float _fY, float _fZ)
: m_fX(_fX)
, m_fY(_fY)
, m_fZ(_fZ)
{
	//Empty
}


CVector3::CVector3(const CVector3& _kRight)
: m_fX(_kRight.m_fX)
, m_fY(_kRight.m_fY)
, m_fZ(_kRight.m_fZ)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CVector3 deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3::~CVector3()
{
	//Empty
}





float
CVector3::Magnitude() const
{
	float fMagnitudeSquare = m_fX * m_fX;
	fMagnitudeSquare += m_fY * m_fY;
	fMagnitudeSquare += m_fZ * m_fZ;


	return (sqrt(fMagnitudeSquare));
}




float
CVector3::MagnitudeSquare() const
{
	float fMagnitudeSquare = m_fX * m_fX;
	fMagnitudeSquare += m_fY * m_fY;
	fMagnitudeSquare += m_fZ * m_fZ;


	return (fMagnitudeSquare);
}





float
CVector3::Distance(const CVector3& _kvrTarget) const
{
	CVector3 vDifference = (*this) - _kvrTarget;


	return (vDifference.Magnitude());
}





float
CVector3::DistanceSquare(const CVector3& _kvrTarget) const
{
	CVector3 vDifference = (*this) - _kvrTarget;


	return (vDifference.MagnitudeSquare());
}






float
CVector3::Dot(const CVector3& _krVector) const
{
	float fDot = 0;
	fDot += m_fX * _krVector.m_fX;
	fDot += m_fY * _krVector.m_fY;
	fDot += m_fZ * _krVector.m_fZ;


	return (fDot);
}





float
CVector3::DotAngle(const CVector3& _krVector) const
{
	float fDot = 0;
	fDot += m_fX * _krVector.m_fX;
	fDot += m_fY * _krVector.m_fY;
	fDot += m_fZ * _krVector.m_fZ;


	float fUMag = (*this).Magnitude();
	float fVMag = _krVector.Magnitude();


	float fAngle = acos(fDot / (fUMag * fVMag));


	return (fAngle);
}





void
CVector3::Cross(const CVector3& _krRight, CVector3& _rResult) const
{
	_rResult.SetX(m_fY * _krRight.m_fZ - m_fZ * _krRight.m_fY);
	_rResult.SetY(m_fZ * _krRight.m_fX - m_fX * _krRight.m_fZ);
	_rResult.SetZ(m_fX * _krRight.m_fY - m_fY * _krRight.m_fX);
}





CVector3
CVector3::Cross(const CVector3& _kvrRight) const
{
	CVector3 vReturn(m_fY * _kvrRight.m_fZ - m_fZ * _kvrRight.m_fY,
					 m_fZ * _kvrRight.m_fX - m_fX * _kvrRight.m_fZ,
					 m_fX * _kvrRight.m_fY - m_fY * _kvrRight.m_fX);


	return (vReturn);
}





void
CVector3::Normalise()
{
	float fUnit = sqrt((m_fX * m_fX) + (m_fY * m_fY) + (m_fZ * m_fZ));


	if (fUnit != 0.0f)
	{
		m_fX /= fUnit;
		m_fY /= fUnit;
		m_fZ /= fUnit;
	}
}





void
CVector3::Normalise(CVector3& _rResult) const
{
	_rResult = *this;
	_rResult.Normalise();
}




CVector3
CVector3::Normalise() const
{
	CVector3 vResult(*this);
	vResult.Normalise();


	return (vResult);
}





bool
CVector3::IsZero()
{
	if (m_fX != 0 ||
		m_fY != 0 ||
		m_fZ != 0)
	{
		return (false);
	}
	else
	{
		return (true);
	}
}




const CVector3&
CVector3::operator += (const CVector3& _krRight)
{
	m_fX += _krRight.GetX();
	m_fY += _krRight.GetY();
	m_fZ += _krRight.GetZ();


	return (*this);
}





const CVector3&
CVector3::operator -= (const CVector3& _kRight)
{
	m_fX -= _kRight.GetX();
	m_fY -= _kRight.GetY();
	m_fZ -= _kRight.GetZ();


	return (*this);
}






const CVector3&
CVector3::operator *= (float _fValue)
{
	m_fX *= _fValue;
	m_fY *= _fValue;
	m_fZ *= _fValue;


	return (*this);
}






const CVector3&
CVector3::operator /= (float _fValue)
{
	m_fX /= _fValue;
	m_fY /= _fValue;
	m_fZ /= _fValue;


	return (*this);
}






CVector3
CVector3::operator + (const CVector3& _kRight) const
{
	CVector3 Return(m_fX + _kRight.GetX(),
					m_fY + _kRight.GetY(),
					m_fZ + _kRight.GetZ());


	return (Return);
}






CVector3
CVector3::operator - (const CVector3& _kRight) const
{
	CVector3 Return(m_fX - _kRight.GetX(),
					m_fY - _kRight.GetY(),
					m_fZ - _kRight.GetZ());


	return (Return);
}






CVector3
CVector3::operator * (float _fValue) const
{
	CVector3 Return(m_fX * _fValue,
					m_fY * _fValue,
					m_fZ * _fValue);


	return (Return);
}






CVector3
CVector3::operator / (float _fValue) const
{
	CVector3 Return(m_fX / _fValue,
					m_fY / _fValue,
					m_fZ / _fValue);


	return (Return);
}






bool
CVector3::operator == (const CVector3&_kRight) const
{
	if (m_fX != _kRight.GetX() ||
		m_fY != _kRight.GetY() ||
		m_fZ != _kRight.GetZ())
	{
		return (false);
	}
	else
	{
		return (true);
	}
}





bool
CVector3::operator != (const CVector3&_kRight) const
{
	if (m_fX == _kRight.GetX() &&
		m_fY == _kRight.GetY() &&
		m_fZ == _kRight.GetZ())
	{
		return (false);
	}
	else
	{
		return (true);
	}
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/