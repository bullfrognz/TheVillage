//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   Vector3.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


void
CVector3::AddX(float _fX)
{
	m_fX += _fX;
}


void
CVector3::AddY(float _fY)
{
	m_fY += _fY;
}


void
CVector3::AddZ(float _fZ)
{
	m_fZ += _fZ;
}


void
CVector3::Add(float _fX, float _fY, float _fZ)
{
	m_fX += _fX;
	m_fY += _fY;
	m_fZ += _fZ;
}


void
CVector3::SetX(float _fX)
{
	m_fX = _fX;
}


void
CVector3::SetY(float _fY)
{
	m_fY = _fY;
}


void
CVector3::SetZ(float _fZ)
{
	m_fZ = _fZ;
}


void
CVector3::Set(float _fX, float _fY, float _fZ)
{
	m_fX = _fX;
	m_fY = _fY;
	m_fZ = _fZ;
}


float
CVector3::GetX() const
{
	return (m_fX);
}


float
CVector3::GetY() const
{
	return (m_fY);
}


float
CVector3::GetZ() const
{
	return (m_fZ);
}