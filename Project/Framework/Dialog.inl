//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   Dialog.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


void
CDialog::Show()
{
	ShowWindow(m_hHandle, 1);
}


void
CDialog::Hide()
{
	ShowWindow(m_hHandle, 0);
}