//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   Segment.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


void
CSegment::SetHeight(uint _uiX, uint _uiZ, ushort _usHeight)
{
	m_uspHeightmap[_uiZ * m_tLayoutDesc.uiWidth + _uiX] = _usHeight;
}


void
CSegment::SetHeightScale(float _fScale)
{
	m_fHeightScale = _fScale;
}


void
CSegment::SetPosition(float _fX, float _fZ)
{
	m_fPositionX = _fX;
	m_fPositionZ = _fZ;
	m_bUpdateBounds = true;
}


void
CSegment::SetVerticesOffset(uint _uiOffset)
{
	m_uiVerticesOffset = _uiOffset;
}


void
CSegment::SetActive(bool _bActive)
{
	m_bActive = _bActive;
}



float
CSegment::GetHeight(uint _uiX, uint _uiZ) const
{
	return (m_uspHeightmap[_uiZ * m_tLayoutDesc.uiWidth + _uiX] / m_fHeightScale);
}


float
CSegment::GetPositionX() const
{
	return (m_fPositionX);
}


float
CSegment::GetPositionZ() const
{
	return (m_fPositionZ);
}


uint
CSegment::GetWidth() const
{
	return (m_tLayoutDesc.uiWidth);
}


uint
CSegment::GetLength() const
{
	return (m_tLayoutDesc.uiLength);
}


uint
CSegment::GetVerticesOffset() const
{
	return (m_uiVerticesOffset);
}


uint
CSegment::GetVerticesCount() const
{
	return (m_tLayoutDesc.uiWidth * m_tLayoutDesc.uiLength);
}


uint
CSegment::GetIndicesOffset() const
{
	return (s_tIndicesInfo[m_eType].uiOffset);
}


uint
CSegment::GetIndicesCount() const
{
	return (s_tIndicesInfo[m_eType].uiCount);
}


uint
CSegment::GetIndexX() const
{
	return (m_tLayoutDesc.uiIndexX);
}


uint
CSegment::GetIndexZ() const
{
	return (m_tLayoutDesc.uiIndexZ);
}


const CAABB&
CSegment::GetAABBox() const
{
	return (*m_pAABBox);
}


const CSegment::TNeighbourhood&
CSegment::GetNeighbourhood() const
{
	return (m_tNeighbourHood);
}


bool
CSegment::IsActive() const
{
	return (m_bActive);
}