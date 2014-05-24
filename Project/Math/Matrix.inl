//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Matrix.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


float
CMatrix::GetValue(ushort _usRow, ushort _usColumn) const
{
	return (m_fMatrix[_usRow][_usColumn]);
}


void
CMatrix::SetValue(ushort _usRow, ushort _usColumn, float _fValue)
{
	m_fMatrix[_usRow][_usColumn] = _fValue;
}