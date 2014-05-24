//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   TerrainVertex.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __TerrainVertex_H__
#define __TerrainVertex_H__


// Library Includes


// Local Includes
#include "Scene\Game\Terrain.h"
#include "Library\Vertex.h"
#include "Math\Vector3.h"
#include "Math\Vector2.h"


// Types


// Prototypes


class CTerrainVertex : public IVertex
{

	// Member Types
public:


	// Member Functions
public:


	 CTerrainVertex();
	~CTerrainVertex();


	// Inline Functions
	inline CVector3& Position();
	inline CVector3& Normal();
	inline CVector2& UV();


	inline float& TextureAlpha(uint _uiIndex);


protected:


private:


	// Member Variables
protected:


private:


	CVector3 m_vPosition;
	CVector3 m_vNormal;
	CVector2 m_vUV;


	float m_fTextureAlpha[CTerrain::TEXTURES_MAX];


};


#include "TerrainVertex.inl"


#endif //__TerrainVertex_H__