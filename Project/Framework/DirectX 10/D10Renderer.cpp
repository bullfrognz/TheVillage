//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   D10Renderer.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <assert.h>
#include <string>
#include <sstream>
#include <time.h>


// Defines Includes
#include "resource.h"
#include "Defines\Macros.h"


// Utilities Inclues
#include "Utilities\StrUtilities.h"
#include "Utilities\D10Convert.h"


// Math Includes
#include "Math\WorldMatrix.h"
#include "Math\ViewMatrix.h"


// Framework Includes
#include "Framework\Application.h"
#include "Framework\Clock.h"
#include "Framework\Dialog.h"
#include "Framework\DirectX 10\D10Text.h"
#include "Framework\DirectX 10\D10VertexBuffer.h"
#include "Framework\DirectX 10\D10IndexBuffer.h"
#include "Framework\DirectX 10\D10Effect.h"
#include "Framework\DirectX 10\D10Texture.h"



// This Include
#include "D10Renderer.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CD10Renderer constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD10Renderer::CD10Renderer()
: m_pD3D10Device(0)
, m_pSwapChain(0)
, m_pDepthStencilBuffer(0)
, m_pRenderTargetView(0)
, m_pDepthStencilView(0)
, m_pDebugInfo(0)
, m_pController(0)
, m_eDriverType(D3D10_DRIVER_TYPE_HARDWARE)
, m_uiBufferWidth(0)
, m_uiBufferHeight(0)
, m_uiActiveVertexBufferId(-1)
, m_uiActiveIndexBufferId(-1)
, m_bFullscreen(false)
{
	memset(&m_tClearColour, 0, sizeof(D3DXCOLOR));
	memset(&m_tActiveEffect, 0, sizeof(TActiveEffect));
	memset(m_tDeviceStates, 0, sizeof(TDeviceStates) * MAX_DEVICESTATES);


	//D3D10_DDI_PRIMITIVE_TOPOLOGY m_t;
	m_tClearColour.r = 0.31f;//0.31f
	m_tClearColour.g = 0.73f;//0.73
	m_tClearColour.b = 1.0f;
	m_tClearColour.a = 1.0f;
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CD10Renderer deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD10Renderer::~CD10Renderer()
{
	Deinitialise();
}





bool
CD10Renderer::Initialise(HWND& _hrWindowHandle, uint _uiBufferWidth, uint _uiBufferHeight, bool _bFullscreen)
{
	m_hWindowHandle = _hrWindowHandle;
	m_uiBufferWidth = _uiBufferWidth;
	m_uiBufferHeight = _uiBufferHeight;
	m_bFullscreen = _bFullscreen;


	FW_VALIDATE(InitialiseDirect3D())
	FW_VALIDATE(InitialiseDialogController())
	FW_VALIDATE(InitialiseDebugInfoText())
	FW_VALIDATE(InitialiseAdapters())
	FW_VALIDATE(InitialiseDefaultStates())
	FW_VALIDATE(InitialiseShadowDrawStates());
	FW_VALIDATE(InitialiseShadowLitStates());


	return (true);
}





bool
CD10Renderer::BeginRendering(bool _bClearTarget, bool _bClearDepth, bool _bClearStencil)
{
	m_pD3D10Device->ClearRenderTargetView(m_pRenderTargetView, m_tClearColour);
	m_pD3D10Device->ClearDepthStencilView(m_pDepthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);


	return (true);
}





bool
CD10Renderer::EndRendering()
{
	RenderFPSText();
	//RenderInfo();
	//RenderTime();


	m_pSwapChain->Present(0, 0);


	// Invalidate active buffers
	m_uiActiveVertexBufferId = -1;
	m_uiActiveIndexBufferId = -1;


	// Reset states
	RestoreDefaultStates(STATE_BLEND | STATE_RASTERIZER | STATE_DEPTHSTENCIL);


	return (true);
}





void
CD10Renderer::Reset()
{
	bool bReturn = false;


	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.
	FW_RELEASE(m_pDepthStencilBuffer);
	FW_RELEASE(m_pRenderTargetView);
	FW_RELEASE(m_pDepthStencilView);


	// Resize the swap chain and recreate the render target view.
	HRESULT hResult = m_pSwapChain->ResizeBuffers(1, m_uiBufferWidth, m_uiBufferHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);


	if (FAILED(hResult))
	{
		// Device or swap chain failed to create
		assert(false);
	}
	else
	{
		ID3D10Texture2D* pBackBuffer;
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&pBackBuffer));
		hResult = m_pD3D10Device->CreateRenderTargetView(pBackBuffer, 0, &m_pRenderTargetView);


		if (FAILED(hResult))
		{
			// Failed to create render target view
			assert(false);
		}
		else
		{
			FW_RELEASE(pBackBuffer);


			// Create the depth/stencil buffer and view.
			D3D10_TEXTURE2D_DESC depthStencilDesc = CreateTexture2DDesc();
			m_pD3D10Device->CreateTexture2D(&depthStencilDesc, 0, &m_pDepthStencilBuffer);
			m_pD3D10Device->CreateDepthStencilView(m_pDepthStencilBuffer, 0, &m_pDepthStencilView);


			// Bind the render target view and depth/stencil view to the pipeline.
			m_pD3D10Device->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	

			// Set the viewport transform.
			D3D10_VIEWPORT vp;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;
			vp.Width    = m_uiBufferWidth;
			vp.Height   = m_uiBufferHeight;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;


			m_pD3D10Device->RSSetViewports(1, &vp);
		}
	}
}





