//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Skybox.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Skybox_H__
#define __Skybox_H__


// Library Includes


// Local Includes
#include "Math\Vector3.h"


// Types


// Prototypes
class IRenderer;
class CObject;
class IEffect;
class CCamera;


class CSkybox
{

	// Memer Types
public:


	enum EType
 	{
		INVALID_TYPE,

		TYPE_CLOUDLY,

		MAX_TYPE
	};


	// Member Functions
public:


	 CSkybox();
	~CSkybox();


	bool Initialise(IRenderer& _rRenderer, EType _eType);
	void Process(float _fDeltatick, CCamera& _rPlayerCamera);
	bool Draw(IRenderer& _rRenderer, CCamera& _rPlayerCamera);


	void SetBrightness(float _fRatio);


	// Inline Functions


protected:


private:


	bool InitialiseEffect(IRenderer& _rRenderer);
	bool InitialiseObject(IRenderer& _rRenderer);


	void Deinitialise();


	CSkybox(const CSkybox& _krSkybox);
	CSkybox& operator = (const CSkybox& _krSkybox);


	// Member Variables
protected:


private:


	CVector3 m_fDiffuse;


	CObject* m_pSkyboxObj;
	IEffect* m_pEffect;


};


#endif //__Skybox_H__