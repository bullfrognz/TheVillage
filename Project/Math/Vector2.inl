//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   Vector2.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation

void
CVector2::SetX(float _fX)
{
	m_fX = _fX;
}


void
CVector2::SetY(float _fY)
{
	m_fY = _fY;
}


void
CVector2::Set(float _fX, float _fY)
{
	m_fX = _fX;
	m_fY = _fY;
}


float
CVector2::GetX() const
{
	return (m_fX);
}


float
CVector2::GetY() const
{
	return (m_fY);
}


bool
CVector2::IsZero() const
{
	if (m_fX == 0.0f &&
		m_fY == 0.0f)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