bool
CD10Renderer::SetActiveEffect(IEffect* _pEffect, const char* _kcpTechnique)
{
	CD10Effect* pD10Effect = dynamic_cast<CD10Effect*>(_pEffect);
	bool bReturn = false;


	if (pD10Effect == 0)
	{
		// Unsupported effect
		assert(false);
	}
	else
	{
		CD10Effect::TEffectTechnique tEffectTechnique;
		FW_VALIDATE(pD10Effect->GetTechnique(_kcpTechnique, tEffectTechnique));

	
		D3D10_TECHNIQUE_DESC tTechniqueDesc;
		tEffectTechnique.pD10Technique->GetDesc(&tTechniqueDesc);


		// Set input laypit for technique
		m_pD3D10Device->IASetInputLayout(tEffectTechnique.pD10InputLayout);


		m_tActiveEffect.pTechnique = tEffectTechnique.pD10Technique;
		m_tActiveEffect.uiNumDrawPasses = tTechniqueDesc.Passes;
		//m_tActiveEffect.uiStatesResetPassId = 


		bReturn = true;
	}


	return (bReturn);
}





bool
CD10Renderer::SetActiveVertexBuffer(IVertexBuffer* _pVertexBuffer, uint _uiOffset)
{
	CD10VertexBuffer* pD10VertexBuffer = dynamic_cast<CD10VertexBuffer*>(_pVertexBuffer);
	bool bReturn = true;


	if (pD10VertexBuffer == 0)
	{
		// Vertex buffer not supported
		assert(false);
		bReturn = false;
	}
	else
	{
		uint uiInstanceId = pD10VertexBuffer->GetInstanceId();


		//if (uiInstanceId != m_uiActiveVertexBufferId)
		{
			// Set primitive type
			IVertexBuffer::EPrimitiveType ePrimitiveType = pD10VertexBuffer->GetPrimitiveType();
			D3D10_PRIMITIVE_TOPOLOGY eD10PrimitiveType = D10Convert::PrimitiveType(ePrimitiveType);


			ID3D10Buffer* pD10Buffer = pD10VertexBuffer->GetBuffer();
			uint uiStide = pD10VertexBuffer->GetStride();


			m_pD3D10Device->IASetPrimitiveTopology(eD10PrimitiveType);
			m_pD3D10Device->IASetVertexBuffers(0, 1, &pD10Buffer, &uiStide, &_uiOffset);


			m_uiActiveVertexBufferId = uiInstanceId;
		}
		///else
		{
			// Do nothing
		}
	}


	return (true);
}





bool
CD10Renderer::Draw(uint _uiNumVertices, uint _uiOffset)
{
	bool bReturn = false;


	if (m_uiActiveVertexBufferId == 0)
	{
		// Vetex buffer has not been set
		assert(false);
	}
	else
	{
		for (uchar i = 0; i < m_tActiveEffect.uiNumDrawPasses; ++ i)
		{
			m_tActiveEffect.pTechnique->GetPassByIndex(i)->Apply(0);


			m_pD3D10Device->Draw(_uiNumVertices, _uiOffset);
		}


		// Apply reset pass
		if (m_tActiveEffect.uiStatesResetPassId != -1)
		{
			//m_tActiveEffect.pTechnique->GetPassByIndex(m_tActiveEffect.uiStatesResetPassId)->Apply(0);
		}


		bReturn = true;
	}


	return (bReturn);
}





bool
CD10Renderer::DrawIndexed(IIndexBuffer* _pIndexBuffer, uint _uiNumIndices, uint _uiIndexOffset, uint _uiVertexOffset)
{
	bool bReturn = false;


	CD10IndexBuffer* pD10IndexBuffer = dynamic_cast<CD10IndexBuffer*>(_pIndexBuffer);


	if (pD10IndexBuffer == 0)
	{
		// Invalid buffer type
		assert(false);
	}
	else
	{
		SetActiveIndexBuffer(pD10IndexBuffer);


		for (uchar i = 0; i < m_tActiveEffect.uiNumDrawPasses; ++ i)
		{
			m_tActiveEffect.pTechnique->GetPassByIndex(i)->Apply(0);


			m_pD3D10Device->DrawIndexed(_uiNumIndices, _uiIndexOffset, _uiVertexOffset);
		}


		// Apply reset pass
		if (m_tActiveEffect.uiStatesResetPassId != -1)
		{
		//	m_tActiveEffect.pTechnique->GetPassByIndex(m_tActiveEffect.uiStatesResetPassId)->Apply(0);
		}


		bReturn = true;
	}


	return (bReturn);
}





