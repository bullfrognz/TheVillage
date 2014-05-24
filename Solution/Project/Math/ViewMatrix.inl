//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   ViewMatrix.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


void
CViewMatrix::GetLookAt(CVector3& _rLookAt) const
{
	_rLookAt.Set(m_fMatrix[0][2], m_fMatrix[1][2], m_fMatrix[2][2]);
}


void
CViewMatrix::GetRight(CVector3& _rRight) const
{
	_rRight.Set(m_fMatrix[0][0], m_fMatrix[1][0], m_fMatrix[2][0]);
}


void
CViewMatrix::GetUp(CVector3& _rUp) const
{
	_rUp.Set(m_fMatrix[0][1], m_fMatrix[1][1], m_fMatrix[2][1]);
}


CVector3
CViewMatrix::GetLookAt() const
{
	return (CVector3(m_fMatrix[0][2], m_fMatrix[1][2], m_fMatrix[2][2]));
}


CVector3
CViewMatrix::GetRight() const
{
	return (CVector3(m_fMatrix[0][0], m_fMatrix[1][0], m_fMatrix[2][0]));
}


CVector3
CViewMatrix::GetUp() const
{
	return (CVector3(m_fMatrix[0][1], m_fMatrix[1][1], m_fMatrix[2][1]));
}