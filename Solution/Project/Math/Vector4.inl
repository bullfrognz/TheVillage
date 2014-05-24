//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   Vector4.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


void
CVector4::AddX(float _fX)
{
	m_fX = _fX;
}


void
CVector4::AddY(float _fY)
{
	m_fY = _fY;
}


void
CVector4::AddZ(float _fZ)
{
	m_fZ = _fZ;
}


void
CVector4::AddW(float _fW)
{
	m_fW = _fW;
}


void
CVector4::Add(float _fX, float _fY, float _fZ, float _fW)
{
	m_fX = _fX;
	m_fY = _fY;
	m_fZ = _fZ;
	m_fW = _fW;
}


void
CVector4::SetX(float _fX)
{
	m_fX = _fX;
}


void
CVector4::SetY(float _fY)
{
	m_fY = _fY;
}


void
CVector4::SetZ(float _fZ)
{
	m_fZ = _fZ;
}


void
CVector4::SetW(float _fW)
{
	m_fW = _fW;
}


void
CVector4::Set(float _fX, float _fY, float _fZ, float _fW)
{
	m_fX = _fX;
	m_fY = _fY;
	m_fZ = _fZ;
	m_fW = _fW;
}


float
CVector4::GetX() const
{
	return (m_fX);
}


float
CVector4::GetY() const
{
	return (m_fY);
}


float
CVector4::GetZ() const
{
	return (m_fZ);
}


float
CVector4::GetW() const
{
	return (m_fW);
}