bool
CD10Renderer::DrawIndexedMulti(IIndexBuffer* _pIndexBuffer, uint _uiDrawCount,  uint* _uipNumIndices, uint* _uipIndexOffsets, uint* _uipVertexOffsets)
{
	bool bReturn = false;


	CD10IndexBuffer* pD10IndexBuffer = dynamic_cast<CD10IndexBuffer*>(_pIndexBuffer);


	if (pD10IndexBuffer == 0)
	{
		// Invalid buffer type
		assert(false);
	}
	else
	{
		SetActiveIndexBuffer(pD10IndexBuffer);


		for (uchar i = 0; i < m_tActiveEffect.uiNumDrawPasses; ++ i)
		{
			m_tActiveEffect.pTechnique->GetPassByIndex(i)->Apply(0);


			for (uint i = 0; i < _uiDrawCount; ++ i)
			{
				m_pD3D10Device->DrawIndexed(_uipNumIndices[i], _uipIndexOffsets[i], _uipVertexOffsets[i]);
			}
		}


		// Apply reset pass
		if (m_tActiveEffect.uiStatesResetPassId != -1)
		{
			//m_tActiveEffect.pTechnique->GetPassByIndex(m_tActiveEffect.uiStatesResetPassId)->Apply(0);
		}


		bReturn = true;
	}


	return (bReturn);
}





bool
CD10Renderer::InstanceEffect(const IEffect::TDesc& _ktrEffectDesc, IEffect*& _prEffect)
{
	CD10Effect* pD10Effect = new CD10Effect();
	FW_VALIDATE(pD10Effect->Initialise(*this, _ktrEffectDesc));


	_prEffect = pD10Effect;


	return (true);
}





bool
CD10Renderer::InstanceFont(const IText::TDesc& _ktrFontDesc, IText*& _prFont)
{
	CD10Text* pD10Text = new CD10Text();
	FW_VALIDATE(pD10Text->Initialise(*this, _ktrFontDesc));


	_prFont = pD10Text;


	return (true);
}





bool
CD10Renderer::InstanceTexture(const ITexture::TDesc& _ktrTextureDesc, ITexture*& _prTexture)
{
	CD10Texture* pD10Texture = new CD10Texture();
	FW_VALIDATE(pD10Texture->Initialise(*this, _ktrTextureDesc));


	_prTexture = pD10Texture;


	return (true);
}





bool
CD10Renderer::InstanceVertexBuffer(const IVertexBuffer::TDesc& _ktrBufferDesc, IVertexBuffer*& _prVertexBuffer)
{
	CD10VertexBuffer* pD10VertexBuffer = new CD10VertexBuffer();
	FW_VALIDATE(pD10VertexBuffer->Initiailise(this, _ktrBufferDesc));


	_prVertexBuffer = pD10VertexBuffer;


	return (true);
}





bool
CD10Renderer::InstanceIndexBuffer(const IIndexBuffer::TDesc& _ktrBufferDesc, IIndexBuffer*& _prIndexBuffer)
{
	CD10IndexBuffer* pD10IndexBuffer = new CD10IndexBuffer();
	FW_VALIDATE(pD10IndexBuffer->Initiailise(this, _ktrBufferDesc));


	_prIndexBuffer = pD10IndexBuffer;


	return (true);
}





