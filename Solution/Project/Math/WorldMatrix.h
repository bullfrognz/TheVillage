//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   WorldMatrix.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __IGFEB11_IG500_WORLDMATRIX_H__
#define __IGFEB11_IG500_WORLDMATRIX_H__


// Library Includes


// Local Includes
#include "Math\Vector3.h"
#include "Math\Matrix.h"


// Types


// Constants


// Prototypes


class CWorldMatrix : public CMatrix
{

	// Member Functions
public:


	 CWorldMatrix();
	~CWorldMatrix();


	void SetScale(float _fX, float _fY, float _fZ);
	void SetOrientation(float _fPitch, float _fRoll, float _fYaw);
	void LookAt(const CVector3& _kvrTargetPosition);


	// Inline Functions
	inline void SetPositionX(float _fX);
	inline void SetPositionY(float _fY);
	inline void SetPositionZ(float _fZ);
	inline void SetPosition(float _fX, float _fY, float _fZ);
	inline void SetPosition(const CVector3& _kv3rVector);


	inline float GetPositionX() const;
	inline float GetPositionY() const;
	inline float GetPositionZ() const;
	inline void  GetPosition(CVector3& _rPosition) const;


	// Position Translation
	inline void GetOrientationX(CVector3& _rOrientationX) const;
	inline void GetOrientationY(CVector3& _rOrientationY) const;
	inline void GetOrientationZ(CVector3& _rOrientationZ) const;


	inline CVector3 GetOrientationX() const;
	inline CVector3 GetOrientationY() const;
	inline CVector3 GetOrientationZ() const;


protected:


private:


	void Deinitialise();


	// Member Variables
protected:


private:


};


#include "WorldMatrix.inl"


#endif //__IGFEB11_IG500_WORLDMATRIX_H__