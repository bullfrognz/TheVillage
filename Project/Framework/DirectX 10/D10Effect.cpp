//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   D10Effect.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <assert.h>
#include <D3DX10.h>
#include <string>


// Local Includes
#include "Defines\Macros.h"
#include "Math\Vector4.h"
#include "Library\Vertex.h"
#include "Framework\DirectX 10\D10Renderer.h"
#include "Framework\DirectX 10\D10Texture.h"
#include "Framework\Light.h"
#include "Utilities\StrUtilities.h"


// This Include
#include "D10Effect.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CD10Effect constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD10Effect::CD10Effect()
: m_cpFile(0)
, m_pD10Effect(0)
, m_bUsesLightHelper(0)
, m_bUsesTextureHelper(0)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CD10Effect deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD10Effect::~CD10Effect()
{
	Deinitialise();
}





bool
CD10Effect::Initialise(CD10Renderer& _rD10Renderer, const IEffect::TDesc& _ktrDescription)
{
	if (_ktrDescription.kcpEffectFile != 0)
	{
		StrUtilities::Copy(_ktrDescription.kcpEffectFile, m_cpFile);
	}


	FW_VALIDATE(InitialiseEffect(_rD10Renderer, _ktrDescription))
	FW_VALIDATE(InitialiseTechniques(_rD10Renderer, _ktrDescription))
	FW_VALIDATE(InitialiseVariables(_ktrDescription))
	FW_VALIDATE(InitialiseHelpers(_ktrDescription))


	return (true);
}





bool
CD10Effect::SetVariable(const char* _kcpName, const CMatrix& _kxrVariable)
{
	std::map<std::string, ID3D10EffectVariable*>::iterator VariableContainer = m_Variables.find(_kcpName);
	bool bReturn = true;


	if (VariableContainer != m_Variables.end())
	{
		const float* kfpMatrix = reinterpret_cast<const float*>(&_kxrVariable);


		(*VariableContainer).second->AsMatrix()->SetMatrix(const_cast<float*>(kfpMatrix));
	}
	else
	{
		// Variable not found
		assert(false);
		bReturn = false;
	}


	return (bReturn);
}





bool
CD10Effect::SetVariable(const char* _kcpName, const CVector3& _kvrVariable)
{
	return (SetVariable(_kcpName, CVector4(_kvrVariable)));
}





bool
CD10Effect::SetVariable(const char* _kcpName, const CVector4& _kvrVariable)
{
	std::map<std::string, ID3D10EffectVariable*>::iterator VariableContainer = m_Variables.find(_kcpName);
	bool bReturn = true;


	if (VariableContainer != m_Variables.end())
	{
		const float* kfpMatrix = reinterpret_cast<const float*>(&_kvrVariable);


		(*VariableContainer).second->AsVector()->SetFloatVector(const_cast<float*>(kfpMatrix));
	}
	else
	{
		// Variable not found
		assert(false);
		bReturn = false;
	}


	return (bReturn);
}





bool
CD10Effect::SetVariable(const char* _kcpName, float _fVariable)
{
	std::map<std::string, ID3D10EffectVariable*>::iterator VariableContainer = m_Variables.find(_kcpName);
	bool bReturn = true;


	if (VariableContainer != m_Variables.end())
	{
		(*VariableContainer).second->AsScalar()->SetFloat(_fVariable);
	}
	else
	{
		// Variable not found
		assert(false);
		bReturn = false;
	}


	return (bReturn);
}





bool
CD10Effect::SetVariable(const char* _kcpName, uint _uiVariable)
{
	return (SetVariable(_kcpName, static_cast<int>(_uiVariable)));
}





bool
CD10Effect::SetVariable(const char* _kcpName, int _iVariable)
{
	std::map<std::string, ID3D10EffectVariable*>::iterator VariableContainer = m_Variables.find(_kcpName);
	bool bReturn = true;


	if (VariableContainer != m_Variables.end())
	{
		(*VariableContainer).second->AsScalar()->SetInt(_iVariable);
	}
	else
	{
		// Variable not found
		assert(false);
		bReturn = false;
	}


	return (bReturn);
}





bool
CD10Effect::SetVariable(const char* _kcpName, bool _bVariable)
{
	std::map<std::string, ID3D10EffectVariable*>::iterator VariableContainer = m_Variables.find(_kcpName);
	bool bReturn = true;


	if (VariableContainer != m_Variables.end())
	{
		(*VariableContainer).second->AsScalar()->SetBool(_bVariable);
	}
	else
	{
		// Variable not found
		assert(false);
		bReturn = false;
	}


	return (bReturn);
}





