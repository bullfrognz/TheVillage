//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   WinKeyboard.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <Windows.h>


// Defines Includes
#include "Defines\Macros.h"


// Local Includes
#include "Utilities\Messenger.h"


// This Include
#include "WinKeyboard.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CWinKeyboard constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWinKeyboard::CWinKeyboard()
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CWinKeyboard deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWinKeyboard::~CWinKeyboard()
{
	Deinitialise();
}





bool
CWinKeyboard::Initialise()
{
	// Empty


	return (true);
}




void
CWinKeyboard::HandleKeyMessage(uint _uiKey, bool _bDown)
{
	int iSubject = 0;


	switch (_uiKey)
	{
		case VK_BACK:
			iSubject = (_bDown) ? KEY_DWN_BACK : KEY_UP_BACK;
			break;

		case VK_TAB:
			iSubject = (_bDown) ? KEY_DWN_TAB : KEY_UP_TAB;
			break;

		case VK_RETURN:
			iSubject = (_bDown) ? KEY_DWN_RETURN : KEY_UP_RETURN;
			break;

		case VK_SHIFT:
			iSubject = (_bDown) ? KEY_DWN_SHIFT : KEY_UP_SHIFT;
			break;

		case VK_CONTROL:
			iSubject = (_bDown) ? KEY_DWN_CONTROL : KEY_UP_CONTROL;
			break;

		case VK_ESCAPE:
			iSubject = (_bDown) ? KEY_DWN_ESCAPE : KEY_UP_ESCAPE;
			break;

		case VK_SPACE:
			iSubject = (_bDown) ? KEY_DWN_SPACE : KEY_UP_SPACE;
			break;

		case VK_LEFT:
			iSubject = (_bDown) ? KEY_DWN_LEFTARROW : KEY_UP_LEFTARROW;
			break;

		case VK_RIGHT:
			iSubject = (_bDown) ? KEY_DWN_RIGHTARROW : KEY_UP_RIGHTARROW;
			break;

		case VK_UP:
			iSubject = (_bDown) ? KEY_DWN_UPARROW : KEY_UP_UPARROW;
			break;

		case VK_DOWN:
			iSubject = (_bDown) ? KEY_DWN_DOWNARROW : KEY_UP_DOWNARROW;
			break;

		case VK_F1:
			iSubject = (_bDown) ? KEY_DWN_F01 : KEY_UP_F01;
			break;

		case VK_F2:
			iSubject = (_bDown) ? KEY_DWN_F02 : KEY_UP_F02;
			break;

		case VK_F3:
			iSubject = (_bDown) ? KEY_DWN_F03 : KEY_UP_F03;
			break;

		case VK_F4:
			iSubject = (_bDown) ? KEY_DWN_F04 : KEY_UP_F04;
			break;

		case VK_F5:
			iSubject = (_bDown) ? KEY_DWN_F05 : KEY_UP_F05;
			break;

		case VK_F6:
			iSubject = (_bDown) ? KEY_DWN_F06 : KEY_UP_F06;
			break;

		case VK_F7:
			iSubject = (_bDown) ? KEY_DWN_F07 : KEY_UP_F07;
			break;

		case VK_F8:
			iSubject = (_bDown) ? KEY_DWN_F08 : KEY_UP_F08;
			break;

		case VK_F9:
			iSubject = (_bDown) ? KEY_DWN_F09 : KEY_UP_F09;
			break;

		case VK_F10:
			iSubject = (_bDown) ? KEY_DWN_F10 : KEY_UP_F10;
			break;

		case VK_F11:
			iSubject = (_bDown) ? KEY_DWN_F11 : KEY_UP_F11;
			break;

		case VK_F12:
			iSubject = (_bDown) ? KEY_DWN_F12 : KEY_UP_F12;
			break;

		case 'A':
			iSubject = (_bDown) ? KEY_DWN_A : KEY_UP_A;
			break;

		case 'B':
			iSubject = (_bDown) ? KEY_DWN_B : KEY_UP_B;
			break;

		case 'C':
			iSubject = (_bDown) ? KEY_DWN_C : KEY_UP_C;
			break;

		case 'D':
			iSubject = (_bDown) ? KEY_DWN_D : KEY_UP_D;
			break;

		case 'E':
			iSubject = (_bDown) ? KEY_DWN_E : KEY_UP_E;
			break;

		case 'F':
			iSubject = (_bDown) ? KEY_DWN_F : KEY_UP_F;
			break;

		case 'G':
			iSubject = (_bDown) ? KEY_DWN_G : KEY_UP_G;
			break;

		case 'H':
			iSubject = (_bDown) ? KEY_DWN_H : KEY_UP_H;
			break;

		case 'I':
			iSubject = (_bDown) ? KEY_DWN_I : KEY_UP_I;
			break;

		case 'J':
			iSubject = (_bDown) ? KEY_DWN_J : KEY_UP_J;
			break;

		case 'K':
			iSubject = (_bDown) ? KEY_DWN_K : KEY_UP_K;
			break;

		case 'L':
			iSubject = (_bDown) ? KEY_DWN_L : KEY_UP_L;
			break;

		case 'M':
			iSubject = (_bDown) ? KEY_DWN_M : KEY_UP_M;
			break;

		case 'N':
			iSubject = (_bDown) ? KEY_DWN_N : KEY_UP_N;
			break;

		case 'O':
			iSubject = (_bDown) ? KEY_DWN_O : KEY_UP_O;
			break;

		case 'P':
			iSubject = (_bDown) ? KEY_DWN_P : KEY_UP_P;
			break;

		case 'Q':
			iSubject = (_bDown) ? KEY_DWN_Q : KEY_UP_Q;
			break;

		case 'R':
			iSubject = (_bDown) ? KEY_DWN_R : KEY_UP_R;
			break;

		case 'S':
			iSubject = (_bDown) ? KEY_DWN_S : KEY_UP_S;
			break;

		case 'T':
			iSubject = (_bDown) ? KEY_DWN_T : KEY_UP_T;
			break;

		case 'U':
			iSubject = (_bDown) ? KEY_DWN_U : KEY_UP_U;
			break;

		case 'V':
			iSubject = (_bDown) ? KEY_DWN_V : KEY_UP_V;
			break;

		case 'W':
			iSubject = (_bDown) ? KEY_DWN_W : KEY_UP_W;
			break;

		case 'X':
			iSubject = (_bDown) ? KEY_DWN_X : KEY_UP_X;
			break;

		case 'Y':
			iSubject = (_bDown) ? KEY_DWN_Y : KEY_UP_Y;
			break;

		case 'Z':
			iSubject = (_bDown) ? KEY_DWN_Z : KEY_UP_Z;
			break;

		case '1':
			iSubject = (_bDown) ? KEY_DWN_1 : KEY_UP_1;
			break;

		case '2':
			iSubject = (_bDown) ? KEY_DWN_2 : KEY_UP_2;
			break;

		case '3':
			iSubject = (_bDown) ? KEY_DWN_3 : KEY_UP_3;
			break;

		case '4':
			iSubject = (_bDown) ? KEY_DWN_4 : KEY_UP_4;
			break;

		case '5':
			iSubject = (_bDown) ? KEY_DWN_5 : KEY_UP_5;
			break;

		case '6':
			iSubject = (_bDown) ? KEY_DWN_6 : KEY_UP_6;
			break;

		case '7':
			iSubject = (_bDown) ? KEY_DWN_7 : KEY_UP_7;
			break;

		case '8':
			iSubject = (_bDown) ? KEY_DWN_8 : KEY_UP_8;
			break;

		case '9':
			iSubject = (_bDown) ? KEY_DWN_9 : KEY_UP_9;
			break;

		case '0':
			iSubject = (_bDown) ? KEY_DWN_0 : KEY_UP_0;
			break;
	}


	if (iSubject != 0)
	{
		Messenger::Send(iSubject, this);
	}
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





void
CWinKeyboard::Deinitialise()
{
	// Empty
}