bool
CD10Renderer::RestoreDefaultStates(uint _uiStates)
{
	if (_uiStates & STATE_BLEND)
	{
		m_pD3D10Device->OMSetBlendState(m_tDeviceStates[DEVICESTATES_DEFAULT].m_pD10Blend, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}


	if (_uiStates & STATE_RASTERIZER)
	{
		m_pD3D10Device->RSSetState(m_tDeviceStates[DEVICESTATES_DEFAULT].m_pD10Rasterizer);
	}


	if (_uiStates & STATE_DEPTHSTENCIL)
	{
		m_pD3D10Device->OMSetDepthStencilState(m_tDeviceStates[DEVICESTATES_DEFAULT].m_pD10DepthStencil, 0);
	}


	return (true);
}





bool
CD10Renderer::EnableShadowDrawStates()
{
	m_pD3D10Device->OMSetDepthStencilState(m_tDeviceStates[DEVICESTATES_SHADOWDRAW].m_pD10DepthStencil, 0);
	m_pD3D10Device->OMSetBlendState(m_tDeviceStates[DEVICESTATES_SHADOWDRAW].m_pD10Blend, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	m_pD3D10Device->RSSetState(m_tDeviceStates[DEVICESTATES_SHADOWDRAW].m_pD10Rasterizer);


	return (true);
}





bool
CD10Renderer::EnableLitDrawStates()
{
	m_pD3D10Device->OMSetDepthStencilState(m_tDeviceStates[DEVICESTATES_SHADOWLITDRAW].m_pD10DepthStencil, 0);
	m_pD3D10Device->OMSetBlendState(m_tDeviceStates[DEVICESTATES_SHADOWLITDRAW].m_pD10Blend, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	m_pD3D10Device->RSSetState(m_tDeviceStates[DEVICESTATES_SHADOWLITDRAW].m_pD10Rasterizer);


	return (true);
}





uint
CD10Renderer::GetBufferWidth() const
{
	return (m_uiBufferWidth);
}





uint
CD10Renderer::GetBufferHeight() const
{
	return (m_uiBufferHeight);
}





bool
CD10Renderer::LoadEffectFile(const char* _kcpFile, ID3D10Effect*& _prEffect)
{
	ulong ulShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
	bool bReturn = false;


#if defined(DEBUG) || defined(_DEBUG)


    ulShaderFlags |= D3D10_SHADER_DEBUG;
	ulShaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;


#endif


	std::string File;
	File += EFFECTS_DIR;
	File += _kcpFile;


	wchar_t* wcpFile = 0;
	StrUtilities::ConvertToWString(File.c_str(), wcpFile);
 

	ID3D10Blob* pCompilationErrors = 0;
	HRESULT hResult = D3DX10CreateEffectFromFile(wcpFile, 0, 0, "fx_4_0", ulShaderFlags, 0, m_pD3D10Device, 0, 0, &_prEffect, &pCompilationErrors, 0);


	if(FAILED(hResult))
	{
		if(pCompilationErrors != 0)
		{
			MessageBoxA(0, static_cast<char*>(pCompilationErrors->GetBufferPointer()), 0, 0);
			FW_RELEASE(pCompilationErrors);
		}


		//DXTrace(__FILE__, (DWORD)__LINE__, hr, L"D3DX10CreateEffectFromFile", true);
	}
	else
	{
		bReturn = true;
	}


	FW_ADELETE(wcpFile);


	return (bReturn);
}





bool
CD10Renderer::CreateInputLayout(ID3D10EffectTechnique* _pTechnique, D3D10_INPUT_ELEMENT_DESC* _tpVetexDesc, uint _uiNumElements, ID3D10InputLayout*& _prInputLayout)
{
	HRESULT hResult = S_OK;
	bool bReturn = false;


    D3D10_PASS_DESC tPassDesc;
    hResult = _pTechnique->GetPassByIndex(0)->GetDesc(&tPassDesc);


	if (FAILED(hResult))
	{
		// Could not get pass desc
		assert(false);
	}
	else
	{
		hResult = m_pD3D10Device->CreateInputLayout(_tpVetexDesc, _uiNumElements, tPassDesc.pIAInputSignature, tPassDesc.IAInputSignatureSize, &_prInputLayout);


		if (FAILED(hResult))
		{
			// Could not get pass desc
			assert(false);
		}
		else
		{
			bReturn = true;
		}
	}


	return (bReturn);
}




bool
CD10Renderer::CreateFontIndirect(const D3DX10_FONT_DESC& _ktrFontDesc, ID3DX10Font*& _prD10Text)
{
	bool bReturn = false;


	HRESULT hResult = D3DX10CreateFontIndirect(m_pD3D10Device, &_ktrFontDesc, &_prD10Text);


	if (FAILED(hResult))
	{
		// Failed to create font indirect
		assert(false);
	}
	else
	{
		bReturn = true;
	}


	return (bReturn);
}





bool
CD10Renderer::CreateBuffer(const D3D10_BUFFER_DESC& _krBufferDesc, const D3D10_SUBRESOURCE_DATA& _krSubresourceData, ID3D10Buffer*& _krBuffer)
{
	bool bReturn = false;


	HRESULT hCreated = m_pD3D10Device->CreateBuffer(&_krBufferDesc, &_krSubresourceData, &_krBuffer);


	if (FAILED(hCreated))
	{
		// Failed to create buffer
		assert(false);
	}
	else
	{
		bReturn = true;
	}


	return (true);
}





bool
CD10Renderer::CreateTextureResource(const char* _kcpFile, D3DX10_IMAGE_LOAD_INFO& _trImageInfo, ID3D10ShaderResourceView*& _prResourceView)
{
	wchar_t* wcFile = 0;
	bool bReturn = false;


	StrUtilities::ConvertToWString(_kcpFile, wcFile);


	HRESULT hResult = D3DX10CreateShaderResourceViewFromFile(m_pD3D10Device, wcFile, &_trImageInfo, 0, &_prResourceView, 0);


	if (FAILED(hResult))
	{
		// Failed to load texture
		assert(false);
	}
	else
	{
		bReturn = true;
	}


	FW_ADELETE(wcFile);


	return (bReturn);
}




bool
CD10Renderer::Create2DTexture(D3D10_TEXTURE2D_DESC& _trD10TextureDesc, ID3D10Texture2D*& _prTexture2D)
{
	bool bReturn = false;


	HRESULT hResult = m_pD3D10Device->CreateTexture2D( &_trD10TextureDesc, NULL, &_prTexture2D );


	if (FAILED(hResult))
	{
		// Failed to create empty texture
		assert(false);
	}
	else
	{
		bReturn = true;
	}


	return (true);
}





bool
CD10Renderer::Create2DTextureFromFile(const char* _kcpFile, D3DX10_IMAGE_LOAD_INFO& _trImageLoadInfo, ID3D10Texture2D*& _prTexture2D)
{
	ID3D10Resource* pTextureResource = 0;
	wchar_t* wcFile = 0;
	bool bReturn = false;


	StrUtilities::ConvertToWString(_kcpFile, wcFile);


	HRESULT hResult = D3DX10CreateTextureFromFile(m_pD3D10Device, wcFile, &_trImageLoadInfo, 0, &pTextureResource, 0);


	if (FAILED(hResult))
	{
		// Texture failed to load
		assert(false);
	}
	else
	{
		_prTexture2D = static_cast<ID3D10Texture2D*>(pTextureResource);
		bReturn = true;
	}


	FW_ADELETE(wcFile);


	return (bReturn);
}





bool
CD10Renderer::CreateShaderResourceView(ID3D10Resource* _pResource, ID3D10ShaderResourceView*& _prResourceView)
{
	D3D10_RESOURCE_DIMENSION eResourceType = D3D10_RESOURCE_DIMENSION_UNKNOWN;
	bool bReturn = false;


	_pResource->GetType(&eResourceType);


	if (eResourceType != D3D10_RESOURCE_DIMENSION_TEXTURE2D)
	{
		// Something else loaded instead of a 2d textre?
		assert(false);
	}
	else
	{
		D3D10_SHADER_RESOURCE_VIEW_DESC tResourceViewDesc;
		memset(&tResourceViewDesc, 0, sizeof(D3D10_SHADER_RESOURCE_VIEW_DESC));
		D3D10_TEXTURE2D_DESC tTexture2dDesc;
		memset(&tTexture2dDesc, 0, sizeof(D3D10_TEXTURE2D_DESC));
			

		ID3D10Texture2D* pD10Texture2D = static_cast<ID3D10Texture2D*>(_pResource);
		pD10Texture2D->GetDesc(&tTexture2dDesc);
		

		tResourceViewDesc.Format = tTexture2dDesc.Format;
		tResourceViewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
		tResourceViewDesc.Texture2D.MipLevels = tTexture2dDesc.MipLevels;
		tResourceViewDesc.Texture2D.MostDetailedMip = 0;


		HRESULT hResult = m_pD3D10Device->CreateShaderResourceView(pD10Texture2D, &tResourceViewDesc, &_prResourceView);


		if (FAILED(hResult))
		{
			// Failed to create shader resource view
			assert(false);
		}
		else
		{
			bReturn = true;
		}
	}


	return (bReturn);
}





bool
CD10Renderer::UpdateSubresource(ID3D10Resource* _pResource, const D3D10_BOX& _rBoundary, const void* _pData, uint _uiRowPitch, uint _uiDepthPitch)
{
	m_pD3D10Device->UpdateSubresource(_pResource, 0, &_rBoundary, _pData, _uiRowPitch, _uiDepthPitch);


	return (true);
}





/********************************
            Protected
*********************************/





DXGI_SWAP_CHAIN_DESC
CD10Renderer::CreateSwapChainDesc()
{
	DXGI_SWAP_CHAIN_DESC tSwapChainDesc;
	ZeroMemory(&tSwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));


	// Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.
	tSwapChainDesc.BufferDesc.Width  = m_uiBufferWidth;
	tSwapChainDesc.BufferDesc.Height = m_uiBufferHeight;
	tSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	tSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	tSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tSwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	tSwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;


	// No multisampling.
	tSwapChainDesc.SampleDesc.Count   = 1;
	tSwapChainDesc.SampleDesc.Quality = 0;


	tSwapChainDesc.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	tSwapChainDesc.BufferCount  = 1;
	tSwapChainDesc.OutputWindow = m_hWindowHandle;
	tSwapChainDesc.Windowed     = (!m_bFullscreen);
	tSwapChainDesc.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
	tSwapChainDesc.Flags        = 0;


	return (tSwapChainDesc);
}





D3D10_TEXTURE2D_DESC
CD10Renderer::CreateTexture2DDesc()
{
	D3D10_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D10_TEXTURE2D_DESC));
	

	depthStencilDesc.Width     = m_uiBufferWidth;
	depthStencilDesc.Height    = m_uiBufferHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count   = 1; // multisampling must match
	depthStencilDesc.SampleDesc.Quality = 0; // swap chain values.
	depthStencilDesc.Usage          = D3D10_USAGE_DEFAULT;
	depthStencilDesc.BindFlags      = D3D10_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags      = 0;


	return (depthStencilDesc);
}





