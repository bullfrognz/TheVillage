//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   Camera.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <D3DX10.h>


// Local Includes
#include "Math\WorldMatrix.h"
#include "Math\ViewMatrix.h"
#include "Library\AABB.h"


// This Include
#include "Camera.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CCamera constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CCamera::CCamera()
: m_bViewDirty(true)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CCamera deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CCamera::~CCamera()
{
	Deinitialise();
}





bool
CCamera::Initialise(uint _uiWidth, uint _uiHeight)
{
	GenerateProjection(_uiWidth, _uiHeight);


	return (true);
}





bool
CCamera::IsInFrustum(const CAABB& _rAABoundingBox) const
{
	bool bInFrustum = true;
	CVector3 vPlaneVertex;


	//Loop through all planes
	for (int iPlane = 0; iPlane < CProjMatrix::MAX_FRUSTUMPLANE; ++ iPlane)
	{
		// x-axis
		if(m_FrustumPlane[iPlane].GetA() < 0.0f)	// Which AABB vertex is furthest down (plane normals direction) the x axis
			vPlaneVertex.SetX( _rAABoundingBox.GetCenter().GetX() + _rAABoundingBox.GetSideOffset(CAABB::SIDE_LEFT) ); // min x plus tree positions x
		else
			vPlaneVertex.SetX( _rAABoundingBox.GetCenter().GetX() + _rAABoundingBox.GetSideOffset(CAABB::SIDE_RIGHT) ); // max x plus tree positions x

		// y-axis
		if(m_FrustumPlane[iPlane].GetB() < 0.0f)	// Which AABB vertex is furthest down (plane normals direction) the y axis
			vPlaneVertex.SetY( _rAABoundingBox.GetCenter().GetY() + _rAABoundingBox.GetSideOffset(CAABB::SIDE_BOTTOM) ); // min y plus tree positions y
		else
			vPlaneVertex.SetY( _rAABoundingBox.GetCenter().GetY() + _rAABoundingBox.GetSideOffset(CAABB::SIDE_TOP) ); // max y plus tree positions y
			
		// z-axis
		if(m_FrustumPlane[iPlane].GetC() < 0.0f)	// Which AABB vertex is furthest down (plane normals direction) the z axis
			vPlaneVertex.SetZ( _rAABoundingBox.GetCenter().GetZ() + _rAABoundingBox.GetSideOffset(CAABB::SIDE_BACK) ); // min z plus tree positions z
		else
			vPlaneVertex.SetZ( _rAABoundingBox.GetCenter().GetZ() + _rAABoundingBox.GetSideOffset(CAABB::SIDE_FRONT) ); // max z plus tree positions z

		// Now we get the signed distance from the AABB vertex that's furthest down the frustum planes normal,
		// and if the signed distance is negative, then the entire bounding box is behind the frustum plane, which means
		// that it should be culled
		if(D3DXPlaneDotCoord(reinterpret_cast<const D3DXPLANE*>(&m_FrustumPlane[iPlane]), reinterpret_cast<const D3DXVECTOR3*>(&vPlaneVertex)) < 0.0f) // + m_FrustumPlane[iPlane].d
		{
			bInFrustum = false;


			break;
		}
	}


	return(bInFrustum);
}





/********************************
            Protected
*********************************/





void
CCamera::SetWorldDirty(bool _bDirty)
{
	if (_bDirty)
	{
		m_bViewDirty = true;
	}


	CEntity::SetWorldDirty(_bDirty);
}





void
CCamera::RegenerateView()
{
	CEntity::GetWorld().Inverse(m_xView);
	RegenerateFrustumPlanes();


	m_bViewDirty = false;
}





void
CCamera::RegenerateFrustumPlanes()
{
	for (uint i = 0; i < CProjMatrix::MAX_FRUSTUMPLANE; ++ i)
	{
		m_xProjection.GenerateFrustumPlane(m_xView, static_cast<CProjMatrix::EFrustumPlane>(i), m_FrustumPlane[i]);
	}
}





void
CCamera::GenerateProjection(uint _uiWidth, uint _uiHeight)
{
	float fAspectRatio = float(_uiWidth) / float(_uiHeight);
	m_xProjection.SetPerspectiveFovLH(1.047f, fAspectRatio, 0.1f, 4000.0f);


	RegenerateFrustumPlanes();
}





/********************************
            Private
*********************************/





void
CCamera::Deinitialise()
{
	//Empty
}