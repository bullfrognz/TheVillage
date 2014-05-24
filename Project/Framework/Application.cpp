//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   Application.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Defines\Macros.h"
#include "Framework\Window.h"
#include "Framework\Clock.h"


// This Include
#include "Application.h"


// Static Variables
CApplication* CApplication::s_pApplication = 0;


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* Application class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CApplication::CApplication()
: m_hInstance(0)
, m_pClock(0)
, m_pWindow(0)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Application class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CApplication::~CApplication()
{
	Deinitialise();
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates clock and window instances.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CApplication::Initialise(HINSTANCE& _hrInstance, uint _uiWindowWidth, uint _uiWindowHeight)
{
	//Saet member variables
	m_hInstance = _hrInstance;


	//Run class initialisers
	FW_VALIDATE(InitialiseClock());
	FW_VALIDATE(InitialiseWindow(_uiWindowWidth, _uiWindowHeight));


	return (true);
}




void
CApplication::ExecuteOneFrame()
{
	m_pClock->Process();


	float fDeltaTick = m_pClock->GetDeltaTick();


	if (fDeltaTick > 1.0f / 30.0f)
	{
		fDeltaTick = 1.0f / 30.0f;
	}


	m_pWindow->Process(fDeltaTick);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the instance of application or creates it if it does not exist.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CApplication&
CApplication::GetInstance()
{
	if (s_pApplication == 0)
	{
		s_pApplication = new CApplication();
	}

	return (*s_pApplication);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Destroys the application instance.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CApplication::DestroyInstance()
{
	FW_DELETE(s_pApplication);
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





bool
CApplication::InitialiseClock()
{
	m_pClock = new CClock();
	FW_VALIDATE(m_pClock->Initialise());


	return (true);
}





bool
CApplication::InitialiseWindow(uint _uiWindowWidth, uint _uiWindowHeight)
{
	char* cpWindowTitle = "The Village";
	DWORD dwStyles = WS_VISIBLE | WS_OVERLAPPED | WS_SYSMENU;


	m_pWindow = new CWindow();
	FW_VALIDATE(m_pWindow->Initialise(m_hInstance, cpWindowTitle, dwStyles, _uiWindowWidth, _uiWindowHeight));


	return (true);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CApplication::Deinitialise()
{
	FW_DELETE(m_pClock);
	FW_DELETE(m_pWindow);
}


