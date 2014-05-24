//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Waypoint.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Waypoint_H__
#define __Waypoint_H__


// Library Includes


// Local Includes
#include "Math\WorldMatrix.h"


// Types


// Constants


// Prototypes
class IRenderer;
class IVertexBuffer;
class IDefaultEffect;


class CWaypoint
{

	// Member Functions
public:


	 CWaypoint();
	~CWaypoint();


	bool Initialise(IRenderer& _rRenderer);
	void Draw(IRenderer& _rRenderer);


	// Inline Functions
	inline void SetPosition(float _fX, float _fZ);


	inline CWorldMatrix& GetWorldMatrix();


protected:


private:


	void Deinitialise();


	CWaypoint(const CWaypoint& _krWaypoint);
	CWaypoint& operator = (const CWaypoint& _krWaypoint);


	// Member Variables
protected:


private:


	CWorldMatrix m_WorldMatrix;


	IDefaultEffect* m_pDefaultEffect;
	IVertexBuffer* m_pVertexBuffer;


	float m_fPositionX;
	float m_fPositionZ;


};


#include "Waypoint.inl"


#endif //__Waypoint_H__