//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   DialogMsgTarget.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __DialogMsgTarget_H__
#define __DialogMsgTarget_H__


// Library Includes


// Local Includes


// Types


// Constants


// Prototypes


class IDialogMsgTarget
{

	// Member Functions
public:


			 IDialogMsgTarget() {};
	virtual ~IDialogMsgTarget() {};


	virtual void ProcessDialogCommand(UINT _uiMessage, WPARAM _wParam, LPARAM _lParam) = 0;


	// Inline Functions


protected:


private:


	// Member Variables
protected:


private:


};


#endif //__DialogMsgTarget_H__