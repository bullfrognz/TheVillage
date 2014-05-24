//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   TerrainVertex.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


CVector3&
CTerrainVertex::Position()
{
	return (m_vPosition);
}


CVector3&
CTerrainVertex::Normal()
{
	return (m_vNormal);
}


CVector2&
CTerrainVertex::UV()
{
	return (m_vUV);
}


float&
CTerrainVertex::TextureAlpha(uint _uiIndex)
{
	return (m_fTextureAlpha[_uiIndex]);
}