bool
CD10Effect::SetTransformations(const CMatrix& _kxrWorld, const CMatrix& _kxrView, const CMatrix& _kxrProjection)
{
	SetVariable("g_xWorld", _kxrWorld);
	SetVariable("g_xView", _kxrView);
	SetVariable("g_xProjection", _kxrProjection);


	CMatrix xWorldViewProj(_kxrWorld);
	xWorldViewProj *= _kxrView;
	xWorldViewProj *= _kxrProjection;


	SetVariable("g_xWorldViewProjection", xWorldViewProj);


	return (true);
}





bool
CD10Effect::SetLights(CLight** _ppLights, uint _uiNumLights, const CVector3& _kvrCameraPosition)
{
	std::map<std::string, ID3D10EffectVariable*>::iterator VariableContainer = m_Variables.find("g_tLight");
	uint uiNumValidLights = 0;
	bool bReturn = true;


	if (VariableContainer != m_Variables.end())
	{
		for (uint i = 0; i < IEffect::MAX_LIGHTS && uiNumValidLights < _uiNumLights; ++ i)
		{
			if (_ppLights[i] != 0)
			{
				(*VariableContainer).second->GetElement(i)->SetRawValue(_ppLights[i], 0, sizeof(CLight));


				++ uiNumValidLights;
			}
			else
			{
				// Don't set light
			}
		}


		FW_VALIDATE(SetVariable("g_iNumLights", uiNumValidLights));


		if (uiNumValidLights > 0)
		{
			FW_VALIDATE(SetVariable("g_vCameraPosition", _kvrCameraPosition));
		}
		else
		{
			// No point sending down camera position
		}
	}
	else
	{
		// Variable not found
		assert(false);
		bReturn = false;
	}


	return (bReturn);
}





bool
CD10Effect::SetTextures(ITexture** _ppTextures, uint _uiNumTextures)
{
	std::map<std::string, ID3D10EffectVariable*>::iterator ResourcesContainer = m_Variables.find("g_TextureResources");
	uint uiNumValidTextures = 0;
	bool bReturn = true;


	if (ResourcesContainer == m_Variables.end())
	{
		// Effect file has not included texture helper effect file
		assert(false);
		bReturn = false;
	}
	else
	{
		for (uint i = 0; i < IEffect::MAX_TEXTURES && uiNumValidTextures < _uiNumTextures; ++ i)
		{
			if (_ppTextures[i] != 0)
			{
				CD10Texture* pD10Texture = static_cast<CD10Texture*>(_ppTextures[i]);
				ID3D10ShaderResourceView* pShaderResourceView = pD10Texture->GetResourceView();


				(*ResourcesContainer).second->GetElement(i)->AsShaderResource()->SetResource(pShaderResourceView);


				++ uiNumValidTextures;
			}
			else
			{
				(*ResourcesContainer).second->GetElement(i)->AsShaderResource()->SetResource(0);
			}
		}
	}


	FW_VALIDATE(SetVariable("g_iTextureCount", uiNumValidTextures));


	return (bReturn);
}





bool
CD10Effect::GetVariable(const char* _kcpName, CMatrix& _rVariable)
{
	std::map<std::string, ID3D10EffectVariable*>::iterator VariableContainer = m_Variables.find(_kcpName);
	bool bReturn = true;


	if (VariableContainer != m_Variables.end())
	{
		static_cast<ID3D10EffectMatrixVariable*>((*VariableContainer).second)->GetMatrix(reinterpret_cast<float*>(&_rVariable));
	}
	else
	{
		bReturn = false;
	}


	return (bReturn);
}





bool
CD10Effect::GetVariable(const char* _kcpName, float& _frVariable)
{
	std::map<std::string, ID3D10EffectVariable*>::iterator VariableContainer = m_Variables.find(_kcpName);
	bool bReturn = true;


	if (VariableContainer != m_Variables.end())
	{
		static_cast<ID3D10EffectScalarVariable*>((*VariableContainer).second)->GetFloat(&_frVariable);
	}
	else
	{
		bReturn = false;
	}


	return (bReturn);
}





bool
CD10Effect::GetVariable(const char* _kcpName, int& _irVariable)
{
	std::map<std::string, ID3D10EffectVariable*>::iterator VariableContainer = m_Variables.find(_kcpName);
	bool bReturn = true;


	if (VariableContainer != m_Variables.end())
	{
		static_cast<ID3D10EffectScalarVariable*>((*VariableContainer).second)->GetInt(&_irVariable);
	}
	else
	{
		bReturn = false;
	}


	return (bReturn);
}





bool
CD10Effect::GetTechnique(const char* _kcpName, TEffectTechnique& _trEffectTechnique)
{
	std::map<std::string, TEffectTechnique>::iterator TechniqueContainer = m_Techniques.find(_kcpName);
	bool bReturn = true;


	if (TechniqueContainer != m_Techniques.end())
	{
		_trEffectTechnique = (*TechniqueContainer).second;
	}
	else
	{
		bReturn = false;
	}


	return (bReturn);
}





