//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   QuadTree.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __QuadTree_H__
#define __QuadTree_H__


// Library Includes
#include <assert.h>
#include <vector>


// Local Includes
#include "Library\AABB.h"


// Types


// Prototypes


template <class TYPE>
class CQuadTree : public CAABB
{

	// Member Functions
public:


	 CQuadTree(uint _uiItemCapacity)
	 : m_uiItemCapacity(_uiItemCapacity)
	 {
		m_pChildrenTrees[0] = 0;
		m_pChildrenTrees[1] = 0;
		m_pChildrenTrees[2] = 0;
		m_pChildrenTrees[3] = 0;
	 }


	~CQuadTree() {};


	void InsertItem(float _fX, float _fZ, TYPE _Item)
	{
		// Has been subdivided
		if (m_pChildrenTrees[0] != 0)
		{
			// Hand item down to children
			for (ushort i = 0; i < CQuadTree::MAX_QTREE; ++ i)
			{
				// Point within child bounds
				if (m_pChildrenTrees[i]->IsWithinBounds(_fX, 0.0f, _fZ))
				{
					m_pChildrenTrees[i]->InsertItem(_fX, _fZ, _Item);
				}
			}
		}
		else
		{
			// Don't have enough space for item
			if (m_Items.size() >= m_uiItemCapacity)
			{
				Subdivide();


				InsertItem(_fX, _fZ, _Item);
			}
			else
			{
				m_Items.push_back(_Item);
			}
		}
	}


	// Inline Functions
	inline uint GetNumItems()
	{
		return (m_Items.size());
	}


	inline TYPE* GetItem(uint _uiIndex)
	{
		assert(_uiIndex < m_Items.size());


		return (&m_Items[_uiIndex]);
	}


protected:


	void Subdivide()
	{
		assert(m_pChildrenTrees[0] == 0);


		for (ushort i = 0; i < CQuadTree::MAX_QTREE; ++ i)
		{
			m_pChildrenTrees[i] = new CQuadTree<TYPE>(m_uiItemCapacity);
		}
		

		// Children half width
		const float kfChildHalfWidth = CAABB::m_fHalfWidth / 2.0f;


		// Children center positions
		CVector3 vNECenter = m_vCenter;
		vNECenter.AddX(kfChildHalfWidth);
		vNECenter.AddZ(kfChildHalfWidth);


		CVector3 vSECenter = m_vCenter;
		vNECenter.AddX(kfChildHalfWidth);
		vNECenter.AddZ(-kfChildHalfWidth);


		CVector3 vSWCenter = m_vCenter;
		vNECenter.AddX(-kfChildHalfWidth);
		vNECenter.AddZ(-kfChildHalfWidth);


		CVector3 vNWCenter = m_vCenter;
		vNECenter.AddX(-kfChildHalfWidth);
		vNECenter.AddZ(kfChildHalfWidth);


		// Set children bounds
		m_pChildrenTrees[CQuadTree::QTREE_NORTHEAST]->SetBounds(vNECenter, kfChildHalfWidth);
		m_pChildrenTrees[CQuadTree::QTREE_SOUTHEAST]->SetBounds(vSECenter, kfChildHalfWidth);
		m_pChildrenTrees[CQuadTree::QTREE_SOUTHWEST]->SetBounds(vSWCenter, kfChildHalfWidth);
		m_pChildrenTrees[CQuadTree::QTREE_NORTHWEST]->SetBounds(vNWCenter, kfChildHalfWidth);
	}


private:


	void Deinitialise();


	CQuadTree(const CQuadTree& _krQuadTree);
	CQuadTree& operator = (const CQuadTree& _krQuadTree);


	// Member Variables
protected:


	enum
	{
		INVALID_QTREE = -1,

		QTREE_NORTHEAST,
		QTREE_SOUTHEAST,
		QTREE_SOUTHWEST,
		QTREE_NORTHWEST,

		MAX_QTREE
	};


private:


	CQuadTree* m_pChildrenTrees[MAX_QTREE];


	uint m_uiItemCapacity;


	std::vector<TYPE> m_Items;


};


#endif //__QuadTree_H__