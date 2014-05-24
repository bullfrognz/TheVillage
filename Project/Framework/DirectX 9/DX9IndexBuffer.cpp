//
//  Bryce Booth
//  9 Park Hill Road
//  North Shore City
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   DX9IndexBuffer.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   brycebooth@hotmail.com
//


// Library Includes
#include <assert.h>


// Local Includes
#include "Defines\Macros.h"
#include "Framework\Renderer.h"
#include "Framework\VertexBuffer.h"
#include "Framework\DeviceStates.h"


// This Include
#include "DX9IndexBuffer.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CDX9IndexBuffer constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDX9IndexBuffer::CDX9IndexBuffer()
: m_pDX9IndexBuffer(0)
, m_ePool(MEMORYPOOL_INVALID)
, m_eBufferType(BUFFERTYPE_INVALID)
, m_eIndexSize(INDEXSIZE_INVALID)
, m_ulUsageFlags(0)
, m_uiCapacity(0)
, m_uiMinIndex(0)
, m_uiDrawIndexCount(0)
, m_bLocked(false)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CDX9IndexBuffer deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDX9IndexBuffer::~CDX9IndexBuffer()
{
	Deinitialise();
}





bool
CDX9IndexBuffer::Initialise(CRenderer& _rRenderer, EBufferType _eBufferType, EIndexSize _eIndexSize, uint _uiNumIndices)
{
	m_eBufferType = _eBufferType;
	m_eIndexSize = _eIndexSize;
	m_uiCapacity = _uiNumIndices;


	FW_VALIDATE(InitialiseBuffer(_rRenderer));


	return (true);
}





bool
CDX9IndexBuffer::Draw(CRenderer& _rRenderer, CVertexBuffer& _rVertexBuffer)
{
	EPrimitiveType ePrimitiveType = _rVertexBuffer.GetPrimitiveType();
	uint uiNumPrimitives = CalculateNumPrimitives(ePrimitiveType, m_uiDrawIndexCount);


	_rVertexBuffer.PrepareDevice(_rRenderer);


	_rRenderer.GetDeviceStates().SetIndices(m_pDX9IndexBuffer);


	bool bRendered = _rRenderer.DrawIndexedPrimitive(static_cast<D3DPRIMITIVETYPE>(ePrimitiveType), uiNumPrimitives, m_uiMinIndex, _rVertexBuffer.GetNumVertices());


	return (bRendered);
}




bool
CDX9IndexBuffer::ExpandCapacity(CRenderer& _rRenderer, uint _uiNumIndices, bool _bTransferData)
{
	IDirect3DDX9IndexBuffer9* pTmpDX9IndexBuffer = 0;
	uint uiNewCapacity = m_uiCapacity + _uiNumIndices;


	if (_bTransferData == false)
	{
		FW_RELEASE(m_pDX9IndexBuffer);
	}


	_rRenderer.CreateDX9IndexBuffer(uiNewCapacity, m_ulUsageFlags, m_eIndexSize, m_ePool, pTmpDX9IndexBuffer);


	if (_bTransferData)
	{
		uint* uipIndexData = 0;
		uint* uipNewIndexData = 0;


		Lock(reinterpret_cast<void**>(&uipIndexData), D3DLOCK_READONLY);
		pTmpDX9IndexBuffer->Lock(0, 0, reinterpret_cast<void**>(&uipNewIndexData), D3DLOCK_DISCARD);


		memcpy(uipNewIndexData, uipIndexData, sizeof(uint) * m_uiCapacity);


		pTmpDX9IndexBuffer->Unlock();
		Unlock();
		FW_RELEASE(m_pDX9IndexBuffer);
	}


	m_uiCapacity = uiNewCapacity;
	m_pDX9IndexBuffer = pTmpDX9IndexBuffer;


	return (true);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Locks the index buffer so it can be written to.
*
* @author Bryce Booth
*
* @param _ppIndexData			Returns pointer to index buffer memory.
* @param _ulFlags				Flags used for locking.
* @param _uiNumIndices			Number of indices to lock, set 0 to lock all memory.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDX9IndexBuffer::Lock(void** _ppIndexData, ulong _ulFlags, uint _uiNumIndices)
{
	assert(m_bLocked == false);


	bool bReturn = false;
	uint uiMemoryLockSize = 0;


	if (m_eIndexSize == INDEXSIZE_16)
	{
		uiMemoryLockSize = _uiNumIndices * sizeof(short);
	}
	else
	{
		uiMemoryLockSize = _uiNumIndices * sizeof(int);
	}


	HRESULT hResult = m_pDX9IndexBuffer->Lock(0, uiMemoryLockSize, _ppIndexData, _ulFlags);


	if (FAILED(hResult))
	{
		bReturn = false;
		//TODO: Update error report. ("Could not lock index buffer.");
	}
	else
	{
		m_bLocked = true;
	}


	return (bReturn);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Unlocks the index buffer from locked state.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDX9IndexBuffer::Unlock()
{
	assert(m_bLocked == true);


	bool bReturn = false;


	HRESULT hResult = m_pDX9IndexBuffer->Unlock();


	if (FAILED(hResult))
	{
		bReturn = false;
		//TODO: Update error report. ("Could not unlock index buffer.");
	}
	else
	{
		m_bLocked = false;
	}


	return (bReturn);
}




/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates vertex buffer based on buffer type and number of primitives.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDX9IndexBuffer::InitialiseBuffer(CRenderer& _rRenderer)
{
	bool bReturn = true;


	if (m_eBufferType == BUFFERTYPE_STATIC)
	{
		m_ulUsageFlags = USAGEFLAG_WRITEONLY;
		m_ePool = MEMORYPOOL_DEFAULT;
	}
	else
	{
		m_ulUsageFlags = USAGEFLAG_DYNAMIC | USAGEFLAG_WRITEONLY;
		m_ePool = MEMORYPOOL_DEFAULT;
	}


	bReturn = _rRenderer.CreateDX9IndexBuffer(m_uiCapacity, m_ulUsageFlags, m_eIndexSize, m_ePool, m_pDX9IndexBuffer);


	return (bReturn);
}





uint
CDX9IndexBuffer::CalculateNumPrimitives(EPrimitiveType _ePrimitiveType, uint _uiNumIndices)
{
	uint uiNumPrimitives = 0;


	//Caluclate number of vertices
	switch(_ePrimitiveType)
	{
	case PRIMITIVETYPE_POINTLIST:
		uiNumPrimitives = _uiNumIndices;
		break;

	case PRIMITIVETYPE_LINELIST:
		uiNumPrimitives = _uiNumIndices / 2;
		break;

	case PRIMITIVETYPE_LINESTRIP:
		uiNumPrimitives = _uiNumIndices - 1;
		break;

	case PRIMITIVETYPE_TRIANGLELIST:
		uiNumPrimitives = _uiNumIndices / 3;
		break;

	case PRIMITIVETYPE_TRIANGLESTRIP:
		uiNumPrimitives = _uiNumIndices - 2;
		break;

	case PRIMITIVETYPE_TRIANGLEFAN:
		uiNumPrimitives = _uiNumIndices - 2;
		break;

	default:
		//TODO: Update error report. ("Unknown primitive type.");
		break;
	}


	return(uiNumPrimitives);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDX9IndexBuffer::Deinitialise()
{
	FW_RELEASE(m_pDX9IndexBuffer);
}