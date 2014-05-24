//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   Plane.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


void 
CPlane::SetA(float _fA)
{
	m_fA = _fA;
}


void
CPlane::SetB(float _fB)
{
	m_fB = _fB;
}


void
CPlane::SetC(float _fC)
{
	m_fC = _fC;
}


void
CPlane::SetD(float _fD)
{
	m_fD = _fD;
}


void
CPlane::Set(float _fA, float _fB, float _fC, float _fD)
{
	m_fA = _fA;
	m_fB = _fB;
	m_fC = _fC;
	m_fD = _fD;
}


float
CPlane::GetA() const
{
	return (m_fA);
}


float
CPlane::GetB() const
{
	return (m_fB);
}


float
CPlane::GetC() const
{
	return (m_fC);
}


float
CPlane::GetD() const
{
	return (m_fD);
}