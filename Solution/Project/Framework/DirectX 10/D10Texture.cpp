//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   D10Texture.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <D3DX10.h>


// Local Includes
#include "Defines\Macros.h"
#include "Utilities\StrUtilities.h"
#include "Utilities\D10Convert.h"
#include "Framework\DirectX 10\D10Renderer.h"


// This Include
#include "D10Texture.h"


// Static Variables
uint CD10Texture::s_uiInstanceCount = 0;


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CD10Texture constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD10Texture::CD10Texture()
: m_cpFile(0)
, m_pTexture2D(0)
, m_pResourceView(0)
, m_eFormat(ITexture::INVALID_FORMAT)
, m_eUsage(IBuffer::INVALID_BUFFERUSAGE)
, m_eCPUAccess(IBuffer::INVALID_CPUACCESS)
, m_uiWidth(0)
, m_uiHeight(0)
, m_uiTexelSize(0)
, m_uiNumMipMaps(0)
, m_uiBindFlags(0)
, m_uiRowPitch(0)
, m_uiDepthPitch(0)
, m_uiInstanceId(++ s_uiInstanceCount)
, m_bLocked(false)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CD10Texture deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD10Texture::~CD10Texture()
{
	Deinitialise();
}





bool
CD10Texture::Initialise(CD10Renderer& _rD10Renderer, const TDesc& _ktrDescription)
{
	if (_ktrDescription.kcpFile != 0)
	{
		StrUtilities::Copy(_ktrDescription.kcpFile, m_cpFile);
	}


	m_eCPUAccess = _ktrDescription.eCPUAccess;
	m_eFormat = _ktrDescription.eFormat;
	m_eUsage = _ktrDescription.eUsage;
	m_uiBindFlags = _ktrDescription.eBindFlag;
	m_uiNumMipMaps = _ktrDescription.uiNumMipMaps;
	m_uiTexelSize = D10Convert::TexelSize(m_eFormat);


	FW_VALIDATE(InitialiseTexture(_rD10Renderer, _ktrDescription));
	FW_VALIDATE(InitialiseResourceView(_rD10Renderer, _ktrDescription));


	return (true);
}





bool
CD10Texture::Lock(ELockFlag _eLockFlag, void** _ppTextureData, uint& _uirRowPitch)
{
	assert(!m_bLocked);


	D3D10_MAP eD10LockFlag = D10Convert::LockFlag(_eLockFlag);
	bool bReturn = false;


	D3D10_MAPPED_TEXTURE2D tMappedTexture2D;
	HRESULT hLocked = m_pTexture2D->Map(D3D10CalcSubresource(0, 0, 1), eD10LockFlag, 0, &tMappedTexture2D);


	if (FAILED(hLocked))
	{
		// Failed to lock
		assert(false);
	}
	else
	{
		bReturn = true;
		m_bLocked = true;


		(*_ppTextureData) = tMappedTexture2D.pData;
		_uirRowPitch = tMappedTexture2D.RowPitch;
	}


	return (true);
}





void
CD10Texture::Unlock()
{
	assert(m_bLocked);


	m_pTexture2D->Unmap(0);
}





bool
CD10Texture::UpdateRegion(IRenderer& _rRenderer, void* _pTexelData, const TTexelOffset& _ktrOffsets, uint _uiRowPitch, uint _uiDepthPitch)
{
	bool bReturn = false;


	CD10Renderer* pD10Renderer = dynamic_cast<CD10Renderer*>(&_rRenderer);


	if (pD10Renderer == 0)
	{
		// Invalid renderer type
		assert(false);
	}
	else
	{
		D3D10_BOX tBox;
		memset(&tBox, 0, sizeof(tBox));


		tBox.top = _ktrOffsets.uiTop;
		tBox.bottom = _ktrOffsets.uiBottom;


		tBox.front = 0;
		tBox.back = 1;


		tBox.left = _ktrOffsets.uiLeft;
		tBox.right = _ktrOffsets.uiRight;


		pD10Renderer->UpdateSubresource(m_pTexture2D, tBox, _pTexelData, _uiRowPitch, _uiDepthPitch);



		bReturn = true;
	}


	return (bReturn);
}





/********************************
            Protected
*********************************/