void
CD10Renderer::SetActiveIndexBuffer(CD10IndexBuffer* _pD10IndexBuffer)
{
	//if (_pD10IndexBuffer->GetInstanceId() != m_uiActiveIndexBufferId)
	{
		m_pD3D10Device->IASetIndexBuffer(_pD10IndexBuffer->GetBuffer(), _pD10IndexBuffer->GetIndexSize() == IIndexBuffer::INDEXSIZE_32 ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT, 0);


		// Cache
		m_uiActiveIndexBufferId = _pD10IndexBuffer->GetInstanceId();
	}
}





/********************************
            Private
*********************************/





bool
CD10Renderer::InitialiseDirect3D()
{
	uint uiDeviceFlags = 0;
	bool bReturn = true;


#if defined(DEBUG) || defined(_DEBUG)

    uiDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;

#endif


	HRESULT hResult = D3D10CreateDeviceAndSwapChain(0,                 //default adapter
													m_eDriverType,
													0,                 // no software device
													uiDeviceFlags, 
													D3D10_SDK_VERSION,
													&CreateSwapChainDesc(),
													&m_pSwapChain,
													&m_pD3D10Device);


	if (FAILED(hResult))
	{
		// Device or swap chain failed to create
		assert(false);
		bReturn = false;
	}
	else
	{
		Reset();
	}


	return (bReturn);
}




