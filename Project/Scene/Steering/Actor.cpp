//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   Actor.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Defines Inludes
#include "Defines\Buffer.h"
#include "Defines\VertexTypes.h"
#include "Defines\EffectTypes.h"


// Framework Includes
#include "Framework\Renderer.h"
#include "Framework\VertexBuffer.h"


// Scene Includes
#include "Scene\Steering\Waypoint.h"


// This Include
#include "Actor.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CActor constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CActor::CActor()
: m_pVertexBuffer(0)
, m_fTurnRate(4.80f)
, m_fAcceleration(1)
, m_fVelocity(8)
, m_fYRotation(0)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CActor deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CActor::~CActor()
{
	Deinitialise();
}





bool
CActor::Initialise(IRenderer& _rRenderer)
{
	/*
	TVertexBufferDesc tVBuffer_Desc;
	tVBuffer_Desc.ePrimitiveType = PRIMITIVETYPE_TRIANGLELIST;
	tVBuffer_Desc.eUsage = BUFFERUSAGE_DYNAMIC;
	tVBuffer_Desc.uiNumVertices = 3;
	tVBuffer_Desc.uiStride = sizeof(TCVertex);
	tVBuffer_Desc.ulFVF = TCVertexFVF;


	_rRenderer.InstanceVertexBuffer(tVBuffer_Desc, m_pVertexBuffer);


	TDefaultEftVertex* pVertexData = 0;


	m_pVertexBuffer->Lock(LOCKFLAG_WRITEDISCARD, reinterpret_cast<void**>(&pVertexData));


	pVertexData[0].PositionX = 0;
	pVertexData[0].PositionZ = 1;
	pVertexData[0].fGreen = 0.9f;


	pVertexData[1].fPositionX = 0.5;
	pVertexData[1].fPositionZ = -0.5;
	pVertexData[1].fGreen = 0.9f;


	pVertexData[2].fPositionX = -0.5;
	pVertexData[2].fPositionZ = -0.5;
	pVertexData[2].fGreen = 0.9f;


	m_pVertexBuffer->Unlock();
	*/


	return (true);
}





void
CActor::Process(float _fDeltaTick, CWaypoint* _pTargetWaypoint)
{
	/*
	m_WorldMatrix.Identity();



	CVector3 TargetPosition;
	_pTargetWaypoint->GetWorldMatrix().GetPosition(TargetPosition);


	m_fYRotation += m_fTurnRate * _fDeltaTick;
	//D3DXMatrixRotationY(&m_WorldMatrix, m_fYRotation);


	CVector3 OrientationZ;
	m_WorldMatrix.GetOrientationZ(OrientationZ);
	OrientationZ.Normalise();


	OrientationZ *= m_fVelocity * _fDeltaTick;
	m_Position += OrientationZ;


	m_WorldMatrix.SetPosition(m_Position);
	*/
}




void
CActor::Draw(IRenderer& _rRenderer)
{
	//_rRenderer.SetWorldMatrix(m_WorldMatrix);
	//_rRenderer.DrawVertexBuffer(m_pDefaultEffect, m_pVertexBuffer);
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





void
CActor::Deinitialise()
{
	//Empty
}