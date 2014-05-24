//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name   :   Application.inl
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


HINSTANCE&
CApplication::GetInstanceHandle()
{
	return (m_hInstance);
}


CWindow&
CApplication::GetWindow()
{
	return (*m_pWindow);
}


CClock&
CApplication::GetClock()
{
	return (*m_pClock);
}


void
CApplication::Quit()
{
	PostQuitMessage(0);
}