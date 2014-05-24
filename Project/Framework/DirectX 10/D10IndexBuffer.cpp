//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   D10IndexBuffer.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <D3DX10.h>
#include <assert.h>


// Local Includes
#include "Defines\Macros.h"
#include "Framework\DirectX 10\D10Renderer.h"


// This Include
#include "D10IndexBuffer.h"


// Static Variables
uint CD10IndexBuffer::s_uiInstanceCount = 0;


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CD10IndexBuffer constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD10IndexBuffer::CD10IndexBuffer()
: m_pIndexBuffer(0)
, m_eUsage(INVALID_BUFFERUSAGE)
, m_eIndexSize(INVALID_INDEXSIZE)
, m_uiCapacity(0)
, m_uiInstanceId(++ s_uiInstanceCount)
, m_bLocked(0)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CD10IndexBuffer deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD10IndexBuffer::~CD10IndexBuffer()
{
	Deinitialise();
}





bool
CD10IndexBuffer::Initiailise(CD10Renderer* _pD10Renderer, const TDesc& _ktrBufferDesc)
{
	m_eUsage = _ktrBufferDesc.eUsage;
	m_eIndexSize = _ktrBufferDesc.eIndexSize;
	m_uiCapacity = _ktrBufferDesc.uiIndicesCount;


	bool bReturn = false;


	D3D10_BUFFER_DESC tIndexBufferDesc;
	memset(&tIndexBufferDesc, 0, sizeof(D3D10_BUFFER_DESC));
	tIndexBufferDesc.ByteWidth  = _ktrBufferDesc.uiIndicesCount;
	tIndexBufferDesc.ByteWidth *= (m_eIndexSize == INDEXSIZE_32) ? sizeof(int) : sizeof(short);
	tIndexBufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;


	switch (_ktrBufferDesc.eUsage)
	{
	case USAGE_STATIC:
		tIndexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
		break;

	case USAGE_DYNAMIC:
		tIndexBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
		tIndexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		break;

	case USAGE_STAGING:
		tIndexBufferDesc.Usage = D3D10_USAGE_STAGING;
		tIndexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		break;

	default:
		// Invalid usage flag
		assert(false);
		break;
	}


	D3D10_SUBRESOURCE_DATA tSubresourceDesc;
	memset(&tSubresourceDesc, 0, sizeof(D3D10_SUBRESOURCE_DATA));


	if (_ktrBufferDesc.pInitialData == 0)
	{
		tSubresourceDesc.pSysMem = new char[tIndexBufferDesc.ByteWidth];
	}
	else
	{
		tSubresourceDesc.pSysMem = _ktrBufferDesc.pInitialData;
	}
	

	_pD10Renderer->CreateBuffer(tIndexBufferDesc, tSubresourceDesc, m_pIndexBuffer);


	if (_ktrBufferDesc.pInitialData == 0)
	{
		FW_DELETE(tSubresourceDesc.pSysMem);
	}


	return (true);
}






bool
CD10IndexBuffer::Lock(ELockFlag _eLockFlag, void** _ppBufferData)
{
	assert(!m_bLocked);


	D3D10_MAP eLockFlag = D3D10_MAP_READ;
	bool bFlagDefined = true;
	bool bReturn = false;


	switch (_eLockFlag)
	{
	case LOCKFLAG_READONLY:
		eLockFlag = D3D10_MAP_READ;
		break;

	case LOCKFLAG_READWRITE:
		eLockFlag = D3D10_MAP_WRITE;
		break;

	case LOCKFLAG_WRITEONLY:
		eLockFlag = D3D10_MAP_READ_WRITE;
		break;

	case LOCKFLAG_WRITEDISCARD:
		eLockFlag = D3D10_MAP_WRITE_DISCARD;
		break;

	case LOCKFLAG_WRITENOOVERWRITE:
		eLockFlag = D3D10_MAP_WRITE_NO_OVERWRITE;
		break;

	default:
		bFlagDefined = false;
		break;
	}



	if (!bFlagDefined)
	{
		// Lock flag not supported
		assert(false);
	}
	else
	{
		HRESULT hLocked = m_pIndexBuffer->Map(eLockFlag, 0, _ppBufferData);


		if (FAILED(hLocked))
		{
			// Failed to lock
			assert(false);
		}
		else
		{
			bReturn = true;
			m_bLocked = true;
		}
	}


	return (bReturn);
}






void
CD10IndexBuffer::Unlock()
{
	assert(m_bLocked);


	m_pIndexBuffer->Unmap();
}






/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





void
CD10IndexBuffer::Deinitialise()
{
	FW_RELEASE(m_pIndexBuffer);
}