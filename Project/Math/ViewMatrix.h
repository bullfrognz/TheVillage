//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   ViewMatrix.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __IGFEB11_IG500_VIEWMATRIX_H__
#define __IGFEB11_IG500_VIEWMATRIX_H__


// Library Includes


// Local Includes
#include "Math\Vector3.h"
#include "Math\Matrix.h"


// Types


// Constants


// Prototypes


class CViewMatrix : public CMatrix
{

	// Member Functions
public:


	 CViewMatrix();
	~CViewMatrix();


	void LookAtLH(const CVector3& _krPosition, const CVector3& _krTarget);


	// Inline Functions
	inline void GetLookAt(CVector3& _rLookAt) const;
	inline void GetRight(CVector3& _rRight) const;
	inline void GetUp(CVector3& _rUp) const;


	inline CVector3 GetLookAt() const;
	inline CVector3 GetRight() const;
	inline CVector3 GetUp() const;


protected:


private:


	void Deinitialise();


	// Member Variables
protected:


private:


};


#include "ViewMatrix.inl"


#endif //__IGFEB11_IG500_VIEWMATRIX_H__