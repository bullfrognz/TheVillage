//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   Waypoint.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <cmath>


// Defines Inludes
#include "Defines\Buffer.h"
#include "Defines\VertexTypes.h"


// Framework Includes
#include "Framework\Renderer.h"
#include "Framework\VertexBuffer.h"


// This Include
#include "Waypoint.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CWaypoint constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWaypoint::CWaypoint()
: m_fPositionX(0)
, m_fPositionZ(0)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CWaypoint deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWaypoint::~CWaypoint()
{
	Deinitialise();
}





bool
CWaypoint::Initialise(IRenderer& _rRenderer)
{
	/*
	TVertexBufferDesc tVBuffer_Desc;
	tVBuffer_Desc.ePrimitiveType = PRIMITIVETYPE_LINESTRIP;
	tVBuffer_Desc.eUsage = BUFFERUSAGE_DYNAMIC;
	tVBuffer_Desc.uiNumVertices = 19;
	tVBuffer_Desc.uiStride = sizeof(TCVertex);
	tVBuffer_Desc.ulFVF = TCVertexFVF;


	_rRenderer.InstanceVertexBuffer(tVBuffer_Desc, m_pVertexBuffer);


	const int kiNumPoints = 18;
	float fAngle = 6.28318531f / kiNumPoints;
	TCVertex* pVertexData = 0;


	m_pVertexBuffer->Lock(LOCKFLAG_WRITEDISCARD, reinterpret_cast<void**>(&pVertexData));

	
	for (int i = 0; i < kiNumPoints; ++ i)
	{
		pVertexData[i].fPositionX = sin(fAngle * i);
		pVertexData[i].fPositionZ = cos(fAngle * i);
	}


	pVertexData[18].fPositionZ = cos(0.0f);


	m_pVertexBuffer->Unlock();
	*/
	

	return (true);
}





void
CWaypoint::Draw(IRenderer& _rRenderer)
{
	//_rRenderer.DrawVertexBuffer(m_pDefaultEffect, m_pVertexBuffer);
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





void
CWaypoint::Deinitialise()
{
	//Empty
}