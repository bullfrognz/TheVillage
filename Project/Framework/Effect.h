//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Effect.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Effect_H__
#define __Effect_H__


// Library Includes
#include <string>
#include <vector>


// Local Includes
#include "Library\Vertex.h"


// Types


// Constants


// Prototypes
class IRenderer;
class CMatrix;
class CVector3;
class CVector4;
class CLight;
class ITexture;


class IEffect
{

	// Member Types
public:


	enum EDefines
	{
		MAX_LIGHTS = 8,
		MAX_TEXTURES = 8
	};


	enum EVariableType
	{
		INVALID_VARIABLETYPE = -1,

		VARIABLETYPE_BOOL,
		VARIABLETYPE_UINT,
		VARIABLETYPE_FLOAT1,
		VARIABLETYPE_FLOAT2,
		VARIABLETYPE_FLOAT3,
		VARIABLETYPE_FLOAT4,

		MAX_VARIABLETYPE
	};


	enum EHelperVar
	{
		HELPERVAR_FOG_STARTDISTANCE,	// Float
		HELPERVAR_FOG_DENSITY,			// Float
		HELPERVAR_FOG_COLOUR,			// Vector4
	};


	struct TInput
	{
		TInput::TInput()
		: kcpName(0)
		, eVariableType(INVALID_VARIABLETYPE)
		, uiSemanticIndex(0)
		, uiBindSlot(0)
		{ /* Empty */ }


		const char* kcpName;

		EVariableType eVariableType;

		uint uiSemanticIndex;
		uint uiBindSlot;
	};


	struct TTechnqiue
	{
		TTechnqiue::TTechnqiue()
		: kcpName(0)
		, uiStatesResetPassId(-1)
		{ /* Empty */ }


		const char* kcpName;
		uint uiStatesResetPassId;

		std::vector<TInput> aInputLayout;
	};


	struct TDesc
	{
		TDesc::TDesc()
		: kcpEffectFile(0)
		, bTransformationHelper(false)
		, bLightHelper(false)
		, bTextureHelper(false)
		, bShadowHelper(false)
		, bFogHelper(false)
		{ /* Empty */ }


		const char* kcpEffectFile;

		bool bTransformationHelper;
		bool bLightHelper;
		bool bTextureHelper;
		bool bShadowHelper;
		bool bFogHelper;

		std::vector<TTechnqiue> aTechniques;
		std::vector<std::string> aVariableNames;
	};


	// Member Functions
public:


			 IEffect() {};
	virtual ~IEffect() {};


	virtual bool SetVariable(const char* _kcpName, const CMatrix& _kxrVariable) = 0;
	virtual bool SetVariable(const char* _kcpName, const CVector3& _kvrVariable) = 0;
	virtual bool SetVariable(const char* _kcpName, const CVector4& _kvrVariable) = 0;
	virtual bool SetVariable(const char* _kcpName, float _fVariable) = 0;
	virtual bool SetVariable(const char* _kcpName, uint _uiVariable) = 0;
	virtual bool SetVariable(const char* _kcpName, int _iVariable) = 0;
	virtual bool SetVariable(const char* _kcpName, bool _bVariable) = 0;


	virtual bool SetTransformations(const CMatrix& _kxrWorld, const CMatrix& _kxrView, const CMatrix& _kxrProjection) = 0;
	virtual bool SetLights(CLight** _ppLights, uint _uiNumLights, const CVector3& _kvrCameraPosition) = 0;
	virtual bool SetTextures(ITexture** _ppTextures, uint _uiNumTextures) = 0;


	virtual bool GetVariable(const char* _kcpName, CMatrix& _rVariable) = 0;
	virtual bool GetVariable(const char* _kcpName, float& _frVariable) = 0;
	virtual bool GetVariable(const char* _kcpName, int& _irVariable) = 0;


	// Inline Functions


protected:


private:


	IEffect(const IEffect& _krIEffect);
	IEffect& operator = (const IEffect& _krIEffect);


	// Member Variables
protected:


private:


};


#endif //__Effect_H__