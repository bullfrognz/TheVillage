//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Entity.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Entity_H__
#define __Entity_H__


// Library Includes


// Local Includes
#include "Math\WorldMatrix.h"
#include "Math\Vector3.h"


// Types


// Constants


// Prototypes
class CWorldMatrix;


class CEntity
{

	// Member Functions
public:


			 CEntity();
	virtual ~CEntity();


	void TrackTarget(const CVector3& _kvrTarget);


	// Inline Functions
	inline void SetPositionX(float _fX);
	inline void SetPositionY(float _fY);
	inline void SetPositionZ(float _fZ);
	inline void SetPosition(const CVector3& _krPosition);
	inline void TranslateX(float _fX);
	inline void TranslateY(float _fY);
	inline void TranslateZ(float _fZ);
	inline void Translate(const CVector3& _krTranslation);


	inline void SetRotationX(float _fX);
	inline void SetRotationY(float _fY);
	inline void SetRotationZ(float _fZ);
	inline void SetRotation(const CVector3& _krRotation);
	inline void AddRotationX(float _fX);
	inline void AddRotationY(float _fY);
	inline void AddRotationZ(float _fZ);
	inline void AddRotation(const CVector3& _krRotation);


	inline void SetScaleX(float _fX);
	inline void SetScaleY(float _fY);
	inline void SetScaleZ(float _fZ);
	inline void SetScale(float _fX, float _fY, float _fZ);


	inline const CVector3& GetPosition() const;
	inline const CVector3& GetRotation() const;
	inline const CVector3& GetScale() const;
	inline void GetPosition(CVector3& _rPosition) const;
	inline void GetRotation(CVector3& _rRotation) const;
	inline void GetScale(CVector3& _rScale) const;


	inline void GetWorld(CWorldMatrix& _xrWorld);
	inline const CWorldMatrix& GetWorld();


protected:


	virtual void RegenerateWorld();


	// Inline Functions
	virtual inline void SetWorldDirty(bool _bDirty);


private:


	// Member Variables
protected:


private:


	CWorldMatrix m_xWorld;


	CVector3 m_vPosition;
	CVector3 m_vRotation;
	CVector3 m_vScale;
	CVector3 m_vTargetPosition;


	bool m_bWorldDirty;
	bool m_bTrackTarget;


};


#include "Entity.inl"


#endif //__Entity_H__