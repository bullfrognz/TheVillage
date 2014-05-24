//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Object.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Object_H__
#define __Object_H__


// Library Includes


// Local Includes
#include "Library\Entity.h"
#include "Library\Model.h"


// Types


// Prototypes
class CModel;
class IEffect;
class CCamera;


class CObject : public CEntity
{

	// Member Functions
public:


	 CObject();
	~CObject();


	bool Initialise(IRenderer& _rRenderer, const char* _kcpModelFile, const std::vector<CModel::EInputType>& _karInputLayout);


	bool Draw(IRenderer& _rRenderer, IEffect& _rEffect);


	// Inline Functions


protected:


private:


	void Deinitialise();


	CObject(const CObject& _krObject);
	CObject& operator = (const CObject& _krObject);


	// Member Variables
protected:


private:


	CModel* m_pModel;


};


#endif //__Object_H__