//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   D10Convert.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <assert.h>
#include <D3DX10.h>


// Local Includes


// This Include
#include "D10Convert.h"


// Static Variables


// Implementation


namespace D10Convert
{
	D3D_PRIMITIVE_TOPOLOGY
	PrimitiveType(IVertexBuffer::EPrimitiveType _eType)
	{
		D3D_PRIMITIVE_TOPOLOGY ePrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;


		switch (_eType)
		{
		case IVertexBuffer::PRIMITIVETYPE_POINTLIST:
			ePrimitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_POINTLIST;
			break;

		case IVertexBuffer::PRIMITIVETYPE_LINELIST:
			ePrimitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_LINELIST;
			break;

		case IVertexBuffer::PRIMITIVETYPE_LINESTRIP:
			ePrimitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP;
			break;

		case IVertexBuffer::PRIMITIVETYPE_TRIANGLELIST:
			ePrimitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;

		case IVertexBuffer::PRIMITIVETYPE_TRIANGLESTRIP:
			ePrimitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
			break;

		default:
			// Unknown or unsupported primitive type
			assert(false);
			break;
		}


		return (ePrimitiveTopology);
	}



	D3D10_USAGE
	BufferUsage(IBuffer::EUsage _eUsage)
	{
		D3D10_USAGE eD10Usage = D3D10_USAGE_DEFAULT;


		switch (_eUsage)
		{
		case IBuffer::USAGE_STATIC:
			eD10Usage = D3D10_USAGE_DEFAULT;
			break;

		case IBuffer::USAGE_DYNAMIC:
			eD10Usage = D3D10_USAGE_DYNAMIC;
			break;

		case IBuffer::USAGE_STAGING:
			eD10Usage = D3D10_USAGE_STAGING;
			break;

		default:
			assert(false);
			break;
		}


		return (eD10Usage);
	}


	uint
	CPUAccess(IBuffer::ECPUAccess _eAccess)
	{
		uint uiD10CPUAccess = 0;


		switch (_eAccess)
		{
		case IBuffer::CPUACCESS_NONE:
			uiD10CPUAccess = 0;
			break;

		case IBuffer::CPUACCESS_READ:
			uiD10CPUAccess = D3D10_CPU_ACCESS_READ;
			break;

		case IBuffer::CPUACCESS_WRITE:
			uiD10CPUAccess = D3D10_CPU_ACCESS_WRITE;
			break;

		case IBuffer::CPUACCESS_READWRITE:
			uiD10CPUAccess = D3D10_CPU_ACCESS_READ | D3D10_CPU_ACCESS_WRITE;
			break;

		default:
			assert(false);
			break;
		}


		return (uiD10CPUAccess);
	}


	uint
	BindFlags(ITexture::EBindFlag _eBindFlag)
	{
		uint uiBindFlags = 0;


		if (_eBindFlag & ITexture::BINDFLAG_SHADERRESOURCE)
		{
			uiBindFlags |= D3D10_BIND_SHADER_RESOURCE;
		}


		if (_eBindFlag & ITexture::BINDFLAG_STREAMOUTPUT)
		{
			uiBindFlags |= D3D10_BIND_STREAM_OUTPUT;
		}


		if (_eBindFlag & ITexture::BINDFLAG_RENDERTARGET)
		{
			uiBindFlags |= D3D10_BIND_RENDER_TARGET;
		}


		if (_eBindFlag & ITexture::BINDFLAG_DEPTHSTENCIL)
		{
			uiBindFlags |= D3D10_BIND_DEPTH_STENCIL;
		}


		return (uiBindFlags);
	}


	DXGI_FORMAT
	TextureFormat(ITexture::EFormat _eFormat)
	{
		DXGI_FORMAT eD10Formaat = DXGI_FORMAT_UNKNOWN;


		switch(_eFormat)
		{
		case ITexture::FORMAT_R16G16B16A16:
			eD10Formaat = DXGI_FORMAT_R16G16B16A16_UNORM;
			break;

		case ITexture::FORMAT_R8G8B8A8:
			eD10Formaat = DXGI_FORMAT_R8G8B8A8_UNORM;
			break;

		case ITexture::FORMAT_R16:
			eD10Formaat = DXGI_FORMAT_R16_UNORM;
			break;

		case ITexture::FORMAT_R8:
			eD10Formaat = DXGI_FORMAT_R8_UNORM;//DXGI_FORMAT_R8_UNORM
			break;

		default:
			// Unsupported texture format
			assert(false);
			break;
		}


		return (eD10Formaat);
	}


	D3D10_MAP
	LockFlag(IBuffer::ELockFlag _eLockFlag)
	{
		D3D10_MAP eD10LockFlag = D3D10_MAP_READ;


		switch (_eLockFlag)
		{
		case IBuffer::LOCKFLAG_READONLY:
			eD10LockFlag = D3D10_MAP_READ;
			break;

		case IBuffer::LOCKFLAG_READWRITE:
			eD10LockFlag = D3D10_MAP_WRITE;
			break;

		case IBuffer::LOCKFLAG_WRITEONLY:
			eD10LockFlag = D3D10_MAP_READ_WRITE;
			break;

		case IBuffer::LOCKFLAG_WRITEDISCARD:
			eD10LockFlag = D3D10_MAP_WRITE_DISCARD;
			break;

		case IBuffer::LOCKFLAG_WRITENOOVERWRITE:
			eD10LockFlag = D3D10_MAP_WRITE_NO_OVERWRITE;
			break;

		default:
			// Unknown lock flag
			assert(false);
			break;
		}


		return (eD10LockFlag);
	}


	uint
	TexelSize(ITexture::EFormat _eFormat)
	{
		uint uiSize = 0;


		switch (_eFormat)
		{
		case ITexture::FORMAT_R16G16B16A16:
			uiSize = 8;
			break;

		case ITexture::FORMAT_R8G8B8A8:
			uiSize = 4;
			break;

		case ITexture::FORMAT_R16:
			uiSize = 2;
			break;

		case ITexture::FORMAT_R8:
			uiSize = 1;
			break;

		default:
			// Unknown format
			assert(false);
			break;
		}


		return (uiSize);
	}
}