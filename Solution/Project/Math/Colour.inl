//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   Colour.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


void
CColour::AddRed(float _fX)
{
	m_fRed = _fX;
}


void
CColour::AddGreen(float _fY)
{
	m_fGreen = _fY;
}


void
CColour::AddBlue(float _fZ)
{
	m_fBlue = _fZ;
}


void
CColour::AddOpacity(float _fW)
{
	m_fOpacity = _fW;
}


void
CColour::Add(float _fX, float _fY, float _fZ, float _fW)
{
	m_fRed = _fX;
	m_fGreen = _fY;
	m_fBlue = _fZ;
	m_fOpacity = _fW;
}


void
CColour::SetRed(float _fX)
{
	m_fRed = _fX;
}


void
CColour::SetGreen(float _fY)
{
	m_fGreen = _fY;
}


void
CColour::SetBlue(float _fZ)
{
	m_fBlue = _fZ;
}


void
CColour::SetOpacity(float _fW)
{
	m_fOpacity = _fW;
}


void
CColour::Set(float _fX, float _fY, float _fZ, float _fW)
{
	m_fRed = _fX;
	m_fGreen = _fY;
	m_fBlue = _fZ;
	m_fOpacity = _fW;
}


float
CColour::GetRed() const
{
	return (m_fRed);
}


float
CColour::GetGreen() const
{
	return (m_fGreen);
}


float
CColour::GetBlue() const
{
	return (m_fBlue);
}


float
CColour::GetOpacity() const
{
	return (m_fOpacity);
}

