//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Camera.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Camera_H__
#define __Camera_H__


// Library Includes


// Local Includes
#include "Math\WorldMatrix.h"
#include "Math\ViewMatrix.h"
#include "Math\ProjMatrix.h"
#include "Math\Plane.h"
#include "Library\Entity.h"


// Types


// Constants


// Prototypes
class CViewMatrix;
class CAABB;


class CCamera : public CEntity
{

	// Member Functions
public:


			 CCamera();
	virtual ~CCamera();


	virtual bool Initialise(uint _uiWidth, uint _uiHeight);


	bool IsInFrustum(const CAABB& _rAABoundingBox) const;


	// Inline Functions
	inline void GetView(CViewMatrix& _xrView);
	inline const CViewMatrix& GetView();


	inline const CProjMatrix& GetProjection() const;
	inline void GetProjection(CProjMatrix& _xrProjection) const;


protected:


	virtual void SetWorldDirty(bool _bDirty);


	void RegenerateView();
	void RegenerateFrustumPlanes();
	void GenerateProjection(uint _uiWidth, uint _uiHeight);


private:


	void Deinitialise();


	CCamera(const CCamera& _krCamera);
	CCamera& operator = (const CCamera& _krCamera);


	// Member Variables
protected:


private:


	CViewMatrix m_xView;
	CProjMatrix m_xProjection;


	CPlane m_FrustumPlane[CProjMatrix::MAX_FRUSTUMPLANE];


	bool m_bViewDirty;


};


#include "Camera.inl"


#endif //__Camera_H__