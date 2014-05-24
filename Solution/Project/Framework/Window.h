//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   Window.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __IGFEB11_IG500_WINDOW_H__
#define __IGFEB11_IG500_WINDOW_H__


// Library Includes
#include <Windows.h>


// Local Includes
#include "Defines\Datatypes.h"


// Types


// Constants
#define WINCLASSNAME L"DirectX 10"


// Prototypes
class IRenderer;
class CWinMouse;
class CWinKeyboard;
class CScene;
class CVector2;
enum EScene;


class CWindow
{

	// Member Types
public:


	enum ESubject
	{
		SUBJECT_FOCUS		= 4400,
		SUBJECT_UNFOCUS		= 4401,

		SUBJECT_DESCROYED	= 4402
	};


	// Member Functions
public:


	 CWindow();
	~CWindow();


	bool Initialise(HINSTANCE& _hrInstance, const char* _kcpTitle, ulong _ulStyles, uint _uiWidth, uint _uiHeight);


	void Process(float _fDeltaTick);


	void Resize(uint _uiWidth, uint _uiHeight);


	CVector2& GetDimentions(bool m_bClientRect, CVector2& _rDimentions);


	LRESULT CALLBACK WindowProc(HWND _hWindow, unsigned int _uiMessage, WPARAM _wParam, LPARAM _lParam);


	// Inline Functions
	inline void SetScene(EScene _eScene, void* _pSceneData = 0);


	inline HWND& GetWindowHandle();


	inline CScene& GetCurrentScene();
	inline IRenderer& GetRenderer();
	inline CWinMouse& GetMouse();
	inline CWinKeyboard& GetKeyboard();


	inline bool IsFocused() const;


protected:


	void ExecuteSceneChange();


private:


	bool InitialiseWinClass(HINSTANCE& _hrInstance);
	bool InitialiseHandle(HINSTANCE& _hrInstance, const char* _kcpTitle);
	bool InitialiseRenderer();
	bool InitialiseMouseKeyboard();
	

	void Deinitialise();


	CWindow(const CWindow& _krWindow);
	CWindow& operator = (const CWindow& _krWindow);


	// Member Variables
protected:


	HWND m_hWindowHandle;


	IRenderer* m_pRenderer;
	CWinMouse* m_pMouse;
	CWinKeyboard* m_pKeyboard;
	CScene* m_pScene;


	EScene m_eChangeToScene;
	void*  m_pChangeToSceneData;


	DWORD m_ulStyles;
	uint m_uiWidth;
	uint m_uiHeight;


	bool m_bFocused;


private:


	static const uint s_kuiDefaultMarginX;
	static const uint s_kuiDefaultMarginY;


};


#include "Window.inl"


#endif //__IGFEB11_IG500_WINDOW_H__