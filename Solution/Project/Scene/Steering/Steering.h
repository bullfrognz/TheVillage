//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Steering.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Steering_H__
#define __Steering_H__


// Library Includes
#include <vector>


// Local Includes
#include "Framework\Scene.h"


// Types


// Constants


// Prototypes
class IVertexBuffer;
class CWaypoint;
class CActor;


class CSteering : public CScene
{

	// Member Functions
public:


			 CSteering();
	virtual ~CSteering();


	virtual bool Initialise(IRenderer& _rRenderer, void* _pData = 0);
	virtual void Process(IRenderer& _rRenderer, float _fDeltaTick);
	virtual void Draw(IRenderer& _rRenderer);


	// Inline Functions


protected:


private:


	void Deinitialise();


	CSteering(const CSteering& _krSteering);
	CSteering& operator = (const CSteering& _krSteering);


	// Member Variables
protected:


private:


	CActor* m_pActor;


	std::vector<CWaypoint*> m_pWaypoints;


};


#endif //__Steering_H__