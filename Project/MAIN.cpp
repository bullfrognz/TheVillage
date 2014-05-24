//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   MAIN.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <windows.h>
//#include "Plugins\VLD\include\vld.h"


// Local Includes
#include "Defines\Macros.h"
#include "Framework\Application.h"
#include "Framework\Window.h"
#include "Framework\Scene.h"


// Implementation


int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _1pCmdLine, INT _iCmdShow)
{
	MSG tWindowsMessage;
	ZeroMemory(&tWindowsMessage, sizeof(MSG));
	bool bApplicationSetup = false;


	CApplication& rApplication = CApplication::GetInstance();
	
	
	bApplicationSetup = rApplication.Initialise(_hInstance, 1024, 768);


	if (bApplicationSetup == false)
	{
		//TODO: Add application creation error.
	}
	else
	{
		//Set default scene
		rApplication.GetWindow().SetScene(SCENE_GAME);


		do
		{
			if (PeekMessage(&tWindowsMessage, NULL, 0, 0, PM_REMOVE))
			{
				if (!IsDialogMessage(0, &tWindowsMessage))

				TranslateMessage(&tWindowsMessage); //Translate any accesserator keys
				DispatchMessage(&tWindowsMessage);  //Send the message to the window proc
			}
			else
			{
				rApplication.ExecuteOneFrame();
			}
		}
		while (tWindowsMessage.message != WM_QUIT);
	}


	CApplication::GetInstance().DestroyInstance();


	return (static_cast<int>(tWindowsMessage.wParam));
}