/********************************
            Protected
*********************************/





bool
CD10Effect::RegisterTechnique(CD10Renderer& _rD10Renderer, const TTechnqiue& _ktrTechnique)
{
	std::vector<D3D10_INPUT_ELEMENT_DESC> InputElementDescs;
	FW_VALIDATE(CompileInputLayout(_ktrTechnique.aInputLayout, InputElementDescs));


	ID3D10EffectTechnique* pD10Technique = m_pD10Effect->GetTechniqueByName(_ktrTechnique.kcpName);


	ID3D10InputLayout* pInputLayout = 0;
	FW_VALIDATE(_rD10Renderer.CreateInputLayout(pD10Technique, &(*InputElementDescs.begin()), InputElementDescs.size(), pInputLayout));
	

	TEffectTechnique tEffectTechnique;
	tEffectTechnique.pD10Technique = pD10Technique;
	tEffectTechnique.pD10InputLayout = pInputLayout;
	tEffectTechnique.uiStatesResetPassId = _ktrTechnique.uiStatesResetPassId;


	m_Techniques.insert( std::pair<std::string, TEffectTechnique>(_ktrTechnique.kcpName, tEffectTechnique) );


	return (true);
}





bool
CD10Effect::RegisterVariable(const char* _kcpName)
{
	ID3D10EffectVariable* pVariable = m_pD10Effect->GetVariableByName(_kcpName);


	m_Variables.insert( std::pair<std::string, ID3D10EffectVariable*>(_kcpName, pVariable) );


	return (true);
}





bool
CD10Effect::RegisterTransformationHelper()
{
	FW_VALIDATE(RegisterVariable("g_xWorld"));
	FW_VALIDATE(RegisterVariable("g_xView"));
	FW_VALIDATE(RegisterVariable("g_xProjection"));
	FW_VALIDATE(RegisterVariable("g_xWorldViewProjection"));


	return (true);
}





bool
CD10Effect::RegisterLightHelper()
{
	FW_VALIDATE(RegisterVariable("g_tLight"));
	FW_VALIDATE(RegisterVariable("g_iNumLights"));
	FW_VALIDATE(RegisterVariable("g_vCameraPosition"));



	return (true);
}





bool
CD10Effect::RegisterTextureHelper()
{
	FW_VALIDATE(RegisterVariable("g_TextureResources"));
	FW_VALIDATE(RegisterVariable("g_iTextureCount"));
	FW_VALIDATE(RegisterVariable("g_iTextureTypes"));


	return (true);
}





bool
CD10Effect::RegisterShadowHelper()
{

	return (true);


}





bool
CD10Effect::RegisterFogHelper()
{
	FW_VALIDATE(RegisterVariable("g_fFogStartDistance"));
	FW_VALIDATE(RegisterVariable("g_fFogDensity"));
	FW_VALIDATE(RegisterVariable("g_vFogColour"));


	return (true);
}





bool
CD10Effect::CompileInputLayout(const std::vector<TInput>& _karInputLayout, std::vector<D3D10_INPUT_ELEMENT_DESC>& _rInputElementDescs)
{
	uint uiByteOffset = 0;
	bool bReturn = true;


	for (uint i = 0; i < _karInputLayout.size(); ++ i)
	{
		switch (_karInputLayout[i].eVariableType)
		{
		case  VARIABLETYPE_BOOL:
			{
				D3D10_INPUT_ELEMENT_DESC InputDesc = {_karInputLayout[i].kcpName, _karInputLayout[i].uiSemanticIndex, DXGI_FORMAT_R8_UINT, 0, uiByteOffset, D3D10_INPUT_PER_VERTEX_DATA, 0};
				_rInputElementDescs.push_back(InputDesc);
				uiByteOffset += 1;
			}
			break;


		case  VARIABLETYPE_UINT:
			{
				D3D10_INPUT_ELEMENT_DESC InputDesc = {_karInputLayout[i].kcpName, _karInputLayout[i].uiSemanticIndex, DXGI_FORMAT_R32_UINT, 0, uiByteOffset, D3D10_INPUT_PER_VERTEX_DATA, 0};
				_rInputElementDescs.push_back(InputDesc);
				uiByteOffset += 4;
			}
			break;


		case  VARIABLETYPE_FLOAT1:
			{
				D3D10_INPUT_ELEMENT_DESC InputDesc = {_karInputLayout[i].kcpName, _karInputLayout[i].uiSemanticIndex, DXGI_FORMAT_R32_FLOAT, 0, uiByteOffset, D3D10_INPUT_PER_VERTEX_DATA, 0};
				_rInputElementDescs.push_back(InputDesc);
				uiByteOffset += 4;
			}
			break;

		case VARIABLETYPE_FLOAT2:
			{
				D3D10_INPUT_ELEMENT_DESC InputDesc = {_karInputLayout[i].kcpName, _karInputLayout[i].uiSemanticIndex, DXGI_FORMAT_R32G32_FLOAT, 0, uiByteOffset, D3D10_INPUT_PER_VERTEX_DATA, 0};
				_rInputElementDescs.push_back(InputDesc);
				uiByteOffset += 8;
			}
			break;

		case VARIABLETYPE_FLOAT3:
			{
				D3D10_INPUT_ELEMENT_DESC InputDesc = {_karInputLayout[i].kcpName, _karInputLayout[i].uiSemanticIndex, DXGI_FORMAT_R32G32B32_FLOAT, 0, uiByteOffset, D3D10_INPUT_PER_VERTEX_DATA, 0};
				_rInputElementDescs.push_back(InputDesc);
				uiByteOffset += 12;
			}
			break;

		case VARIABLETYPE_FLOAT4:
			{
				D3D10_INPUT_ELEMENT_DESC InputDesc = {_karInputLayout[i].kcpName, _karInputLayout[i].uiSemanticIndex, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, uiByteOffset, D3D10_INPUT_PER_VERTEX_DATA, 0};
				_rInputElementDescs.push_back(InputDesc);
				uiByteOffset += 16;
			}
			break;
		}
	}


	return (bReturn);
}





