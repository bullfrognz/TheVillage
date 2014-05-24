//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Actor.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Actor_H__
#define __Actor_H__


// Library Includes


// Math Includes
#include "Math\WorldMatrix.h"
#include "Math\Vector3.h"


// Framework Includes


// Types


// Constants


// Prototypes


class CActor
{

	// Member Functions
public:


	 CActor();
	~CActor();


	bool Initialise(IRenderer& _rRenderer);
	void Process(float _fDeltaTick, CWaypoint* _pTargetWaypoint);
	void Draw(IRenderer& _rRenderer);


	// Inline Functions


protected:


private:


	void Deinitialise();


	CActor(const CActor& _krActor);
	CActor& operator = (const CActor& _krActor);


	// Member Variables
protected:


private:


	CWorldMatrix m_WorldMatrix;


	CVector3 m_Position;


	IDefaultEffect* m_pDefaultEffect;
	IVertexBuffer* m_pVertexBuffer;


	float m_fTurnRate;
	float m_fAcceleration;
	float m_fVelocity;


	float m_fYRotation;


};


#endif //__Actor_H__