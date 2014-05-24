//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   D10VertexBuffer.cpp
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
#include "D10VertexBuffer.h"


// Static Variables
uint CD10VertexBuffer::s_uiInstanceCount = 0;


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CD10VertexBuffer constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD10VertexBuffer::CD10VertexBuffer()
: m_pVertexBuffer(0)	
, m_ePrimitiveType(INVALID_PRIMITIVETYPE)
, m_eUsage(INVALID_BUFFERUSAGE)
, m_ulFvF(0)
, m_uiCapacity(0)
, m_uiStride(0)
, m_uiInstanceId(++ s_uiInstanceCount)
, m_bLocked(false)
{
	// Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CD10VertexBuffer deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD10VertexBuffer::~CD10VertexBuffer()
{
	Deinitialise();
}





bool
CD10VertexBuffer::Initiailise(CD10Renderer* _pD10Renderer, const TDesc& _ktrBufferDesc)
{
	m_ePrimitiveType = _ktrBufferDesc.ePrimitiveType;
	m_eUsage = _ktrBufferDesc.eUsage;
	m_uiCapacity = _ktrBufferDesc.uiNumVertices;
	m_uiStride = _ktrBufferDesc.uiStride;


	bool bReturn = false;


	D3D10_BUFFER_DESC tVertexBufferDesc;
	memset(&tVertexBufferDesc, 0, sizeof(D3D10_BUFFER_DESC));
	tVertexBufferDesc.ByteWidth  = _ktrBufferDesc.uiNumVertices;
	tVertexBufferDesc.ByteWidth *= _ktrBufferDesc.uiStride;
	tVertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;


	switch (_ktrBufferDesc.eUsage)
	{
	case USAGE_STATIC:
		tVertexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
		break;

	case USAGE_DYNAMIC:
		tVertexBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
		tVertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		break;

	case USAGE_STAGING:
		tVertexBufferDesc.Usage = D3D10_USAGE_STAGING;
		tVertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
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
		tSubresourceDesc.pSysMem = new char[tVertexBufferDesc.ByteWidth];
	}
	else
	{
		tSubresourceDesc.pSysMem = _ktrBufferDesc.pInitialData;
	}


	_pD10Renderer->CreateBuffer(tVertexBufferDesc, tSubresourceDesc, m_pVertexBuffer);


	if (_ktrBufferDesc.pInitialData == 0)
	{
		FW_DELETE(tSubresourceDesc.pSysMem);
	}


	return (true);
}





bool
CD10VertexBuffer::Lock(ELockFlag _eLockFlag, void** _ppBufferData)
{
	assert(!m_bLocked);


	D3D10_MAP eD10LockFlag = D3D10_MAP_READ;
	bool bReturn = false;


	FW_VALIDATE(ConvertLockFlag(_eLockFlag, eD10LockFlag));


	if (m_eUsage == USAGE_STATIC)
	{
		bReturn = LockStatic(eD10LockFlag, _ppBufferData);
	}
	else if (m_eUsage == USAGE_DYNAMIC)
	{
		bReturn = LockDynamic(eD10LockFlag, _ppBufferData);
	}
	else
	{
		// Buffer cannot be locked!
		assert(false);
	}


	return (bReturn);
}





void
CD10VertexBuffer::Unlock()
{
	assert(m_bLocked);


	m_pVertexBuffer->Unmap();
}





bool
CD10VertexBuffer::UpdateRegion(IRenderer& _rRenderer, const void* _kpVertexData, uint _uiNumVertices, uint _uiIndexOffset)
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

		tBox.left = _uiIndexOffset * m_uiStride;
		tBox.right = tBox.left + (_uiNumVertices * m_uiStride);
		tBox.bottom = 1;
		tBox.back = 1;


		pD10Renderer->UpdateSubresource(m_pVertexBuffer, tBox, _kpVertexData, 0, 0);



		bReturn = true;
	}


	return (bReturn);
}





/********************************
            Protected
*********************************/





bool
CD10VertexBuffer::LockStatic(D3D10_MAP _eD10LockFlag, void** _ppVertexData)
{
	HRESULT hResult = S_OK;
	bool bReturn = false;


	return (bReturn);
}





bool
CD10VertexBuffer::LockDynamic(D3D10_MAP _eD10LockFlag, void** _ppVertexData)
{
	HRESULT hResult = S_OK;
	bool bReturn = false;



	hResult = m_pVertexBuffer->Map(_eD10LockFlag, 0, _ppVertexData);


	if (FAILED(hResult))
	{
		// Failed to lock
		assert(false);
	}
	else
	{
		bReturn = true;
		m_bLocked = true;
	}


	return (bReturn);
}





bool
CD10VertexBuffer::ConvertLockFlag(ELockFlag _eLockFlag, D3D10_MAP& _erD10LockFlag)
{
	bool bReturn = true;


	switch (_eLockFlag)
	{
	case LOCKFLAG_READONLY:
		_erD10LockFlag = D3D10_MAP_READ;
		break;

	case LOCKFLAG_READWRITE:
		_erD10LockFlag = D3D10_MAP_READ_WRITE;
		break;

	case LOCKFLAG_WRITEONLY:
		_erD10LockFlag = D3D10_MAP_WRITE;
		break;

	case LOCKFLAG_WRITEDISCARD:
		_erD10LockFlag = D3D10_MAP_WRITE_DISCARD;
		break;

	case LOCKFLAG_WRITENOOVERWRITE:
		_erD10LockFlag = D3D10_MAP_WRITE_NO_OVERWRITE;
		break;

	default:
		bReturn = false;
		break;
	}


	return (bReturn);
}






/********************************
            Private
*********************************/





void
CD10VertexBuffer::Deinitialise()
{
	FW_RELEASE(m_pVertexBuffer);
}