bool
CD10Renderer::InitialiseDialogController()
{
	m_pController = new CDialog();
	FW_VALIDATE(m_pController->Initialise(RENDERER_CONTROL, this));
	//m_pController->Show();


	return (true);
}




bool
CD10Renderer::InitialiseDebugInfoText()
{
	IText::TDesc tTextDesc;
	FW_VALIDATE(InstanceFont(tTextDesc, m_pDebugInfo));
	m_pDebugInfo->SetPosition(10, 10);
	m_pDebugInfo->SetSize(12);
	m_pDebugInfo->SetColour(1.0f, 1.0f, 1.0f);


	return (true);
}





bool
CD10Renderer::InitialiseAdapters()
{
	IDXGIAdapter * pAdapter = NULL; 
    IDXGIFactory* pFactory = NULL;
	bool bReturn = false;


	HRESULT hResult = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFactory));
    

	if (FAILED(hResult))
	{
		assert(false);
	}
	else
	{
		for (uint i = 0; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++ i)
		{
			m_Adapters.push_back(pAdapter); 
		}


		FW_RELEASE(pFactory);


		bReturn = true;
	}


	return (bReturn);
}





bool
CD10Renderer::InitialiseDefaultStates()
{
	// Rasterizer
	D3D10_RASTERIZER_DESC tDefaultRasterizerDesc;
	tDefaultRasterizerDesc.FillMode = D3D10_FILL_SOLID;
	tDefaultRasterizerDesc.CullMode = D3D10_CULL_BACK;
	tDefaultRasterizerDesc.FrontCounterClockwise = false;
	tDefaultRasterizerDesc.DepthBias = 0;
	tDefaultRasterizerDesc.DepthBiasClamp = 0.0f;
	tDefaultRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	tDefaultRasterizerDesc.DepthClipEnable = true;
	tDefaultRasterizerDesc.ScissorEnable = false;
	tDefaultRasterizerDesc.MultisampleEnable = false;
	tDefaultRasterizerDesc.AntialiasedLineEnable = false;


	m_pD3D10Device->CreateRasterizerState(&tDefaultRasterizerDesc, &m_tDeviceStates[DEVICESTATES_DEFAULT].m_pD10Rasterizer);


	// Blend
	D3D10_BLEND_DESC tDefaultBlendDesc;
	tDefaultBlendDesc.AlphaToCoverageEnable = FALSE;
	tDefaultBlendDesc.SrcBlend = D3D10_BLEND_ONE;
	tDefaultBlendDesc.DestBlend = D3D10_BLEND_ZERO;
	tDefaultBlendDesc.BlendOp = D3D10_BLEND_OP_ADD;
	tDefaultBlendDesc.SrcBlendAlpha = D3D10_BLEND_ONE;
	tDefaultBlendDesc.DestBlendAlpha = D3D10_BLEND_ZERO;
	tDefaultBlendDesc.BlendOpAlpha = D3D10_BLEND_OP_ADD;
	

	for (uint i = 0; i < 8; ++ i)
	{
		tDefaultBlendDesc.BlendEnable[i] = false;
		tDefaultBlendDesc.RenderTargetWriteMask[i] = D3D10_COLOR_WRITE_ENABLE_ALL;
	}


	m_pD3D10Device->CreateBlendState(&tDefaultBlendDesc, &m_tDeviceStates[DEVICESTATES_DEFAULT].m_pD10Blend);



	// Depth & Stencil
	D3D10_DEPTH_STENCIL_DESC tDepthStencilDesc;
	tDepthStencilDesc.DepthEnable = true;
	tDepthStencilDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
	tDepthStencilDesc.DepthFunc = D3D10_COMPARISON_LESS;
	tDepthStencilDesc.StencilEnable = false;
	tDepthStencilDesc.StencilReadMask = D3D10_DEFAULT_STENCIL_READ_MASK;
	tDepthStencilDesc.StencilWriteMask = D3D10_DEFAULT_STENCIL_WRITE_MASK;


	D3D10_DEPTH_STENCILOP_DESC tDefaultOpDesc;
	tDefaultOpDesc.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	tDefaultOpDesc.StencilDepthFailOp = D3D10_STENCIL_OP_KEEP;
	tDefaultOpDesc.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	tDefaultOpDesc.StencilFunc = D3D10_COMPARISON_ALWAYS;


	tDepthStencilDesc.FrontFace = tDefaultOpDesc;
	tDepthStencilDesc.BackFace = tDefaultOpDesc;


	m_pD3D10Device->CreateDepthStencilState(&tDepthStencilDesc, &m_tDeviceStates[DEVICESTATES_DEFAULT].m_pD10DepthStencil);


	return (true);
}





