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


float
CClock::GetDeltaTick() const
{
	return (static_cast<float>(m_dDeltaTick));
}


uint
CClock::FramesPerSecond() const
{
	return (m_uiFramesPerSecond);
}