//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   TerrainVertex.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// This Include
#include "TerrainVertex.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* TerrainVertex constructors
*
*---------------------------------------------------------------------------------------------------------------------------*/

CTerrainVertex::CTerrainVertex()
{
	memset(m_fTextureAlpha, 1, sizeof(float) * CTerrain::TEXTURES_MAX);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* TerrainVertex deconstructor
*
*---------------------------------------------------------------------------------------------------------------------------*/

CTerrainVertex::~CTerrainVertex()
{
	// Empty
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/