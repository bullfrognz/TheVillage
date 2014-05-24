//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   Mouse.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Defines Includes
#include "Defines\Macros.h"


// Utilities Includes
#include "Utilities\Messenger.h"
#include "Framework\Window.h"


// Math Includes
#include "Math\Vector2.h"


// Local Includes
#include "Framework\Application.h"
#include "Framework\Window.h"


// This Include
#include "WinMouse.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CWinMouse constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWinMouse::CWinMouse()
: m_iTranslationX(0)
, m_iTranslationY(0)
, m_bCursorVisible(true)
, m_bCursorTmp(true)
, m_bWindowFocused(true)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CWinMouse deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWinMouse::~CWinMouse()
{
	Deinitialise();
}





bool
CWinMouse::Initialise(HWND& _hrWindowHandle)
{
	InitialiseRawInput(_hrWindowHandle);
	InitialiseSubjects();
	CenterCursor();


	return (true);
}





void
CWinMouse::EndProcessing()
{
	m_iTranslationX = 0;
	m_iTranslationY = 0;
}





void
CWinMouse::HandleMouseMessage(uint _uiMessage, LPARAM _lParam)
{
	int iSubject = true;
	bool bSubjectSet = true;


	switch (_uiMessage)
	{
		case WM_LBUTTONUP:
			iSubject = MOUSE_UP_LEFT;
			break;

		case WM_LBUTTONDOWN:
			iSubject = MOUSE_DWN_LEFT;
			break;

		case WM_RBUTTONUP:
			iSubject = MOUSE_UP_RIGHT;
			break;

		case WM_RBUTTONDOWN:
			iSubject = MOUSE_DWN_RIGHT;
			break;

		case WM_MOUSEMOVE:
			iSubject = MOUSE_MOVE;
			break;

		case WM_INPUT:
			iSubject = MOUSE_RAWINPUT;
			ReadRawInput(_lParam);
			break;


		default:
			bSubjectSet = false;
			break;
	}


	if (bSubjectSet &&
		m_bWindowFocused)
	{
		Messenger::Send(iSubject, this);
	}
}





void
CWinMouse::CenterCursor()
{
	if (m_bWindowFocused)
	{
		CVector2 WindowDimentions;
		CApplication::GetInstance().GetWindow().GetDimentions(true, WindowDimentions);


		//Default
		POINT MousePosition;
		MousePosition.x = static_cast<long>(WindowDimentions.GetX() / 2);
		MousePosition.y = static_cast<long>(WindowDimentions.GetY() / 2);


		//Convert position relative to screen
		::ScreenToClient(CApplication::GetInstance().GetWindow().GetWindowHandle(), &MousePosition);



		::SetCursorPos(MousePosition.x, MousePosition.y);
	}
}









void
CWinMouse::SetCursorVisible(bool _bVisible)
{
	if (_bVisible == true && m_bCursorVisible == false)
	{
		::ShowCursor(TRUE);


		m_bCursorVisible = true;
	}
	else if (_bVisible == false && m_bCursorVisible == true)
	{
		::ShowCursor(FALSE);


		m_bCursorVisible = false;
	}
}





/********************************
            Protected
*********************************/





void
CWinMouse::ReadRawInput(LPARAM _lParam)
{
	UINT dwSize = 40;
	static BYTE lpb[40];
    

	GetRawInputData(reinterpret_cast<HRAWINPUT>(_lParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
	RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(lpb);
    

	if (raw->header.dwType == RIM_TYPEMOUSE) 
	{
		m_iTranslationX += raw->data.mouse.lLastX;
		m_iTranslationY += raw->data.mouse.lLastY;
	} 
}





/********************************
            Private
*********************************/





bool
CWinMouse::InitialiseRawInput(HWND& _hrWindowHandle)
{
	RAWINPUTDEVICE Rid[1];
	Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC; 
	Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE; 
	Rid[0].dwFlags = RIDEV_INPUTSINK;   
	Rid[0].hwndTarget = _hrWindowHandle;


	::RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));


	return (true);
}





bool
CWinMouse::InitialiseSubjects()
{
	FW_VALIDATE(Messenger::RegisterObserver(CURSOR_CENTER, this));
	FW_VALIDATE(Messenger::RegisterObserver(CURSOR_HIDE, this));
	FW_VALIDATE(Messenger::RegisterObserver(CURSOR_SHOW, this));
	FW_VALIDATE(Messenger::RegisterObserver(CWindow::SUBJECT_FOCUS, this));
	FW_VALIDATE(Messenger::RegisterObserver(CWindow::SUBJECT_UNFOCUS, this));


	return (true);
}





void
CWinMouse::NotifyMessage(uint _uiSubject, void* _pDispatcher)
{
	switch (_uiSubject)
	{
	case CURSOR_CENTER:
		CenterCursor();
		break;

	case CURSOR_HIDE:
		SetCursorVisible(false);
		break;

	case CURSOR_SHOW:
		SetCursorVisible(true);
		break;

	case CWindow::SUBJECT_FOCUS:
		m_bWindowFocused = static_cast<CWindow*>(_pDispatcher)->IsFocused();
		SetCursorVisible(m_bCursorTmp);
		break;

	case CWindow::SUBJECT_UNFOCUS:
		m_bWindowFocused = static_cast<CWindow*>(_pDispatcher)->IsFocused();
		m_bCursorTmp = m_bCursorVisible;
		SetCursorVisible(true);
		break;
	}
}





void
CWinMouse::Deinitialise()
{
	DeinitialiseSubjects();
}





bool
CWinMouse::DeinitialiseSubjects()
{
	FW_VALIDATE(Messenger::UnregisterObserver(CURSOR_CENTER, this));
	FW_VALIDATE(Messenger::UnregisterObserver(CURSOR_HIDE, this));
	FW_VALIDATE(Messenger::UnregisterObserver(CURSOR_SHOW, this));
	FW_VALIDATE(Messenger::UnregisterObserver(CWindow::SUBJECT_FOCUS, this));
	FW_VALIDATE(Messenger::UnregisterObserver(CWindow::SUBJECT_UNFOCUS, this));


	return (true);
}