/********************************
            Private
*********************************/





bool
CD10Effect::InitialiseEffect(CD10Renderer& _rD10Renderer, const IEffect::TDesc& _ktrDescription)
{
	// Load effect file
	FW_VALIDATE(_rD10Renderer.LoadEffectFile(_ktrDescription.kcpEffectFile, m_pD10Effect));


	return (true);
}





bool
CD10Effect::InitialiseTechniques(CD10Renderer& _rD10Renderer, const IEffect::TDesc& _ktrDescription)
{
	// Techniques & Input layouts
	std::vector<TTechnqiue>::const_iterator kCurrentTechnique = _ktrDescription.aTechniques.cbegin();
	std::vector<TTechnqiue>::const_iterator kEndTechnique = _ktrDescription.aTechniques.cend();


	while (kCurrentTechnique != kEndTechnique)
	{
		FW_VALIDATE(RegisterTechnique(_rD10Renderer, (*kCurrentTechnique)));


		++ kCurrentTechnique;
	}


	return (true);
}





bool
CD10Effect::InitialiseVariables(const IEffect::TDesc& _ktrDescription)
{
	// Variables
	std::vector<std::string>::const_iterator kCurrentVariable = _ktrDescription.aVariableNames.cbegin();
	std::vector<std::string>::const_iterator kEndVariable = _ktrDescription.aVariableNames.cend();


	while (kCurrentVariable != kEndVariable)
	{
		const char* kcpVariableName = (*kCurrentVariable).c_str();


		FW_VALIDATE(RegisterVariable(kcpVariableName));


		++ kCurrentVariable;
	}


	return (true);
}





bool
CD10Effect::InitialiseHelpers(const IEffect::TDesc& _ktrDescription)
{
	if (_ktrDescription.bTransformationHelper)
	{
		FW_VALIDATE(RegisterTransformationHelper())
	}


	if (_ktrDescription.bLightHelper)
	{
		FW_VALIDATE(RegisterLightHelper())
		m_bUsesLightHelper = true;
	}


	if (_ktrDescription.bTextureHelper)
	{
		FW_VALIDATE(RegisterTextureHelper())
		m_bUsesTextureHelper = true;
	}


	if (_ktrDescription.bFogHelper)
	{
		FW_VALIDATE(RegisterFogHelper())
	}


	return (true);
}





void
CD10Effect::Deinitialise()
{
	if (m_bUsesLightHelper)
	{
		CLight* pLights[IEffect::MAX_LIGHTS];
		memset(pLights, 0, sizeof(CLight*) * IEffect::MAX_LIGHTS);


		SetLights(pLights, MAX_LIGHTS, CVector3(0.0f, 0.0f, 0.0f));
	}


	if (m_bUsesTextureHelper)
	{
		ITexture* pTextures[IEffect::MAX_TEXTURES];
		memset(pTextures, 0, sizeof(ITexture*) * IEffect::MAX_TEXTURES);


		SetTextures(pTextures, IEffect::MAX_TEXTURES);
	}


	std::map<std::string, TEffectTechnique>::iterator Current = m_Techniques.begin();
	std::map<std::string, TEffectTechnique>::iterator End = m_Techniques.end();


	for (Current; Current != End; ++ Current)
	{
		FW_RELEASE((*Current).second.pD10InputLayout);
	}


	FW_ADELETE(m_cpFile);
	FW_RELEASE(m_pD10Effect);
}