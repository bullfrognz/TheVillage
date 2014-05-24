//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   D10Texture.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __D10Texture_H__
#define __D10Texture_H__


// Library Includes


// Local Includes
#include "Framework\Texture.h"


// Types


// Prototypes
class CD10Renderer;


class CD10Texture : public ITexture
{

	// Member Functions
public:


			 CD10Texture();
	virtual ~CD10Texture();


	bool Initialise(CD10Renderer& _rD10Renderer, const TDesc& _ktrDescription);


	virtual bool Lock(ELockFlag _eLockFlag, void** _ppTextureData, uint& _uirRowPitch);
	virtual void Unlock();


	virtual bool UpdateRegion(IRenderer& _rRenderer, void* _pTexelData, const TTexelOffset& _ktrOffsets, uint _uiRowPitch, uint _uiDepthPitch);


	// Inline Functions
	inline ID3D10ShaderResourceView* GetResourceView();


	virtual inline uint GetWidth() const;
	virtual inline uint GetHeight() const;
	virtual inline EFormat GetFormat() const;
	virtual inline uint GetTexelSize() const;
	virtual inline uint GetRowPitch() const;
	virtual inline uint GetDepthPitch() const;
	virtual inline uint GetInstanceId() const;


protected:


	D3DX10_IMAGE_LOAD_INFO CreateLoadInfo(const TDesc& _ktrDescription);
	D3D10_TEXTURE2D_DESC CreateEmptyDesc(const TDesc& _ktrDescription);


	void UpdateTexelSize();


private:


	bool InitialiseTexture(CD10Renderer& _rD10Renderer, const TDesc& _ktrDescription);
	bool InitialiseResourceView(CD10Renderer& _rD10Renderer, const TDesc& _ktrDescription);


	void Deinitialise();


	CD10Texture(const CD10Texture& _krD10Texture);
	CD10Texture& operator = (const CD10Texture& _krD10Texture);


	// Member Variables
protected:


private:


	char* m_cpFile;
	ID3D10Texture2D* m_pTexture2D;
	ID3D10ShaderResourceView* m_pResourceView;


	EFormat m_eFormat;
	EUsage m_eUsage;
	ECPUAccess m_eCPUAccess;


	uint m_uiWidth;
	uint m_uiHeight;
	uint m_uiTexelSize;
	uint m_uiNumMipMaps;
	uint m_uiBindFlags;
	uint m_uiRowPitch;
	uint m_uiDepthPitch;
	uint m_uiInstanceId;


	bool m_bLocked;


	static uint s_uiInstanceCount;


};


#include "D10Texture.inl"


#endif //__D10Texture_H__