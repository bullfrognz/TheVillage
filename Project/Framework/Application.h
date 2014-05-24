//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   Application.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __IGFEB11_IG500_APPLICATION2_H__
#define __IGFEB11_IG500_APPLICATION2_H__


// Library Includes
#include <windows.h>


// Local Includes
#include "Defines\DataTypes.h"


// Types


// Constants


// Prototypes
class CClock;
class CWindow;


class CApplication
{

	// Member Functions
public:


	~CApplication();


	bool Initialise(HINSTANCE& _hrInstance, uint _uiWindowWidth, uint _uiWindowHeight);


	void ExecuteOneFrame();


	static CApplication& GetInstance();
	static void DestroyInstance();


	// Inline Functions
	inline HINSTANCE& GetInstanceHandle();
	inline CWindow& GetWindow();
	inline CClock& GetClock();
	inline void Quit();


protected:


	void UpdateFPS(float _fDeltaTick);


private:


	bool InitialiseClock();
	bool InitialiseWindow(uint _uiWindowWidth, uint _uiWindowHeight);


	void Deinitialise();


	CApplication();
	CApplication(const CApplication& _krApplication);
	CApplication& operator = (const CApplication& _krApplication);


	// Member Variables
protected:


private:


	HINSTANCE m_hInstance;


	CClock* m_pClock;
	CWindow* m_pWindow;


	static CApplication* s_pApplication;


};


#include "Application.inl"


#endif //__IGFEB11_IG500_APPLICATION2_H__