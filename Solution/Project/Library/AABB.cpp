//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   AABB.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <iostream>


// Local Includes


// This Include
#include "AABB.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CAABB constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CAABB::CAABB()
: m_fHalfWidth(0)
{
	memset(m_fSideOffset, 0, sizeof(float) * MAX_SIDE);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CAABB deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CAABB::~CAABB()
{
	Deinitialise();
}





void
CAABB::SetBounds(const CVector3& _vCenterPosition, float _fHalfWidth, float _fHalfHeight)
{
	const float kfCenterPosX = _vCenterPosition.GetX();
	const float kfCenterPosY = _vCenterPosition.GetY();
	const float kfCenterPosZ = _vCenterPosition.GetZ();


	m_fSideOffset[SIDE_RIGHT] = _vCenterPosition.GetX() + _fHalfWidth;
	m_fSideOffset[SIDE_TOP] = _vCenterPosition.GetY() + _fHalfHeight;
	m_fSideOffset[SIDE_FRONT] = _vCenterPosition.GetZ() + _fHalfWidth;

	m_fSideOffset[SIDE_LEFT] = _vCenterPosition.GetX() - _fHalfWidth;
	m_fSideOffset[SIDE_BOTTOM] = _vCenterPosition.GetY() - _fHalfHeight;
	m_fSideOffset[SIDE_BACK] = _vCenterPosition.GetZ() - _fHalfWidth;
}





void
CAABB::GenerateVertices(std::vector<TVertex>& _rVertexData) const
{
	TVertex tVertex[24];


	for (uint i = 0; i < 24; ++ i)
	{
		tVertex[i].m_vPosition = m_vCenter;
	}


	// Top
	tVertex[0].m_vPosition.Add(m_fSideOffset[SIDE_LEFT], m_fSideOffset[SIDE_TOP], m_fSideOffset[SIDE_FRONT]); // Front
	tVertex[1].m_vPosition.Add(m_fSideOffset[SIDE_RIGHT], m_fSideOffset[SIDE_TOP], m_fSideOffset[SIDE_FRONT]); // Front
	tVertex[2].m_vPosition.Add(m_fSideOffset[SIDE_LEFT], m_fSideOffset[SIDE_TOP], m_fSideOffset[SIDE_BACK]); // Back
	tVertex[3].m_vPosition.Add(m_fSideOffset[SIDE_RIGHT], m_fSideOffset[SIDE_TOP], m_fSideOffset[SIDE_BACK]); // Back
	tVertex[4].m_vPosition.Add(m_fSideOffset[SIDE_LEFT], m_fSideOffset[SIDE_TOP], m_fSideOffset[SIDE_FRONT]); // Left
	tVertex[5].m_vPosition.Add(m_fSideOffset[SIDE_LEFT], m_fSideOffset[SIDE_TOP], m_fSideOffset[SIDE_BACK]); // Left
	tVertex[6].m_vPosition.Add(m_fSideOffset[SIDE_RIGHT], m_fSideOffset[SIDE_TOP], m_fSideOffset[SIDE_FRONT]); // Right
	tVertex[7].m_vPosition.Add(m_fSideOffset[SIDE_RIGHT], m_fSideOffset[SIDE_TOP], m_fSideOffset[SIDE_BACK]); // Right


	// Bottom
	tVertex[8].m_vPosition.Add(m_fSideOffset[SIDE_LEFT], m_fSideOffset[SIDE_BOTTOM], m_fSideOffset[SIDE_FRONT]); // Front
	tVertex[9].m_vPosition.Add(m_fSideOffset[SIDE_RIGHT], m_fSideOffset[SIDE_BOTTOM], m_fSideOffset[SIDE_FRONT]); // Front
	tVertex[10].m_vPosition.Add(m_fSideOffset[SIDE_LEFT], m_fSideOffset[SIDE_BOTTOM], m_fSideOffset[SIDE_BACK]); // Back
	tVertex[11].m_vPosition.Add(m_fSideOffset[SIDE_RIGHT], m_fSideOffset[SIDE_BOTTOM], m_fSideOffset[SIDE_BACK]); // Back
	tVertex[12].m_vPosition.Add(m_fSideOffset[SIDE_LEFT], m_fSideOffset[SIDE_BOTTOM], m_fSideOffset[SIDE_FRONT]); // Left
	tVertex[13].m_vPosition.Add(m_fSideOffset[SIDE_LEFT], m_fSideOffset[SIDE_BOTTOM], m_fSideOffset[SIDE_BACK]); // Left
	tVertex[14].m_vPosition.Add(m_fSideOffset[SIDE_RIGHT], m_fSideOffset[SIDE_BOTTOM], m_fSideOffset[SIDE_FRONT]); // Right
	tVertex[15].m_vPosition.Add(m_fSideOffset[SIDE_RIGHT], m_fSideOffset[SIDE_BOTTOM], m_fSideOffset[SIDE_BACK]); // Right


	// Sides
	tVertex[16].m_vPosition.Add(m_fSideOffset[SIDE_LEFT], m_fSideOffset[SIDE_TOP], m_fSideOffset[SIDE_FRONT]); // Front left
	tVertex[17].m_vPosition.Add(m_fSideOffset[SIDE_LEFT], m_fSideOffset[SIDE_BOTTOM], m_fSideOffset[SIDE_FRONT]); // Front left
	tVertex[18].m_vPosition.Add(m_fSideOffset[SIDE_RIGHT], m_fSideOffset[SIDE_TOP], m_fSideOffset[SIDE_FRONT]); // Front right
	tVertex[19].m_vPosition.Add(m_fSideOffset[SIDE_RIGHT], m_fSideOffset[SIDE_BOTTOM], m_fSideOffset[SIDE_FRONT]); // Front right
	tVertex[20].m_vPosition.Add(m_fSideOffset[SIDE_LEFT], m_fSideOffset[SIDE_TOP], m_fSideOffset[SIDE_BACK]); // Back left
	tVertex[21].m_vPosition.Add(m_fSideOffset[SIDE_LEFT], m_fSideOffset[SIDE_BOTTOM], m_fSideOffset[SIDE_BACK]); // Back left
	tVertex[22].m_vPosition.Add(m_fSideOffset[SIDE_RIGHT], m_fSideOffset[SIDE_TOP], m_fSideOffset[SIDE_BACK]); // Back Right
	tVertex[23].m_vPosition.Add(m_fSideOffset[SIDE_RIGHT], m_fSideOffset[SIDE_BOTTOM], m_fSideOffset[SIDE_BACK]); // Back Right


	for (uint i = 0; i < 24; ++ i)
	{
		_rVertexData.push_back(tVertex[i]);
	}
}





bool
CAABB::IsWithinBounds(CVector3& _vrPoint) const
{
	bool bInBounds = false;


	if (_vrPoint.GetX() > m_fSideOffset[SIDE_LEFT] && _vrPoint.GetX() < m_fSideOffset[SIDE_RIGHT] &&
		_vrPoint.GetY() > m_fSideOffset[SIDE_BOTTOM] && _vrPoint.GetY() < m_fSideOffset[SIDE_TOP] &&
		_vrPoint.GetZ() > m_fSideOffset[SIDE_BACK] && _vrPoint.GetZ() < m_fSideOffset[SIDE_FRONT])
    {
        bInBounds = true;
    }


	return (bInBounds);
}





bool
CAABB::IsWithinBounds(float _fX, float _fY, float _fZ) const
{
	bool bInBounds = false;


	if (_fX > m_fSideOffset[SIDE_LEFT] && _fX < m_fSideOffset[SIDE_RIGHT] &&
		_fY > m_fSideOffset[SIDE_BOTTOM] && _fY < m_fSideOffset[SIDE_TOP] &&
		_fZ > m_fSideOffset[SIDE_BACK] && _fZ < m_fSideOffset[SIDE_FRONT])
    {
        bInBounds = true;
    }


	return (bInBounds);
}





void
CAABB::GenerateEffectDesc(IEffect::TDesc& _trDescription)
{
	IEffect::TDesc tEffectDesc;
	tEffectDesc.kcpEffectFile = "AABB.fx";


	// Helpers
	tEffectDesc.bTransformationHelper = true;


	// Input layout
	IEffect::TInput tPosition;
	tPosition.kcpName = "POSITION";
	tPosition.eVariableType = IEffect::VARIABLETYPE_FLOAT3;


	// Techniques
	IEffect::TTechnqiue tDefaultTechniqu;
	tDefaultTechniqu.kcpName = "DefaultTechnique";
	tDefaultTechniqu.aInputLayout.push_back(tPosition);


	tEffectDesc.aTechniques.push_back(tDefaultTechniqu);


	// Varaibles
	_trDescription = tEffectDesc;
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





void
CAABB::Deinitialise()
{
	//Empty
}