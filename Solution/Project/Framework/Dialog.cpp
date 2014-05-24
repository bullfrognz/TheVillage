//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   Dialog.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "resource.h"
#include "Framework\Application.h"
#include "Framework\DialogMsgTarget.h"


// This Include
#include "Dialog.h"


// Static Variables
std::map<HWND, CDialog*> CDialog::s_DialogInstances;


// Function Prototypes
BOOL CALLBACK DisplayDialogCallback(HWND _hWindow, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam);


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CDialog constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDialog::CDialog()
: m_pMsgTarget(0)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CDialog deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDialog::~CDialog()
{
	Deinitialise();
}





bool
CDialog::Initialise(uint _uiResourceId, IDialogMsgTarget* _pMsgTarget)
{
	m_pMsgTarget = _pMsgTarget;


	m_hHandle = CreateDialog(CApplication::GetInstance().GetInstanceHandle(), MAKEINTRESOURCE(_uiResourceId), 0, DisplayDialogCallback);


	s_DialogInstances.insert( std::pair<HWND, CDialog*>(m_hHandle, this) );


	return (true);
}





bool
CDialog::IsButtonChecked(uint _uiResourceId)
{
	uint uiButtonState = IsDlgButtonChecked(m_hHandle, _uiResourceId);


	return (uiButtonState == BST_CHECKED);
}





bool
CDialog::SetButtonChecked(uint _uiButtonId, bool _bChecked)
{
	bool bSuccessful = (CheckDlgButton(m_hHandle, _uiButtonId, _bChecked) != 0);


	return (bSuccessful);
}





bool
CDialog::SetRadioChecked(uint _uiRadioId, uint _uiStartRangeId, uint _uiEndRangeId)
{
	bool bSuccessful = (CheckRadioButton(m_hHandle, _uiStartRangeId, _uiEndRangeId, _uiRadioId) != 0);


	return (bSuccessful);
}





BOOL CALLBACK
CDialog::DialogProc(HWND _hWindow, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uiMessage)
	{
	case WM_COMMAND:
		m_pMsgTarget->ProcessDialogCommand(_uiMessage, _wParam, _lParam);
		break;

	case WM_CLOSE:
		Hide();
		break;

	default:
		break;
	}



	return (FALSE);
}





CDialog*
CDialog::GetInstance(HWND& _hrWindow)
{
	CDialog* pDialogInstance = 0;


	std::map<HWND, CDialog*>::iterator DialogContainer = s_DialogInstances.find(_hrWindow);


	if (DialogContainer != s_DialogInstances.end())
	{
		pDialogInstance = (*DialogContainer).second;
	}


	return (pDialogInstance);
}





/********************************
            Protected
*********************************/





/********************************
            Private
*********************************/





void
CDialog::Deinitialise()
{
	DestroyWindow(m_hHandle);
}





BOOL CALLBACK
DisplayDialogCallback(HWND _hWindow, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam)
{
	BOOL bReturn = CDialog::GetInstance(_hWindow)->DialogProc(_hWindow, _uiMessage, _wParam, _lParam);


	return (bReturn);
}