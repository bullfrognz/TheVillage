//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   DayNightCycle.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __DayNightCycle_H__
#define __DayNightCycle_H__


// Library Includes


// Local Includes
#include "Framework\Observer.h"


// Types


// Prototypes
class IRenderer;
class CObect;
class CLight;
class IEffect;


class CDayNightCycle : public IObserver
{

	// Member Functions
public:


	 CDayNightCycle();
	~CDayNightCycle();


	bool Initialise(IRenderer& _rRenderer, CCamera& _rPlayerCamera);
	void Process(float _fDeltatick, CCamera& _rPlayerCamera);
	bool Draw(IRenderer& _rRenderer, CCamera& _rPlayerCamera);


	CVector3 GetSunPosition();
	CVector3 GetSunDirection();


	float GetLightRatio();


	// Inline Functions


protected:


	void UpdateTime(CCamera& _rPlayerCamera);


private:


	bool InitialiseEffect(IRenderer& _rRenderer);


	void Deinitialise();


	virtual void NotifyMessage(uint _uiSubject, void* _pDispatcher);


	CDayNightCycle(const CDayNightCycle& _krDayNightCycle);
	CDayNightCycle& operator = (const CDayNightCycle& _krDayNightCycle);


	// Member Variables
protected:


private:


	CObject* m_pSunMoon;
	CLight* m_pSunLight;
	IEffect* m_pEffect;


	const float m_kfSecondsInDay;
	float m_fCurrentTime;
	float m_fMoonSunTranslation;

	
	bool m_bCycleForward;
	bool m_bCycleBackwards;


};


#endif //__DayNightCycle_H__