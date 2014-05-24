//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   Game.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Game_H__
#define __Game_H__


// Library Includes


// Local Includes
#include "Framework\Light.h"


// This Inclues
#include "Framework\Scene.h"
#include "Framework\Observer.h"


// Types


// Constants


// Prototypes
class CFPCamera;
class CTerrain;
class CBuilding;
class CSkybox;
class CDayNightCycle;
class CVillage;
class IText;


class CGame : public CScene, public IObserver
{

	// Member Functions
public:


			 CGame();
	virtual ~CGame();


	virtual bool Initialise(IRenderer& _rRenderer, void* _pData = 0);
	virtual void Process(IRenderer& _rRenderer, float _fDeltaTick);
	virtual void Draw(IRenderer& _rRenderer);


	virtual void NotifyMessage(uint _uiSubject, void* _pDispatcher);


	// Inline Functions


protected:


	void DrawUnlit(IRenderer& _rRenderer);
	void DrawAmbient(IRenderer& _rRenderer);
	void DrawShadows(IRenderer& _rRenderer);
	void DrawLit(IRenderer& _rRenderer, bool _bWithoutStates);


	void ProcessCameras(float _fDeltaTick);
	void ProcessSkybox(float _fDeltaTick);
	void UpdateLights();


private:


	bool InitialiseCameras(IRenderer& _rRenderer);
	bool InitialiseTerrain(IRenderer& _rRenderer);
	bool InitialiseAssets(IRenderer& _rRenderer);
	bool IntiialiseInfoText(IRenderer& _rRenderer);
	bool InitialiseLights();


	void Deinitialise();


	CGame(const CGame& _krGame);
	CGame& operator = (const CGame& _krGame);


	// Member Variables
protected:


private:


	CFPCamera* m_pPlayerCamera;
	CFPCamera* m_pDebugCamera;
	CSkybox* m_pSkybox;
	CTerrain* m_pTerrain;
	CDayNightCycle* m_pDayNightCycle;
	CVillage* m_pVillage;
	IText* m_pInfo;


	bool m_bDrawShadows;


	std::vector<CLight*> m_pLights;


};


#endif //__Game_H__