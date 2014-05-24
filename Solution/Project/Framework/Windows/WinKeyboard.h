//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   WinKeyboard.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __WinKeyboard_H__
#define __WinKeyboard_H__


// Library Includes


// Local Includes
#include "Defines\DataTypes.h"
#include "Framework\Keyboard.h"


// Types


// Constants


// Prototypes


class CWinKeyboard
{

	// Member Functions
public:


	 CWinKeyboard();
	~CWinKeyboard();


	bool Initialise();


	void HandleKeyMessage(uint _uiKey, bool _bDown);


	// Inline Functions


protected:


private:


	void Deinitialise();


	CWinKeyboard(const CWinKeyboard& _krWinKeyboard);
	CWinKeyboard& operator = (const CWinKeyboard& _krWinKeyboard);


	// Member Variables
protected:


private:


};


#endif //__WinKeyboard_H__