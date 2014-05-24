//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Mouse.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Mouse_H__
#define __Mouse_H__


// Library Includes


// Local Includes


// Types
enum EMouseSubject
{
	MIN_MOUSE			= 41400,

	CURSOR_CENTER,
	CURSOR_HIDE,
	CURSOR_SHOW,

	MOUSE_DWN_LEFT,		
	MOUSE_DWN_RIGHT,
	MOUSE_DWN_WHEEL,

	MOUSE_UP_LEFT,
	MOUSE_UP_RIGHT,
	MOUSE_UP_WHEEL,

	MOUSE_MOVE,
	MOUSE_RAWINPUT,

	MAX_MOUSE
};


// Prototypes


class IMouse
{

	// Member Functions
public:


			 IMouse() {};
	virtual ~IMouse() {};


	// Inline Functions


protected:


private:


	// Member Variables
protected:


private:


};


#endif //__Mouse_H__