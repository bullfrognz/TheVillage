//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   Entity.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <cmath>


// Local Includes
#include "Math\WorldMatrix.h"
#include "Utilities\MathUtilities.h"
#include "Math\ViewMatrix.h"


// This Include
#include "Entity.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CEntity constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CEntity::CEntity()
: m_vScale(1.0f, 1.0f, 1.0f)
, m_bWorldDirty(true)
, m_bTrackTarget(false)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CEntity deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CEntity::~CEntity()
{
	// Empty
}





void
CEntity::TrackTarget(const CVector3& _kvrTarget)
{
	m_vTargetPosition = _kvrTarget;
	m_bTrackTarget = true;
	m_bWorldDirty = true;
}





/********************************
            Protected
*********************************/





void
CEntity::RegenerateWorld()
{
	m_xWorld.Identity();


	if (m_bTrackTarget)
	{
		CMatrix xRotation;


		CVector3 vSelfPosition;
		GetPosition(vSelfPosition);


		CViewMatrix xView;
		xView.LookAtLH(vSelfPosition, m_vTargetPosition);
		xView.Inverse(xRotation);


		// Scale
		if (m_vScale.GetX() != 1.0f ||
			m_vScale.GetY() != 1.0f || 
			m_vScale.GetZ() != 1.0f)
		{
			m_xWorld.SetScale(m_vScale.GetX(), m_vScale.GetY(), m_vScale.GetZ());
		}


		m_xWorld *= xRotation;


		// Translation
		m_xWorld.SetPosition(m_vPosition);
	}
	else
	{
		// Scale
		if (m_vScale.GetX() != 1.0f ||
			m_vScale.GetY() != 1.0f || 
			m_vScale.GetZ() != 1.0f)
		{
			m_xWorld.SetScale(m_vScale.GetX(), m_vScale.GetY(), m_vScale.GetZ());
		}


		// Rotation
		if (m_vRotation.GetX() != 0.0f ||
			m_vRotation.GetY() != 0.0f || 
			m_vRotation.GetZ() != 0.0f)
		{
			m_xWorld.SetOrientation(m_vRotation.GetX(), m_vRotation.GetZ(), m_vRotation.GetY());
		}


		// Translation
		m_xWorld.SetPosition(m_vPosition);


		m_bWorldDirty = false;
	}
}






/********************************
            Private
*********************************/