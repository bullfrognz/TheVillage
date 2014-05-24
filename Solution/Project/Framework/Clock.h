//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   Clock.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __IGFEB11_IG500_CLOCK_H__
#define __IGFEB11_IG500_CLOCK_H__


// Library Includes
#include <windows.h>


// Local Includes


// Types
#include "Defines\DataTypes.h"


// Constants


// Prototypes


class CClock
{

	// Member Functions
public:


	 CClock();
	~CClock();


	virtual bool Initialise();
	virtual bool Process();


	// Inline Functions
	inline float GetDeltaTick() const;
	inline uint FramesPerSecond() const;


protected:


	void UpdateFPS();


private:


	void Deinitialise();


	CClock(const CClock& _krClock);
	CClock& operator = (const CClock& _krClock);


	// Member Variables
protected:


private:


	__int64 m_i64CurrentTime;
	__int64 m_i64LastTime;
	__int64 m_i64CountsPerSecond;


	double m_dDeltaTick;


	float m_fPerfCounterTimeScale;
	float m_fTimeElasped;
	

	uint m_uiFrameCount;
	uint m_uiFramesPerSecond;


};


#include "Clock.inl"


#endif //__IGFEB11_IG500_CLOCK_H__

