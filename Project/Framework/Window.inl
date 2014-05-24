//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name   :   Window.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


void
CWindow::SetScene(EScene _eScene, void* _pSceneData)
{
	m_eChangeToScene = _eScene;
	m_pChangeToSceneData = _pSceneData;
}


HWND&
CWindow::GetWindowHandle()
{
	return (m_hWindowHandle);
}


CScene&
CWindow::GetCurrentScene()
{
	return (*m_pScene);
}


IRenderer&
CWindow::GetRenderer()
{
	return (*m_pRenderer);
}


CWinMouse&
CWindow::GetMouse()
{
	return (*m_pMouse);
}


CWinKeyboard&
CWindow::GetKeyboard()
{
	return (*m_pKeyboard);
}


bool
CWindow::IsFocused() const
{
	bool bFocused = false;


	if (GetActiveWindow() == m_hWindowHandle)
	{
		bFocused = true;
	}
	

	return (bFocused);
}