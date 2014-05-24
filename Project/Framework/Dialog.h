//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   Dialog.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Dialog_H__
#define __Dialog_H__


// Library Includes
#include <Windows.h>
#include <map>


// Local Includes
#include "Defines\DataTypes.h"


// Types
enum EDialogItem
{
	EDIALOGITEM_INVALID,

	EDIALOGITEM_COMBOBOX,
	EDIALOGITEM_RADIO,

	EDIALOGITEM_MAX
};


// Constants


// Prototypes
class IDialogMsgTarget;


class CDialog
{

	// Member Functions
public:


	 CDialog();
	~CDialog();


	bool Initialise(uint _uiResourceId, IDialogMsgTarget* _pMsgTarget);
	bool IsButtonChecked(uint _uiResourceId);
	

	bool SetButtonChecked(uint _uiButtonId, bool _bChecked);
	bool SetRadioChecked(uint _uiRadioId, uint _uiStartRangeId, uint _uiEndRangeId);


	BOOL CALLBACK DialogProc(HWND _hWindow, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam);


	static CDialog* GetInstance(HWND& _hrWindow);


	// Inline Functions
	inline void Show();
	inline void Hide();


protected:


private:


	void Deinitialise();


	CDialog(const CDialog& _krDialog);
	CDialog& operator = (const CDialog& _krDialog);


	// Member Variables
protected:


private:


	HWND m_hHandle;


	IDialogMsgTarget* m_pMsgTarget;


	static std::map<HWND, CDialog*> s_DialogInstances;


};


#include "Dialog.inl"


#endif //__Dialog_H__