D3DX10_IMAGE_LOAD_INFO
CD10Texture::CreateLoadInfo(const TDesc& _ktrDescription)
{
	D3DX10_IMAGE_LOAD_INFO tD10ImageLoadInfo;
	memset(&tD10ImageLoadInfo, 0, sizeof(D3DX10_IMAGE_LOAD_INFO));


	tD10ImageLoadInfo.Width = _ktrDescription.uiWidth;
	tD10ImageLoadInfo.Height = _ktrDescription.uiHeight;
	tD10ImageLoadInfo.Depth = D3DX10_FROM_FILE;
	tD10ImageLoadInfo.MipLevels = _ktrDescription.uiNumMipMaps;
	tD10ImageLoadInfo.BindFlags = 0;
	tD10ImageLoadInfo.Filter = D3DX10_FILTER_NONE;
	tD10ImageLoadInfo.MipFilter = D3DX10_FILTER_NONE;
	tD10ImageLoadInfo.MipLevels = m_uiNumMipMaps;


	tD10ImageLoadInfo.Usage = D10Convert::BufferUsage(_ktrDescription.eUsage);
	tD10ImageLoadInfo.CpuAccessFlags = D10Convert::CPUAccess(_ktrDescription.eCPUAccess);
	tD10ImageLoadInfo.BindFlags = D10Convert::BindFlags(_ktrDescription.eBindFlag);
	tD10ImageLoadInfo.Format = D10Convert::TextureFormat(_ktrDescription.eFormat);


	return (tD10ImageLoadInfo);
}





D3D10_TEXTURE2D_DESC
CD10Texture::CreateEmptyDesc(const TDesc& _ktrDescription)
{
	D3D10_TEXTURE2D_DESC tD10Texture2DDesc;
	memset(&tD10Texture2DDesc, 0, sizeof(D3D10_TEXTURE2D_DESC));


	DXGI_SAMPLE_DESC tSampleDesc;
	tSampleDesc.Count = 1;
	tSampleDesc.Quality = 0;


	tD10Texture2DDesc.Width = _ktrDescription.uiWidth;
	tD10Texture2DDesc.Height = _ktrDescription.uiHeight;
	tD10Texture2DDesc.ArraySize = 1;
	tD10Texture2DDesc.MipLevels = _ktrDescription.uiNumMipMaps;
	//tD10Texture2DDesc.MiscFlags = D3DX10_FILTER_NONE;
	tD10Texture2DDesc.SampleDesc = tSampleDesc;


	tD10Texture2DDesc.Usage = D10Convert::BufferUsage(_ktrDescription.eUsage);
	tD10Texture2DDesc.CPUAccessFlags = D10Convert::CPUAccess(_ktrDescription.eCPUAccess);
	tD10Texture2DDesc.BindFlags = D10Convert::BindFlags(_ktrDescription.eBindFlag);
	tD10Texture2DDesc.Format = D10Convert::TextureFormat(_ktrDescription.eFormat);


	return (tD10Texture2DDesc);
}





/********************************
            Private
*********************************/





bool
CD10Texture::InitialiseTexture(CD10Renderer& _rD10Renderer, const TDesc& _ktrDescription)
{
	if (_ktrDescription.kcpFile == 0)
	{
		D3D10_TEXTURE2D_DESC tD10Texture2DDesc = CreateEmptyDesc(_ktrDescription);


		FW_VALIDATE(_rD10Renderer.Create2DTexture(tD10Texture2DDesc, m_pTexture2D));
	}
	else
	{
		D3DX10_IMAGE_LOAD_INFO tD10ImageLoadInfo = CreateLoadInfo(_ktrDescription);


		FW_VALIDATE(_rD10Renderer.Create2DTextureFromFile(_ktrDescription.kcpFile, tD10ImageLoadInfo, m_pTexture2D));
	}


	D3D10_TEXTURE2D_DESC tTexture2dDesc;
	m_pTexture2D->GetDesc(&tTexture2dDesc);


	m_uiWidth = tTexture2dDesc.Width;
	m_uiHeight = tTexture2dDesc.Height;
	m_uiRowPitch = m_uiTexelSize * m_uiWidth;
	m_uiDepthPitch = m_uiRowPitch * m_uiHeight;


	return (true);
}





bool
CD10Texture::InitialiseResourceView(CD10Renderer& _rD10Renderer, const TDesc& _ktrDescription)
{
	if (_ktrDescription.eBindFlag & BINDFLAG_SHADERRESOURCE)
	{
		FW_VALIDATE(_rD10Renderer.CreateShaderResourceView(m_pTexture2D, m_pResourceView));
	}


	return (true);
}





void
CD10Texture::Deinitialise()
{
	FW_RELEASE(m_pTexture2D);
	FW_RELEASE(m_pResourceView);
	FW_ADELETE(m_cpFile);
}