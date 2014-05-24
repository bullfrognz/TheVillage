//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   CLASSNAME.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


void
CTerrain::SetFogEnabled(bool _bEnabled)
{
	m_bFogEnabled = _bEnabled;
	m_pEffect->SetVariable("g_bFogEnabled", m_bFogEnabled);
}



bool
CTerrain::IsBusy()
{
	return (m_DirtyProcessThreadId != 0);
}


void
CTerrain::AddDirtySegment(uint _uiSegmentId)
{
	m_aDirtySegments.push_back(_uiSegmentId);
	m_pSegments[_uiSegmentId].SetActive(false);
}


int
CTerrain::GenerateSegmentId(uint _uiX, uint _uiZ)
{
	return (_uiZ * m_uiSegmentCountX + _uiX);
}