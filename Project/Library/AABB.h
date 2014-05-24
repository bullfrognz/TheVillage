//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   AABB.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __AABB_H__
#define __AABB_H__


// Library Includes
#include <vector>


// Local Includes
#include "Math\Vector3.h"
#include "Framework\Effect.h"
#include "Framework\VertexBuffer.h"


// Types


// Prototypes


class CAABB
{

	// Member Types
public:


	enum ESide
	{
		INVALID_SIDE = -1,

		SIDE_TOP,
		SIDE_BOTTOM,
		SIDE_LEFT,
		SIDE_RIGHT,
		SIDE_FRONT,
		SIDE_BACK,

		MAX_SIDE
	};


	struct TVertex
	{
		static const IVertexBuffer::EPrimitiveType s_kePrimitiveType = IVertexBuffer::PRIMITIVETYPE_LINELIST;


		CVector3 m_vPosition;
	};


	// Member Functions
public:


	 CAABB();
	~CAABB();


	void SetBounds(const CVector3& _vCenterPosition, float _fHalfWidth, float _fHalfHeight);


	void GenerateVertices(std::vector<TVertex>& _rVertexData) const;


	bool IsWithinBounds(CVector3& _vrPosition) const;
	bool IsWithinBounds(float _fX, float _fY, float _fZ) const;


	static void GenerateEffectDesc(IEffect::TDesc& _trDescription);


	// Inline Functions
	inline void GetCenter(CVector3& _vrCenter) const;
	inline CVector3 GetCenter() const;

	inline float GetHalfWidth() const;
	inline float GetSideOffset(ESide _eSide) const;


protected:


private:


	void Deinitialise();


	CAABB(const CAABB& _krAABB);
	CAABB& operator = (const CAABB& _krAABB);


	// Member Variables
protected:


	CVector3 m_vCenter;
	
	
	float m_fHalfWidth;
	float m_fSideOffset[MAX_SIDE];


private:


};


#include "AABB.inl"


#endif //__AABB_H__