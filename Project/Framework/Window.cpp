//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   Window.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Utilities Includes
#include "Utilities\StrUtilities.h"
#include "Utilities\Messenger.h"


// Defines Includes
#include "Defines\Macros.h"


// Math Includes
#include "Math\Vector2.h"


// Framework Includes
#include "Framework\Application.h"
#include "Framework\DirectX 10\D10Renderer.h"
#include "Framework\Scene.h"
#include "Framework\Windows\WinMouse.h"
#include "Framework\Windows\WinKeyboard.h"


// Scene Includes
#include "Scene\Game\Game.h"


// This Include
#include "Window.h"


// Static Variables
const uint CWindow::s_kuiDefaultMarginX = 0;
const uint CWindow::s_kuiDefaultMarginY = 0;


// Function Prototypes
LRESULT CALLBACK WindowProcWrapper(HWND _hWindow, unsigned int _uiMessage, WPARAM _wParam, LPARAM _lParam);


// Implementation


/********************************
            Public
*********************************/




/*---------------------------------------------------------------------------------------------------------------------------
*
* Window class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWindow::CWindow()
: m_pRenderer(0)
, m_pMouse(0)
, m_pKeyboard(0)
, m_ulStyles(0)
, m_uiWidth(0)
, m_uiHeight(0)
, m_pScene(0)
, m_eChangeToScene(SCENE_INVALID)
, m_pChangeToSceneData(0)
{
	//Empty
}




/*---------------------------------------------------------------------------------------------------------------------------
*
* Window class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWindow::~CWindow()
{
	Deinitialise();
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets member variables and runs initialise functions to setup the window.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CWindow::Initialise(HINSTANCE& _hrInstance, const char* _kcpTitle, ulong _ulStyles, uint _uiWidth, uint _uiHeight)
{
	m_ulStyles = _ulStyles;
	m_uiWidth = _uiWidth;
	m_uiHeight = _uiHeight;


	FW_VALIDATE(InitialiseWinClass(_hrInstance));
	FW_VALIDATE(InitialiseHandle(_hrInstance, _kcpTitle));
	FW_VALIDATE(InitialiseRenderer());
	FW_VALIDATE(InitialiseMouseKeyboard());


	return (true);
}





void
CWindow::Process(float _fDeltaTick)
{
	if (m_eChangeToScene != SCENE_INVALID)
	{
		ExecuteSceneChange();
	}


	if (m_pScene)
	{
		m_pScene->Process(*m_pRenderer, _fDeltaTick);
	}


	m_pRenderer->BeginRendering(true, true, false);
	
	
	if (m_pScene)
	{
		m_pScene->Draw(*m_pRenderer);
	}


	m_pRenderer->EndRendering();
	m_pMouse->EndProcessing();
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Resizes the window.
*
* @author Bryce Booth
*
* @param _uiWidth		New window dimention width.
* @param _uiHeight		New window dimention height.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::Resize(uint _uiWidth, uint _uiHeight)
{
	::SetWindowPos(m_hWindowHandle, 0, 0, 0, _uiWidth, _uiHeight, SWP_NOZORDER | SWP_SHOWWINDOW);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Fills input vector with the current dimentions of this window.
*
* @author Bryce Booth
*
* @param m_bClientRect		Get inner dimentions of window, excluding window borders.
* @param _rDimentions		Vector to be filled with dimention data.
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2&
CWindow::GetDimentions(bool m_bClientRect, CVector2& _rDimentions)
{
	RECT WindowRect;


	if (m_bClientRect)
	{
		GetClientRect(m_hWindowHandle, &WindowRect);


		_rDimentions.SetX(static_cast<float>(WindowRect.right));
		_rDimentions.SetY(static_cast<float>(WindowRect.bottom));
	}
	else
	{
		GetWindowRect(m_hWindowHandle, &WindowRect);


		_rDimentions.SetX(static_cast<float>(WindowRect.right));
		_rDimentions.SetY(static_cast<float>(WindowRect.bottom));
	}


	return (_rDimentions);
}





LRESULT CALLBACK
CWindow::WindowProc(HWND _hWindow, uint _uiMessage, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uiMessage)
	{
		case WM_KILLFOCUS:
			Messenger::Send(SUBJECT_UNFOCUS, this);
			break;

		case WM_SETFOCUS:
			Messenger::Send(SUBJECT_FOCUS, this);
			break;

		case WM_CLOSE:
			CApplication::GetInstance().Quit();
			break;


		case WM_INPUT:
		case WM_LBUTTONUP:
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MOUSEMOVE:
			m_pMouse->HandleMouseMessage(_uiMessage, _lParam);
			break;

		case WM_KEYDOWN:
			m_pKeyboard->HandleKeyMessage(_wParam, true);
			break;

		case WM_KEYUP:
			m_pKeyboard->HandleKeyMessage(_wParam, false);
			break;

		default:
			break;
	}


	return (DefWindowProc(_hWindow, _uiMessage, _wParam, _lParam));
}





/********************************
            Protected
*********************************/





