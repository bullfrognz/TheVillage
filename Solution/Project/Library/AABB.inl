//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   AABB.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


void
CAABB::GetCenter(CVector3& _vrCenter) const
{
	_vrCenter = m_vCenter;
}


CVector3
CAABB::GetCenter() const
{
	return (m_vCenter);
}


float
CAABB::GetHalfWidth() const
{
	return (m_fHalfWidth);
}


float
CAABB::GetSideOffset(ESide _eSide) const
{
	return (m_fSideOffset[_eSide]);
}