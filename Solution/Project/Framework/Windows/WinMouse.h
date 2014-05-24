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


#ifndef __WinMouse_H__
#define __WinMouse_H__


// Library Includes
#include <Windows.h>


// Local Includes
#include "Framework\Mouse.h"


// Types
#include "Defines\DataTypes.h"
#include "Framework\Observer.h"


// Constants
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC         ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE        ((USHORT) 0x02)
#endif


// Prototypes
class IObserver;


class CWinMouse : public IObserver
{

	// Member Functions
public:


	 CWinMouse();
	~CWinMouse();


	bool Initialise(HWND& _hrWindowHandle);


	void EndProcessing();


	void HandleMouseMessage(uint _uiMessage, LPARAM _lParam);


	void CenterCursor();


	void SetCursorVisible(bool _bVisible);


	// Inline Functions
	inline int GetTranslationX() const;
	inline int GetTranslationY() const;


protected:


	void ReadRawInput(LPARAM _lParam);


private:


	bool InitialiseRawInput(HWND& _hrWindowHandle);
	bool InitialiseSubjects();


	virtual void NotifyMessage(uint _uiSubject, void* _pDispatcher);


	void Deinitialise();
	bool DeinitialiseSubjects();


	CWinMouse(const CWinMouse& _krMouse);
	CWinMouse& operator = (const CWinMouse& _krMouse);


	// Member Variables
protected:


private:


	int m_iTranslationX;
	int m_iTranslationY;


	bool m_bCursorTmp;
	bool m_bCursorVisible;
	bool m_bWindowFocused;


};


#include "WinMouse.inl"


#endif //__WinMouse_H__