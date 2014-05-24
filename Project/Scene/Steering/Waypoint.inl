//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   Waypoint.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


void
CWaypoint::SetPosition(float _fX, float _fZ)
{
	m_WorldMatrix.SetPosition(_fX, 0.0f, _fZ);
}



CWorldMatrix&
CWaypoint::GetWorldMatrix()
{
	return (m_WorldMatrix);
}