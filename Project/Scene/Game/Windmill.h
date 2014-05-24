//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Windmill.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Windmill_H__
#define __Windmill_H__


// Library Includes
#include <vector>


// Local Includes


// Types


// Prototypes
class IRenderer;
class CObject;


class CWindmill
{

	// Member Functions
public:


	 CWindmill();
	~CWindmill();


	bool Initialise(IRenderer& _rRenderer);
	void Process(float _fDeltatick);


	bool Draw(IRenderer& _rRenderer, CCamera& _rPlayerCamera, IEffect& _rEffect);


	void SetPosition(float _fX, float _fY, float _fZ);
	void SetPosition(const CVector3& _kvrPosition);
	void SetPositionY(float _fY);


	const CVector3& GetPosition();


	// Inline Functions


protected:


private:


	void Deinitialise();


	CWindmill(const CWindmill& _krWindmill);
	CWindmill& operator = (const CWindmill& _krWindmill);


	// Member Variables
protected:


private:


	CObject* m_pBase;
	CObject* m_pBlade;


};


#endif //__Windmill_H__