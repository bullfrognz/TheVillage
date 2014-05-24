//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   WorldMatrix.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


void
CWorldMatrix::SetPositionX(float _fPositionX)
{
	m_fMatrix[3][0] = _fPositionX;
}


void
CWorldMatrix::SetPositionY(float _fPositionY)
{
	m_fMatrix[3][1] = _fPositionY;
}


void
CWorldMatrix::SetPositionZ(float _fPositionZ)
{
	m_fMatrix[3][2] = _fPositionZ;
}


void
CWorldMatrix::SetPosition(float _fPositionX, float _fPositionY, float _fPositionZ)
{
	m_fMatrix[3][0] = _fPositionX;
	m_fMatrix[3][1] = _fPositionY;
	m_fMatrix[3][2] = _fPositionZ;
}


void
CWorldMatrix::SetPosition(const CVector3& _kv3rPosition)
{
	m_fMatrix[3][0] = _kv3rPosition.GetX();
	m_fMatrix[3][1] = _kv3rPosition.GetY();
	m_fMatrix[3][2] = _kv3rPosition.GetZ();
}


void
CWorldMatrix::GetPosition(CVector3& _rPosition) const
{
	_rPosition.Set(m_fMatrix[3][0], m_fMatrix[3][1], m_fMatrix[3][2]);
}


float
CWorldMatrix::GetPositionX() const
{
	return (m_fMatrix[3][0]);
}


float
CWorldMatrix::GetPositionY() const
{
	return (m_fMatrix[3][1]);
}


float
CWorldMatrix::GetPositionZ() const
{
	return (m_fMatrix[3][2]);
}


void
CWorldMatrix::GetOrientationX(CVector3& _rOrientationX) const
{
	_rOrientationX.Set(m_fMatrix[0][0], m_fMatrix[0][1], m_fMatrix[0][2]);
}


void
CWorldMatrix::GetOrientationY(CVector3& _rOrientationY) const
{
	_rOrientationY.Set(m_fMatrix[1][0], m_fMatrix[1][1], m_fMatrix[1][2]);
}


void
CWorldMatrix::GetOrientationZ(CVector3& _rOrientationZ) const
{
	_rOrientationZ.Set(m_fMatrix[2][0], m_fMatrix[2][1], m_fMatrix[2][2]);
}



CVector3
CWorldMatrix::GetOrientationX() const
{
	return (CVector3(m_fMatrix[0][0], m_fMatrix[0][1], m_fMatrix[0][2]));
}


CVector3
CWorldMatrix::GetOrientationY() const
{
	return (CVector3(m_fMatrix[1][0], m_fMatrix[1][1], m_fMatrix[1][2]));
}


CVector3
CWorldMatrix::GetOrientationZ() const
{
	return (CVector3(m_fMatrix[2][0], m_fMatrix[2][1], m_fMatrix[2][2]));
}
