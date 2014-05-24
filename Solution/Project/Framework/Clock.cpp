//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   Clock.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// This Include
#include "Clock.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CClock constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CClock::CClock()
: m_i64CurrentTime(0)
, m_i64LastTime(0)
, m_i64CountsPerSecond(0)
, m_dDeltaTick(0)
, m_fPerfCounterTimeScale(0)
, m_fTimeElasped(0)
, m_uiFrameCount(0)
, m_uiFramesPerSecond(0)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CClock deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CClock::~CClock()
{
	Deinitialise();
}





bool
CClock::Initialise()
{
	bool bReturn = true;


	BOOL bQueryReturn = QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&m_i64CountsPerSecond));


	if (!bQueryReturn)
	{
		bReturn = false;
		//TODO: Update error. ("Could not query the performance frequency from the CPU. Feature may not be supported.");
	}
	else
	{
		m_fPerfCounterTimeScale = 1.0f / static_cast<float>(m_i64CountsPerSecond);


		bQueryReturn = QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_i64LastTime));
	}


	return (bReturn);

}





bool
CClock::Process()
{
	//Default return
	bool bReturn = false;
		

	BOOL bQueryReturn = QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_i64CurrentTime));


	if (!bQueryReturn)
	{
		// Could not query the performance frequency from the CPU. Feature may not be supported.
		bReturn = false;
	}


	m_dDeltaTick  = static_cast<double>(m_i64CurrentTime - m_i64LastTime);
	m_dDeltaTick *= m_fPerfCounterTimeScale;


	m_i64LastTime = m_i64CurrentTime;


	UpdateFPS();


	return (bReturn);
}





/********************************
            Protected
*********************************/





void
CClock::UpdateFPS()
{
	m_fTimeElasped += GetDeltaTick();


	if (m_fTimeElasped > 1.0f)
	{
		m_fTimeElasped -= 1.0f;
		m_uiFramesPerSecond = m_uiFrameCount;
		m_uiFrameCount = 0;
	}


	++ m_uiFrameCount;
}






/********************************
            Private
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CClock::Deinitialise()
{
	//Empty
}