//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   Scene.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __IGFEB11_IG500_SCENE_H__
#define __IGFEB11_IG500_SCENE_H__


// Library Includes


// Local Includes


// Types
enum EScene
{
	SCENE_INVALID,

	SCENE_GAME,

	SCENE_MAX
};


// Constants


// Prototypes
class IRenderer;


class CScene
{

	// Member Functions
public:


	         CScene();
	virtual ~CScene();


	virtual bool Initialise(IRenderer& _rRenderer, void* _pData = 0) = 0;
	virtual void Process(IRenderer& _rRenderer, float _fDeltaTick) = 0;
	virtual void Draw(IRenderer& _rRenderer) = 0;



	// Inline Functions


protected:


private:


	void Deinitialise();


	CScene(const CScene& _krScene);
	CScene& operator = (const CScene& _krScene);


	// Member Variables
protected:


private:


};


#include "Scene.inl"


#endif //__IGFEB11_IG500_Scene_H__