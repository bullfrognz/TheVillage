//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   D10Convert.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __D10Convert_H__
#define __D10Convert_H__


// Library Includes


// Local Includes
#include "Defines\DataTypes.h"
#include "Framework\Buffer.h"
#include "Framework\Texture.h"
#include "Framework\VertexBuffer.h"


// Types


// Prototypes
enum D3D_PRIMITIVE_TOPOLOGY;
enum D3D10_USAGE;
enum DXGI_FORMAT;
enum D3D10_MAP;


namespace D10Convert
{
	// Functions
	D3D_PRIMITIVE_TOPOLOGY PrimitiveType(IVertexBuffer::EPrimitiveType _eType);
	D3D10_USAGE BufferUsage(IBuffer::EUsage _eUsage);
	uint CPUAccess(IBuffer::ECPUAccess _eAccess);
	uint BindFlags(ITexture::EBindFlag _eBindFlag);
	DXGI_FORMAT TextureFormat(ITexture::EFormat _eFormat);
	D3D10_MAP LockFlag(IBuffer::ELockFlag _eLockFlag);
	uint TexelSize(ITexture::EFormat _eFormat);
}


#endif //__D10Convert_H__