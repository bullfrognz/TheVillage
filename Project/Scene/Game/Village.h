//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Village.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Village_H__
#define __Village_H__


// Library Includes


// Local Includes


// Types


// Prototypes
class IEffect;
class CObject;
class CWindmill;
class CTerrain;
class CWater;


class CVillage
{

	// Member Functions
public:


	 CVillage();
	~CVillage();


	bool Initialise(IRenderer& _rRenderer);
	void Process(float _fDeltaTick, CTerrain& _rTerrain);
	
	
	bool DrawUnlit(IRenderer& _rRenderer, CCamera& _rPlayerCamera);
	bool DrawAmbient(IRenderer& _rRenderer, CCamera& _rPlayerCamera, std::vector<CLight*>& _rActiveLights);
	bool DrawShadows(IRenderer& _rRenderer, CCamera& _rPlayerCamera, std::vector<CLight*>& _rActiveLights);
	bool DrawLit(IRenderer& _rRenderer, CCamera& _rPlayerCamera, std::vector<CLight*>& _rActiveLights);


	// Inline Functions


protected:


	bool Draw(IRenderer& _rRenderer, CCamera& _rPlayerCamera, std::vector<CLight*>& _rActiveLights);


	void SetupPositions(CTerrain& _rTerrain);


private:


	bool InitialiseEffect(IRenderer& _rRenderer);
	bool InitialiseObjects(IRenderer& _rRenderer);


	void Deinitialise();


	CVillage(const CVillage& _krVillage);
	CVillage& operator = (const CVillage& _krVillage);


	// Member Variables
protected:


private:


	IEffect* m_pEffect;
	CObject* m_pBarn;
	CObject* m_pPeir;
	CObject* m_pShop;
	CObject* m_pTableBasic;
	CObject* m_pWell;
	CObject* m_pWoodenCart2;
	CObject* m_pHouse;
	CObject* m_pCastleGate;
	CObject* m_pCathedral;
	CWindmill* m_pWindmill;
	CWater* m_pWater;


	bool m_bPositionsSet;


};


#endif //__Village_H__