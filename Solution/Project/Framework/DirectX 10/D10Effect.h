//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   D10Effect.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __D10Effectss_2_H__
#define __D10Effectss_2_H__


// Library Includes
#include <map>
#include <string>


// Local Includes
#include "Defines\DataTypes.h"


// This includes
#include "Framework\Effect.h"


// Types


// Prototypes
struct ID3D10Effect;
struct ID3D10EffectTechnique;
struct ID3D10InputLayout;
struct ID3D10EffectMatrixVariable;

class CD10Renderer;
class CLight;


class CD10Effect : public IEffect
{

	// Member Types
public:


	struct TEffectTechnique
	{
		ID3D10EffectTechnique* pD10Technique;
		ID3D10InputLayout* pD10InputLayout;
		uint uiStatesResetPassId;
	};


	// Member Functions
public:


			 CD10Effect();
	virtual ~CD10Effect();


	bool Initialise(CD10Renderer& _rD10Renderer, const IEffect::TDesc& _ktrDescription);


	virtual bool SetVariable(const char* _kcpName, const CMatrix& _kxrVariable);
	virtual bool SetVariable(const char* _kcpName, const CVector3& _kvrVariable);
	virtual bool SetVariable(const char* _kcpName, const CVector4& _kvrVariable);
	virtual bool SetVariable(const char* _kcpName, float _fVariable);
	virtual bool SetVariable(const char* _kcpName, uint _uiVariable);
	virtual bool SetVariable(const char* _kcpName, int _iVariable);
	virtual bool SetVariable(const char* _kcpName, bool _bVariable);


	virtual bool SetTransformations(const CMatrix& _kxrWorld, const CMatrix& _kxrView, const CMatrix& _kxrProjection);
	virtual bool SetLights(CLight** _ppLights, uint _uiNumLights, const CVector3& _kvrCameraPosition);
	virtual bool SetTextures(ITexture** _ppTextures, uint _uiNumTextures);


	virtual bool GetVariable(const char* _kcpName, CMatrix& _rVariable);
	virtual bool GetVariable(const char* _kcpName, float& _frVariable);
	virtual bool GetVariable(const char* _kcpName, int& _irVariable);


	bool GetTechnique(const char* _kcpName, TEffectTechnique& _trEffectTechnique);


	// Inline Functions


protected:


	bool RegisterTechnique(CD10Renderer& _rD10Renderer, const TTechnqiue& _ktrTechnique);
	bool RegisterVariable(const char* _kcpName);
	bool RegisterTransformationHelper();
	bool RegisterLightHelper();
	bool RegisterTextureHelper();
	bool RegisterShadowHelper();
	bool RegisterFogHelper();


	bool CompileInputLayout(const std::vector<TInput>& _karInputLayout, std::vector<D3D10_INPUT_ELEMENT_DESC>& _rInputElementDescs);


private:


	bool InitialiseEffect(CD10Renderer& _rD10Renderer, const IEffect::TDesc& _ktrDescription);
	bool InitialiseTechniques(CD10Renderer& _rD10Renderer, const IEffect::TDesc& _ktrDescription);
	bool InitialiseVariables(const IEffect::TDesc& _ktrDescription);
	bool InitialiseHelpers(const IEffect::TDesc& _ktrDescription);


	void Deinitialise();


	CD10Effect(const CD10Effect& _krD10Effect);
	CD10Effect& operator = (const CD10Effect& _krD10Effect);


	// Member Variables
protected:


private:


	char* m_cpFile;


	ID3D10Effect* m_pD10Effect;


	bool m_bUsesLightHelper;
	bool m_bUsesTextureHelper;


	std::map<std::string, ID3D10EffectVariable*> m_Variables;			// <VariableName, * >
	std::map<std::string, TEffectTechnique> m_Techniques;				// <TechniqueName, * >


};


#endif //__D10Effectss__H__