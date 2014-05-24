//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   FPCamera.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __FPCamera_H__
#define __FPCamera_H__


// Library Includes


// Local Includes
#include "Framework\Camera.h"
#include "Framework\Observer.h"


// Types


// Constants


// Prototypes


class CFPCamera : public CCamera, public IObserver
{

	// Member Functions
public:


			 CFPCamera();
	virtual ~CFPCamera();


	virtual bool Initialise(uint _uiWidth, uint _uiHeight);


	virtual bool Process(float _fDeltaTick);


	// Inline Functions


protected:


	bool ProcessMouse(float _fDeltaTick);
	bool ProcessMovement(float _fDeltaTick);


	void LimitRotation();


private:


	bool InitialiseObserver();


	virtual void NotifyMessage(uint _uiSubject, void* _pDispatcher);


	void Deinitialise();
	bool DeinitialiseObserver();


	CFPCamera(const CFPCamera& _krFPCamera);
	CFPCamera& operator = (const CFPCamera& _krFPCamera);


	// Member Variables
protected:


private:


	CVector3 m_Velocity;


	float m_fMovementVelocity;
	float m_fMouseTranslationX;
	float m_fMouseTranslationY;
	float m_fSensitivity;


	bool m_bMoveForward;
	bool m_bMoveBack;
	bool m_bMoveLeft;
	bool m_bMoveRight;
	bool m_bMoveUp;
	bool m_bMoveDown;


};


#endif //__FPCamera_H__