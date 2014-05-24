//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   D10Renderer.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __D10Renderer_H__
#define __D10Renderer_H__


// Library Includes
#include <d3dx10.h>
#include <vector>


// Local Includes
#include "Defines\DataTypes.h"
#include "Math\ViewMatrix.h"
#include "Math\WorldMatrix.h"
#include "Framework\Effect.h"



#include "Scene\Game\Terrain.h"
#include "Scene\Game\Skybox.h"
#include "Scene\Game\DayNightCycle.h"
#include "Scene\Game\Village.h"


// This Includes
#include "Framework\Renderer.h"
#include "Framework\DialogMsgTarget.h"


// Types


// Constants


// Prototypes
class CDialog;
class CD10Effect;
class CD10VertexBuffer;
class CD10IndexBuffer;


class CD10Renderer : public IRenderer, public IDialogMsgTarget
{
	
	// Member Types
public:


	enum EDeviceStates
	{
		DEVICESTATES_DEFAULT,
		DEVICESTATES_SHADOWDRAW,
		DEVICESTATES_SHADOWLITDRAW,

		MAX_DEVICESTATES
	};


	struct TActiveEffect
	{
		ID3D10EffectTechnique* pTechnique;
		uint uiNumDrawPasses;
		uint uiStatesResetPassId;
	};


	struct TDeviceStates
	{
		ID3D10BlendState* m_pD10Blend;
		ID3D10RasterizerState* m_pD10Rasterizer;
		ID3D10DepthStencilState* m_pD10DepthStencil;
	};


	// Member Functions
public:


			 CD10Renderer();
	virtual ~CD10Renderer();


	virtual bool Initialise(HWND& _hrWindowHandle, uint _uiBufferWidth, uint _uiBufferHeight, bool _bFullscreen);
	virtual bool BeginRendering(bool _bClearTarget, bool _bClearDepth, bool _bClearStencil);
	virtual bool EndRendering();
	virtual void Reset();


	virtual bool SetActiveEffect(IEffect* _pEffect, const char* _kcpTechnique);
	virtual bool SetActiveVertexBuffer(IVertexBuffer* _pVertexBuffer, uint _uiOffset);


	virtual bool Draw(uint _uiNumVertices, uint _uiOffset);
	virtual bool DrawIndexed(IIndexBuffer* _pIndexBuffer, uint _uiNumIndices, uint _uiIndexOffset, uint _uiVertexOffset);
	virtual bool DrawIndexedMulti(IIndexBuffer* _pIndexBuffer, uint _uiDrawCount,  uint* _uipNumIndices, uint* _uipIndexOffsets, uint* _uipVertexOffsets);


	virtual bool InstanceEffect(const IEffect::TDesc& _ktrEffectDesc, IEffect*& _prEffect);
	virtual bool InstanceFont(const IText::TDesc& _ktrFontDesc, IText*& _prFont);
	virtual bool InstanceTexture(const ITexture::TDesc& _ktrTextureDesc, ITexture*& _prTexture);
	virtual bool InstanceVertexBuffer(const IVertexBuffer::TDesc& _ktrBufferDesc, IVertexBuffer*& _prVertexBuffer);
	virtual bool InstanceIndexBuffer(const IIndexBuffer::TDesc& _ktrBufferDesc, IIndexBuffer*& _prIndexBuffer);


	virtual bool RestoreDefaultStates(uint _uiStates);
	virtual bool EnableShadowDrawStates();
	virtual bool EnableLitDrawStates();


	virtual uint GetBufferWidth() const;
	virtual uint GetBufferHeight() const;


	bool LoadEffectFile(const char* _kcpFile, ID3D10Effect*& _prEffect);
	bool CreateInputLayout(ID3D10EffectTechnique* _pTechnique, D3D10_INPUT_ELEMENT_DESC* _tpVetexDesc, uint _uiNumElements, ID3D10InputLayout*& _prInputLayout);
	bool CreateFontIndirect(const D3DX10_FONT_DESC& _ktrFontDesc, ID3DX10Font*& _prD10Text);
	bool CreateBuffer(const D3D10_BUFFER_DESC& _krBufferDesc, const D3D10_SUBRESOURCE_DATA& _krSubresourceData, ID3D10Buffer*& _krBuffer);
	bool CreateTextureResource(const char* _kcpFile, D3DX10_IMAGE_LOAD_INFO& _trImageInfo, ID3D10ShaderResourceView*& _prResourceView);
	bool Create2DTexture(D3D10_TEXTURE2D_DESC& _trD10TextureDesc, ID3D10Texture2D*& _prTexture2D);
	bool Create2DTextureFromFile(const char* _kcpFile, D3DX10_IMAGE_LOAD_INFO& _trImageLoadInfo, ID3D10Texture2D*& _prTexture2D);
	bool CreateShaderResourceView(ID3D10Resource* _pResource, ID3D10ShaderResourceView*& _prResourceView);


	bool UpdateSubresource(ID3D10Resource* _pResource, const D3D10_BOX& _rBoundary, const void* _pData, uint _uiRowPitch, uint _uiDepthPitch);


	TActiveEffect& GetActiveEffect() {return (m_tActiveEffect);}
	ID3D10Device* GetDevice() {return (m_pD3D10Device);}


	// Inline Functions


protected:


	DXGI_SWAP_CHAIN_DESC CreateSwapChainDesc();
	D3D10_TEXTURE2D_DESC CreateTexture2DDesc();


	void SetActiveIndexBuffer(CD10IndexBuffer* _pD10IndexBuffer);


private:


	bool InitialiseDirect3D();
	bool InitialiseDialogController();
	bool InitialiseDebugInfoText();
	bool InitialiseAdapters();
	bool InitialiseDefaultStates();
	bool InitialiseShadowDrawStates();
	bool InitialiseShadowLitStates();


	bool RenderFPSText();
	bool RenderInfo();
	bool RenderTime();


	virtual void ProcessDialogCommand(UINT _uiMessage, WPARAM _wParam, LPARAM _lParam);


	void Deinitialise();


	CD10Renderer(const CD10Renderer& _krD10Renderer);
	CD10Renderer& operator = (const CD10Renderer& _krD10Renderer);


	// Member Variables
protected:


private:


	TDeviceStates m_tDeviceStates[MAX_DEVICESTATES];
	D3DXCOLOR m_tClearColour;
	TActiveEffect m_tActiveEffect;


	HWND m_hWindowHandle;


	ID3D10Device* m_pD3D10Device;
	IDXGISwapChain* m_pSwapChain;
	ID3D10Texture2D* m_pDepthStencilBuffer;
	ID3D10RenderTargetView* m_pRenderTargetView;
	ID3D10DepthStencilView* m_pDepthStencilView;

	IText* m_pDebugInfo;
	CDialog* m_pController;


	D3D10_DRIVER_TYPE m_eDriverType;


	uint m_uiBufferWidth;
	uint m_uiBufferHeight;
	uint m_uiActiveVertexBufferId;
	uint m_uiActiveIndexBufferId;


	bool m_bFullscreen;


	std::vector<IDXGIAdapter*> m_Adapters;


};


#endif //__D10Renderer_H__