void
CWindow::ExecuteSceneChange()
{
	FW_DELETE(m_pScene);


	switch (m_eChangeToScene)
	{
		case SCENE_GAME:
			m_pScene = new CGame();
			break;


		default:
			//TODO: Add unknown scene error.
			break;
	}


	if (m_pScene == 0)
	{
		//TODO: Add memory error.
	}
	else
	{
		m_pScene->Initialise(*m_pRenderer, m_pChangeToSceneData);


		m_eChangeToScene = SCENE_INVALID;
		m_pChangeToSceneData = 0;
	}
}





/********************************
            Private
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* Setup the winclass.
*
* @author Bryce Booth
*
* @param _hrInstance		Application handle.
*
* @return bSuccessful		States if the winclass was successfully setup.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CWindow::InitialiseWinClass(HINSTANCE& _hrInstance)
{
	bool bSuccessful = true;


	WNDCLASSEX WinClass;
	WinClass.cbSize			= sizeof(WNDCLASSEX);
	WinClass.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; //CS_DBLCLKS | CS_OWNDC | 
	WinClass.lpfnWndProc	= WindowProcWrapper;
	WinClass.cbClsExtra		= 0;
	WinClass.cbWndExtra		= 0;
	WinClass.hInstance		= _hrInstance;
	WinClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	WinClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	WinClass.hbrBackground	= static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	WinClass.lpszMenuName	= NULL;
	WinClass.lpszClassName	= WINCLASSNAME;
	WinClass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);
	 
	ATOM atomRegistered = RegisterClassEx(&WinClass);


	if (!atomRegistered)
	{
		bSuccessful = false;
		//TODO: Add failed error.
	}


	return (bSuccessful);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates the window.
*
* @author Bryce Booth
*
* @param _hrInstance		Application handle.
* @param _kcpTitle			Window title.
*
* @return bCreated			States if the handle was successfully created.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CWindow::InitialiseHandle(HINSTANCE& _hrInstance, const char* _kcpTitle)
{
	bool bCreated = true;


	wchar_t* wcTitle = 0;
	StrUtilities::ConvertToWString(_kcpTitle, wcTitle);


	m_hWindowHandle = CreateWindowEx(NULL,
									 WINCLASSNAME,
									 wcTitle,
									 m_ulStyles,
									 s_kuiDefaultMarginX,
									 s_kuiDefaultMarginY,
									 m_uiWidth,
									 m_uiHeight,
									 NULL, NULL,
									 _hrInstance,
									 NULL);


	if (!m_hWindowHandle)
	{
		bCreated = false;
		//TODO: Add failed error
	}


	FW_ADELETE(wcTitle);


	return (bCreated);
}





bool
CWindow::InitialiseRenderer()
{
	CVector2 vInnerDimentions;
	GetDimentions(true, vInnerDimentions);


	m_pRenderer = new CD10Renderer();
	FW_VALIDATE(m_pRenderer->Initialise(m_hWindowHandle, static_cast<uint>(vInnerDimentions.GetX()), static_cast<uint>(vInnerDimentions.GetY()), false));


	return (true);
}





bool
CWindow::InitialiseMouseKeyboard()
{
	m_pMouse = new CWinMouse();
	FW_VALIDATE(m_pMouse->Initialise(m_hWindowHandle));


	m_pKeyboard = new CWinKeyboard();
	FW_VALIDATE(m_pKeyboard->Initialise());


	return (true);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Deletes owned class instances.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::Deinitialise()
{
	FW_DELETE(m_pScene);
	FW_DELETE(m_pRenderer);
	FW_DELETE(m_pMouse);
	FW_DELETE(m_pKeyboard);
}





LRESULT CALLBACK
WindowProcWrapper(HWND _hWindow, unsigned int _uiMessage, WPARAM _wParam, LPARAM _lParam)
{
	CWindow& rWindow = CApplication::GetInstance().GetWindow();


	if (&rWindow != 0)
	{
		return (rWindow.WindowProc(_hWindow, _uiMessage, _wParam, _lParam));
	}
	else
	{
		return (DefWindowProc(_hWindow, _uiMessage, _wParam, _lParam));
	}
}