bool
CD10Renderer::InitialiseShadowDrawStates()
{
	// Increment for shadows facing towards camera, decrement for shadows that are facing away from camera
	D3D10_DEPTH_STENCIL_DESC tD10DepthStencilDesc;
	tD10DepthStencilDesc.DepthEnable = true;
	tD10DepthStencilDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ZERO;	// Stop writing to the depth buffer
	tD10DepthStencilDesc.DepthFunc = D3D10_COMPARISON_LESS;				// The shadows are still blocked by geometry
	tD10DepthStencilDesc.StencilEnable = true;	// Turn on the stencil buffer
	tD10DepthStencilDesc.StencilReadMask  = D3D10_DEFAULT_STENCIL_READ_MASK;
	tD10DepthStencilDesc.StencilWriteMask = D3D10_DEFAULT_STENCIL_READ_MASK;


	tD10DepthStencilDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
	tD10DepthStencilDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	tD10DepthStencilDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	tD10DepthStencilDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;


	tD10DepthStencilDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
	tD10DepthStencilDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	tD10DepthStencilDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	tD10DepthStencilDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;


	m_pD3D10Device->CreateDepthStencilState(&tD10DepthStencilDesc, &m_tDeviceStates[DEVICESTATES_SHADOWDRAW].m_pD10DepthStencil);


	// Blend
	D3D10_BLEND_DESC tBlendDesc;
	m_tDeviceStates[DEVICESTATES_DEFAULT].m_pD10Blend->GetDesc(&tBlendDesc);


    tBlendDesc.RenderTargetWriteMask[0] = 0x0;


	m_pD3D10Device->CreateBlendState(&tBlendDesc, &m_tDeviceStates[DEVICESTATES_SHADOWDRAW].m_pD10Blend);


	// Rasterizer
	D3D10_RASTERIZER_DESC tRasterizerDesc;
	m_tDeviceStates[DEVICESTATES_DEFAULT].m_pD10Rasterizer->GetDesc(&tRasterizerDesc);


	tRasterizerDesc.CullMode = D3D10_CULL_NONE;


	m_pD3D10Device->CreateRasterizerState(&tRasterizerDesc, &m_tDeviceStates[DEVICESTATES_SHADOWDRAW].m_pD10Rasterizer);


	return (true);
}





bool
CD10Renderer::InitialiseShadowLitStates()
{
	// Stencil
	D3D10_DEPTH_STENCIL_DESC tD10DepthStencilDesc;
	m_tDeviceStates[DEVICESTATES_DEFAULT].m_pD10DepthStencil->GetDesc(&tD10DepthStencilDesc);


	tD10DepthStencilDesc.DepthEnable = true;
	tD10DepthStencilDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ZERO;
	tD10DepthStencilDesc.DepthFunc = D3D10_COMPARISON_LESS_EQUAL;

	tD10DepthStencilDesc.StencilEnable = true;
	tD10DepthStencilDesc.StencilReadMask = 0xFF;
	tD10DepthStencilDesc.StencilWriteMask = 0x0;

	tD10DepthStencilDesc.FrontFace.StencilFunc = D3D10_COMPARISON_EQUAL;
	tD10DepthStencilDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	tD10DepthStencilDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_ZERO;


	tD10DepthStencilDesc.BackFace.StencilFunc = D3D10_COMPARISON_NEVER;
	tD10DepthStencilDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_ZERO;
	tD10DepthStencilDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_ZERO;


	m_pD3D10Device->CreateDepthStencilState(&tD10DepthStencilDesc, &m_tDeviceStates[DEVICESTATES_SHADOWLITDRAW].m_pD10DepthStencil);


	// Desc
	D3D10_BLEND_DESC tBlendDesc;
	m_tDeviceStates[DEVICESTATES_DEFAULT].m_pD10Blend->GetDesc(&tBlendDesc);
	tBlendDesc.AlphaToCoverageEnable = false;
	tBlendDesc.BlendEnable[0] = true;
	tBlendDesc.SrcBlend = D3D10_BLEND_ONE;
	tBlendDesc.DestBlend = D3D10_BLEND_ONE;
	tBlendDesc.BlendOp = D3D10_BLEND_OP_ADD;
	tBlendDesc.SrcBlendAlpha = D3D10_BLEND_ZERO;
	tBlendDesc.DestBlendAlpha = D3D10_BLEND_ZERO;
	tBlendDesc.BlendOpAlpha = D3D10_BLEND_OP_ADD;
	tBlendDesc.RenderTargetWriteMask[0] = 0x0F;


	m_pD3D10Device->CreateBlendState(&tBlendDesc, &m_tDeviceStates[DEVICESTATES_SHADOWLITDRAW].m_pD10Blend);


	// Rasterizer
	D3D10_RASTERIZER_DESC tRasterizerDesc;
	m_tDeviceStates[DEVICESTATES_DEFAULT].m_pD10Rasterizer->GetDesc(&tRasterizerDesc);


	tRasterizerDesc.CullMode = D3D10_CULL_BACK;


	m_pD3D10Device->CreateRasterizerState(&tRasterizerDesc, &m_tDeviceStates[DEVICESTATES_SHADOWLITDRAW].m_pD10Rasterizer);


	return (true);

}





