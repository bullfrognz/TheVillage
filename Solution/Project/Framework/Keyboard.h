//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Keyboard.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Keyboard_H__
#define __Keyboard_H__


// Library Includes


// Local Includes


// Types
enum EKeyboardSubject
{
	MIN_KEY				= 41000,

	KEY_DWN_A			= 41000,
	KEY_DWN_B			= 41001,
	KEY_DWN_C			= 41002,
	KEY_DWN_D			= 41003,
	KEY_DWN_E			= 41004,
	KEY_DWN_F			= 41005,
	KEY_DWN_G			= 41006,
	KEY_DWN_H			= 41007,
	KEY_DWN_I			= 41008,
	KEY_DWN_J			= 41009,
	KEY_DWN_K			= 41010,
	KEY_DWN_L			= 41011,
	KEY_DWN_M			= 41012,
	KEY_DWN_N			= 41013,
	KEY_DWN_O			= 41014,
	KEY_DWN_P			= 41015,
	KEY_DWN_Q			= 41016,
	KEY_DWN_R			= 41017,
	KEY_DWN_S			= 41018,
	KEY_DWN_T			= 41019,
	KEY_DWN_U			= 41020,
	KEY_DWN_V			= 41021,
	KEY_DWN_W			= 41022,
	KEY_DWN_X			= 41023,
	KEY_DWN_Y			= 41024,
	KEY_DWN_Z			= 41025,
	KEY_DWN_BACK		= 41027,
	KEY_DWN_TAB			= 41028,
	KEY_DWN_RETURN		= 41029,
	KEY_DWN_SHIFT		= 41030,
	KEY_DWN_CONTROL		= 41031,
	KEY_DWN_ESCAPE		= 41032,
	KEY_DWN_SPACE		= 41033,
	KEY_DWN_LEFTARROW	= 41034,
	KEY_DWN_RIGHTARROW	= 41035,
	KEY_DWN_UPARROW		= 41036,
	KEY_DWN_DOWNARROW	= 41037,
	KEY_DWN_F01			= 41038,
	KEY_DWN_F02			= 41039,
	KEY_DWN_F03			= 41040,
	KEY_DWN_F04			= 41041,
	KEY_DWN_F05			= 41042,
	KEY_DWN_F06			= 41043,
	KEY_DWN_F07			= 41044,
	KEY_DWN_F08			= 41045,
	KEY_DWN_F09			= 41046,
	KEY_DWN_F10			= 41047,
	KEY_DWN_F11			= 41048,
	KEY_DWN_F12			= 41049,
	KEY_DWN_1			= 41050,
	KEY_DWN_2			= 41051,
	KEY_DWN_3			= 41052,
	KEY_DWN_4			= 41053,
	KEY_DWN_5			= 41054,
	KEY_DWN_6			= 41055,
	KEY_DWN_7			= 41056,
	KEY_DWN_8			= 41057,
	KEY_DWN_9			= 41058,
	KEY_DWN_0			= 41059,

	KEY_UP_A			= 41200,
	KEY_UP_B			= 41201,
	KEY_UP_C			= 41202,
	KEY_UP_D			= 41203,
	KEY_UP_E			= 41204,
	KEY_UP_F			= 41205,
	KEY_UP_G			= 41206,
	KEY_UP_H			= 41207,
	KEY_UP_I			= 41208,
	KEY_UP_J			= 41209,
	KEY_UP_K			= 41210,
	KEY_UP_L			= 41211,
	KEY_UP_M			= 41212,
	KEY_UP_N			= 41213,
	KEY_UP_O			= 41214,
	KEY_UP_P			= 41215,
	KEY_UP_Q			= 41216,
	KEY_UP_R			= 41217,
	KEY_UP_S			= 41218,
	KEY_UP_T			= 41219,
	KEY_UP_U			= 41220,
	KEY_UP_V			= 41221,
	KEY_UP_W			= 41222,
	KEY_UP_X			= 41223,
	KEY_UP_Y			= 41224,
	KEY_UP_Z			= 41225,
	KEY_UP_BACK			= 41226,
	KEY_UP_TAB			= 41227,
	KEY_UP_RETURN		= 41228,
	KEY_UP_SHIFT		= 41229,
	KEY_UP_CONTROL		= 41230,
	KEY_UP_ESCAPE		= 41231,
	KEY_UP_SPACE		= 41232,
	KEY_UP_LEFTARROW	= 41233,
	KEY_UP_RIGHTARROW	= 41234,
	KEY_UP_UPARROW		= 41235,
	KEY_UP_DOWNARROW	= 41236,
	KEY_UP_F01			= 41237,
	KEY_UP_F02			= 41238,
	KEY_UP_F03			= 41239,
	KEY_UP_F04			= 41240,
	KEY_UP_F05			= 41241,
	KEY_UP_F06			= 41242,
	KEY_UP_F07			= 41243,
	KEY_UP_F08			= 41244,
	KEY_UP_F09			= 41245,
	KEY_UP_F10			= 41246,
	KEY_UP_F11			= 41247,
	KEY_UP_F12			= 41248,
	KEY_UP_1			= 41249,
	KEY_UP_2			= 41250,
	KEY_UP_3			= 41251,
	KEY_UP_4			= 41252,
	KEY_UP_5			= 41253,
	KEY_UP_6			= 41254,
	KEY_UP_7			= 41255,
	KEY_UP_8			= 41256,
	KEY_UP_9			= 41257,
	KEY_UP_0			= 41258,

	MAX_KEY				= 41300,
};


// Prototypes


class IKeyboard
{

	// Member Functions
public:


			 IKeyboard() {};
	virtual ~IKeyboard() {};


	// Inline Functions


protected:


private:


	// Member Variables
protected:


private:


};


#endif //__Keyboard_H__