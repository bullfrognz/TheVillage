//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Cube.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Cube_H__
#define __Cube_H__


// Library Includes


// Local Includes
#include "Framework\Entity.h"


// Types


// Prototypes
class IRenderer;
class IVertexBuffer;
class IIndexBuffer;
class CViewMatrix;
class CProjMatrix;
class CCamera;


class CCube : public CEntity
{

	// Member Types


	struct TVertex
	{
		CVector3 mPosition;
		CVector3 mNormal;
	};


	// Member Functions
public:


	 CCube();
	~CCube();


	bool Initialise(IRenderer& _rRenderer);


	bool Process(float _fDeltaTick);


	bool DrawShadow(IRenderer& _rRenderer, CCamera& _rActiveCamera, std::vector<CLight*>& _rActiveLights);
	bool Draw(IRenderer& _rRenderer, CCamera& _rActiveCamera, std::vector<CLight*>& _rActiveLights);


	// Inline Functions


protected:


private:


	bool InitialiseEffectFile(IRenderer& _rRenderer);
	bool InitialiseVertexBuffer(IRenderer& _rRenderer);
	bool InitialiseIndexBuffer(IRenderer& _rRenderer);


	bool FillVertexBuffer();
	bool FillIndexBuffer();


	void Deinitialise();


	CCube(const CCube& _krCube);
	CCube& operator = (const CCube& _krCube);


	// Member Variables
protected:


private:


	IEffect* m_pEffect;
	IVertexBuffer* m_pVertexBuffer;
	IIndexBuffer* m_pIndexBuffer;


};


#endif //__Cube_H__