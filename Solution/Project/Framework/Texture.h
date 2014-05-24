//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Texture.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Texture_H__
#define __Texture_H__


// Library Includes


// Local Includes
#include "Defines\DataTypes.h"
#include "Framework\Buffer.h"


// Types


// Prototypes
class IRenderer;

enum ELockFlag;


class ITexture : public IBuffer
{

	// Member Types
public:


	enum EFormat
	{
		INVALID_FORMAT = -1,

		FORMAT_R16G16B16A16,
		FORMAT_R8G8B8A8,
		FORMAT_R16,
		FORMAT_R8,

		MAX_FORMAT = 4
	};


	enum EBindFlag
	{
		INVALID_BINDFLAG = -1,

		BINDFLAG_NONE			= 1,
		BINDFLAG_SHADERRESOURCE	= 1 << 1,
		BINDFLAG_STREAMOUTPUT	= 1 << 2,
		BINDFLAG_RENDERTARGET	= 1 << 3,
		BINDFLAG_DEPTHSTENCIL	= 1 << 4,

		MAX_BINDFLAG
	};


	struct TDesc
	{
		TDesc()
		{
			memset(this, 0, sizeof(TDesc));
		}

		const char* kcpFile;

		EFormat eFormat;
		EUsage eUsage;
		EBindFlag eBindFlag;
		ECPUAccess eCPUAccess;

		uint uiWidth;		// Leave zero for auto detection when loading texture
		uint uiHeight;		// Leave zero for auto detection when loading texture
		uint uiNumMipMaps;	// Leave zero to automatically create mipmaps
	};


	struct TTexelOffset
	{
		TTexelOffset()
		{
			memset(this, 0, sizeof(TTexelOffset));
		}

		uint uiTop;
		uint uiBottom;
		uint uiLeft;
		uint uiRight;
	};


	// Member Functions
public:


			 ITexture() {};
	virtual ~ITexture() {};


	virtual bool Lock(ELockFlag _eLockFlag, void** _ppTextureData, uint& _uirRowPitch) = 0;
	virtual void Unlock() = 0;


	virtual bool UpdateRegion(IRenderer& _rRenderer, void* _pTexelData, const TTexelOffset& _ktrOffsets, uint _uiRowPitch, uint _uiDepthPitch) = 0;


	// Inline Functions
	virtual inline uint GetWidth() const = 0;
	virtual inline uint GetHeight() const = 0;
	virtual inline EFormat GetFormat() const = 0;
	virtual inline uint GetTexelSize() const = 0;
	virtual inline uint GetRowPitch() const = 0;
	virtual inline uint GetDepthPitch() const = 0;
	virtual inline uint GetInstanceId() const = 0;


protected:


private:


	// Member Variables
protected:


private:


};


#endif //__Texture_H__