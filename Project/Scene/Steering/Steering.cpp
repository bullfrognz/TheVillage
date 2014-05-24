//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   Steering.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Framework Includes
#include "Framework\Renderer.h"


// Scene Includes
#include "Scene\Steering\Waypoint.h"
#include "Scene\Steering\Actor.h"


// This Include
#include "Steering.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CSteering constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSteering::CSteering()
: m_pActor(0)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CSteering deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSteering::~CSteering()
{
	Deinitialise();
}


bool
CSteering::Initialise(IRenderer& _rRenderer, void* _pData)
{
	m_pActor = new CActor();
	m_pActor->Initialise(_rRenderer);


	CWaypoint* pWaypoint = new CWaypoint();
	pWaypoint->Initialise(_rRenderer);
	pWaypoint->SetPosition(-2.0f, 0.0f);


	m_pWaypoints.push_back(pWaypoint);


	return (true);
}


void
CSteering::Process(IRenderer& _rRenderer, float _fDeltaTick)
{
	m_pActor->Process(_fDeltaTick, m_pWaypoints[0]);
}


void
CSteering::Draw(IRenderer& _rRenderer)
{
	for (uint i = 0; i < m_pWaypoints.size(); ++ i)
	{
		m_pWaypoints[i]->Draw(_rRenderer);
	}


	m_pActor->Draw(_rRenderer);
}




/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





void
CSteering::Deinitialise()
{
	//Empty
}