bool
CD10Renderer::RenderFPSText()
{
	float fDeltaTick = CApplication::GetInstance().GetClock().GetDeltaTick();
	uint uiFramesPerSecond = CApplication::GetInstance().GetClock().FramesPerSecond();


	std::stringstream StringSteam;  
	StringSteam.precision(4);
	StringSteam << "FPS: " << uiFramesPerSecond;


	m_pDebugInfo->SetText(StringSteam.str().c_str());
	m_pDebugInfo->Draw();


	return (true);
}





bool
CD10Renderer::RenderInfo()
{
	std::vector<IDXGIAdapter*>::iterator CurrentAdapter = m_Adapters.begin();
	std::vector<IDXGIAdapter*>::iterator EndAdapter = m_Adapters.end();


	std::stringstream StringSteam;
	bool bReturn = false;


	StringSteam << "Graphics Information\n\n";


	for (CurrentAdapter; CurrentAdapter != EndAdapter; ++ CurrentAdapter)
	{
		DXGI_ADAPTER_DESC AdapterDesc;
		IDXGIOutput* pOutput = 0;


		HRESULT hAdapter = (*CurrentAdapter)->GetDesc(&AdapterDesc);
		HRESULT hOutput = (*CurrentAdapter)->EnumOutputs(0, &pOutput);


		if (FAILED(hAdapter) || FAILED(hOutput))
		{
			// Failed to restrieve adapter or output data
			assert(false);
		}
		else
		{
			std::string GraphicsInfo;
			StrUtilities::ConvertToString(AdapterDesc.Description, GraphicsInfo);


			StringSteam << GraphicsInfo << "\n";
			StringSteam << "Dedicated System Memory: " << AdapterDesc.DedicatedSystemMemory / 1000000.0f << "MB\n";
			StringSteam << "Dedicated Video Memory: " << AdapterDesc.DedicatedVideoMemory / 1000000.0f << "MB\n";
			StringSteam << "Device Id: " << AdapterDesc.DeviceId << "\n";
			StringSteam << "Revision: " << AdapterDesc.Revision << "\n";
			StringSteam << "Shared System Memory: " << AdapterDesc.SharedSystemMemory << "\n";
			StringSteam << "Sub Sys Id: " << AdapterDesc.SubSysId << "\n";
			StringSteam << "Vendor Id: " << AdapterDesc.VendorId << "\n\n";
		}


		FW_RELEASE(pOutput);
	}


	m_pDebugInfo->SetPosition(20, 180);
	m_pDebugInfo->SetText(StringSteam.str().c_str());
	m_pDebugInfo->Draw();


	return (true);
}





bool
CD10Renderer::RenderTime()
{
	time_t ul64RawTime;
	tm tTimeInfo;

	time(&ul64RawTime);
	localtime_s(&tTimeInfo, &ul64RawTime);


	char cBuffer[256];
	asctime_s(cBuffer, 256, &tTimeInfo);


	std::stringstream StringSteam;  
	StringSteam.precision(4);
	StringSteam << "Local Time: " << cBuffer << "\n";


	m_pDebugInfo->SetPosition(20, 20);
	m_pDebugInfo->SetText(StringSteam.str().c_str());
	m_pDebugInfo->Draw();


	return (true);
}





void
CD10Renderer::ProcessDialogCommand(UINT _uiMessage, WPARAM _wParam, LPARAM _lParam)
{
	switch (LOWORD(_wParam))
	{
	case RENDERER_CONTROLLER_OK:
		{
			m_bFullscreen = m_pController->IsButtonChecked(RADIO_FULLSCREEN);
			m_pSwapChain->SetFullscreenState(m_bFullscreen, 0);


			break;
		}

	case RENDERER_CONTROLLER_CANCEL:
		{
			m_pController->Hide();
			break;
		}
	}
}





void
CD10Renderer::Deinitialise()
{
	// Remove everything
	m_pD3D10Device->OMSetBlendState(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	m_pD3D10Device->OMSetRenderTargets(0, 0, 0);
	m_pD3D10Device->OMSetDepthStencilState(0, 0);
	m_pD3D10Device->RSSetState(0);
	m_pD3D10Device->VSSetShader(0);
	m_pD3D10Device->GSSetShader(0);
	m_pD3D10Device->PSSetShader(0);
	m_pD3D10Device->IASetVertexBuffers(0, 0, 0, 0, 0);
	m_pD3D10Device->IASetIndexBuffer(0, DXGI_FORMAT_UNKNOWN, 0);


	FW_RELEASE(m_pSwapChain);
	FW_RELEASE(m_pDepthStencilBuffer);
	FW_RELEASE(m_pDepthStencilView);
	FW_RELEASE(m_pRenderTargetView);


	FW_DELETE(m_pDebugInfo);
	FW_DELETE(m_pController);


	for (uint i = 0; i < MAX_DEVICESTATES; ++ i)
	{
		FW_RELEASE(m_tDeviceStates[i].m_pD10Blend);
		FW_RELEASE(m_tDeviceStates[i].m_pD10DepthStencil);
		FW_RELEASE(m_tDeviceStates[i].m_pD10Rasterizer);
	}


	FW_RELEASE(m_pD3D10Device);
}

