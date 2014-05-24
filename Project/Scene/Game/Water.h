//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Water.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Water_H__
#define __Water_H__


// Library Includes


// Local Includes
#include "Math\Vector3.h"
#include "Library\Entity.h"


// Types
#include "Defines\DataTypes.h"


// Prototypes
class IRenderer;
class IEffect;
class IVertexBuffer;
class IIndexBuffer;
class CCamera;


class CWater : public CEntity
{

	// Member Types


	struct TVertex
	{
		CVector3 vPosition;
		float fU;
		float fV;
		bool  bDirection;
	};


	// Member Functions
public:


	 CWater();
	~CWater();


	bool Initialise(IRenderer& _rRenderer, uint _uiWidth, uint _uiLength);
	void Process(float _fDeltatick);
	bool Draw(IRenderer& _rRenderer, CCamera& _rPlayerCamera);


	void SetBrightness(float _fRatio)
	{
		m_pEffect->SetVariable("g_fBrightness", _fRatio);
	}


	// Inline Functions


protected:


	bool GenerateVertices(TVertex*& _tprVertices, uint& _rNumVertices);
	void GenerateIndices(std::vector<uint>& _arIndices);


private:


	bool InitialiseEffect(IRenderer& _rRenderer);
	bool InitialiseVertexBuffer(IRenderer& _rRenderer);
	bool InitialiseIndexBuffer(IRenderer& _rRenderer);


	void Deinitialise();


	CWater(const CWater& _krWater);
	CWater& operator = (const CWater& _krWater);


	// Member Variables
protected:


private:


	IEffect* m_pEffect;
	IVertexBuffer* m_pVertexBuffer;
	IIndexBuffer* m_pIndexBuffer;
	ITexture* m_pTexture;


	float m_fHalfCycleTime;
	float m_fTime;


	uint m_uiWidth;
	uint m_uiLength;


	bool m_bGoingUp;


};


#endif //__Water_H__