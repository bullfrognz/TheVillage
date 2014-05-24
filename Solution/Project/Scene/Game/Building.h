//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Building.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Building_H__
#define __Building_H__


// Library Includes
#include <vector>


// Local Includes
#include "Library\Entity.h"
#include "Framework\Effect.h"


// Types


// Prototypes
class IRenderer;
class IEffect;
class CObject;
class CCamera;


class CBuilding : public CEntity
{

	// Member Functions
public:


	 CBuilding();
	~CBuilding();


	bool Initialise(IRenderer& _rRenderer, const char* _kcpModelFile);


	bool DrawShadow(IRenderer& _rRenderer, CCamera& _rActiveCamera, std::vector<CLight*>& _rActiveLights);
	bool Draw(IRenderer& _rRenderer, CCamera& _rActiveCamera, std::vector<CLight*>& _rActiveLights);


	// Inline Functions


protected:


	void GenerateInputLayout(IEffect::TInput*& _prInputLayout, uint& _uirNumInputs);


private:


	bool InitialiseModel(IRenderer& _rRenderer, const char* _kcpModelFile);
	bool InitialiseEffectFile(IRenderer& _rRenderer);


	void Deinitialise();


	CBuilding(const CBuilding& _krBuilding);
	CBuilding& operator = (const CBuilding& _krBuilding);


	// Member Variables
protected:


private:


	IEffect* m_pEffect;
	CObject* m_pStructure;


};


#endif //__Building_H__