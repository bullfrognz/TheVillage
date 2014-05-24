//
//  Bryce Booth
//  9 Park Hill Road
//  North Shore City
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   DX9VertexBuffer.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   brycebooth@hotmail.com
//


// Library Includes
#include <assert.h>


// Local Includes
#include "Defines/Macros.h"
#include "Framework/Renderer.h"


// This Include
#include "DX9VertexBuffer.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CDX9VertexBuffer constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDX9VertexBuffer::CDX9VertexBuffer()
: m_pDX9VertexBuffer(0)
, m_ed3dPool(MEMORYPOOL_INVALID)
, m_eBufferType(BUFFERTYPE_INVALID)
, m_ePrimitiveType(PRIMITIVETYPE_INVALID)
, m_ulUsageFlags(0)
, m_ulFvF(0)
, m_uiVertexStride(0)
, m_uiCapacity(0)
, m_bLocked(false)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CDX9VertexBuffer deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDX9VertexBuffer::~CDX9VertexBuffer()
{
	Deinitialise();
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialisings the class instance before use.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDX9VertexBuffer::Initialise(CRenderer& _rRenderer, EBufferType _eBufferType, EMemoryPool _eMemoryPool, uint _uiVertexStride, ulong _ulFvF, EPrimitiveType _ePrimitiveType, uint _uiNumVertices)
{
	m_eBufferType = _eBufferType;
	m_uiVertexStride = _uiVertexStride;
	m_ulFvF = _ulFvF;
	m_ePrimitiveType = _ePrimitiveType;
	m_uiCapacity = _uiNumVertices;


	FW_VALIDATE(InitialiseBuffer(_rRenderer, _eMemoryPool));


	return (true);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Prepares the renderer's device to start renderering from this vertex buffer.
*
* @author Bryce Booth
*
* @param _rRenderer		Renderer instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDX9VertexBuffer::PrepareDevice(CRenderer& _rRenderer)
{
	bool bReturn = true;


	//bReturn = _rRenderer.GetDeviceStates().SetStreamSource(m_pDX9VertexBuffer, m_uiVertexStride);


	if (bReturn)
	{
	//	bReturn = _rRenderer.GetDeviceStates().SetFVF(m_ulFvF);
	}


	return (bReturn);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the stream source and FvF on the device and renders the buffer's vertices.
*
* @author Bryce Booth
*
* @param _rRenderer				Renderer instance.
* @param _uiNumVertices			Override number of vertices to draw.
* @param _uiStartVertex			First vertex offset.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDX9VertexBuffer::Draw(CRenderer& _rRenderer, uint _uiNumPrimitives, uint _uiStartPrimitive)
{
	bool bReturn = false;


	if (_uiNumPrimitives == 0)
	{
	//	_uiNumPrimitives = CalculateNumPrimitives(m_uiCapacity);
	}


	//PrepareDevice(_rRenderer);


	//bReturn = _rRenderer.DrawPrimitive(static_cast<D3DPRIMITIVETYPE>(m_ePrimitiveType), CalculateNumVertices(_uiNumPrimitives), _uiNumPrimitives);


	return (bReturn);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Locks the vertex buffer so it can be written to.
*
* @author Bryce Booth
*
* @param _ppVertexData			Returns pointer to vertex buffer memory.
* @param _ulFlags				Flags used for locking.
* @param _uiNumVertices			Number of vertices to lock, set 0 to lock all memory.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDX9VertexBuffer::Lock(void** _ppVertexData, ulong _ulFlags, uint _uiNumVertices)
{
	assert(m_bLocked == false);


	bool bReturn = false;


	/*
	HRESULT hResult = m_pDX9VertexBuffer->Lock(0, _uiNumVertices  * m_uiVertexStride, _ppVertexData, _ulFlags);


	if (FAILED(hResult))
	{
		bReturn = false;
		//TODO: Update error report. ("Could not lock vertex buffer.");
	}
	else
	{
		m_bLocked = true;
	}
	*/


	return (bReturn);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Unlocks the vertex buffer from locked state.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDX9VertexBuffer::Unlock()
{
	assert(m_bLocked == true);


	bool bReturn = false;


	/*
	HRESULT hResult = m_pDX9VertexBuffer->Unlock();


	if (FAILED(hResult))
	{
		bReturn = false;
		//TODO: Update error report. ("Could not unlock vertex buffer.");
	}
	else
	{
		m_bLocked = false;
	}
	*/


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
* @param _rRenderer		Renderer instance to create buffer with.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDX9VertexBuffer::InitialiseBuffer(CRenderer& _rRenderer, EMemoryPool _eMemoryPool)
{
	bool bReturn = true;
	m_ed3dPool = _eMemoryPool;


	if (m_eBufferType == BUFFERTYPE_STATIC)
	{
		m_ulUsageFlags = USAGEFLAG_WRITEONLY;
	}
	else
	{
		m_ulUsageFlags = USAGEFLAG_DYNAMIC | USAGEFLAG_WRITEONLY;
	}


	//bReturn = _rRenderer.CreateDX9VertexBuffer(m_uiCapacity * m_uiVertexStride, m_ulUsageFlags, m_ulFvF, m_ed3dPool, m_pDX9VertexBuffer);


	return (bReturn);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Calculates the number of primitives in a given amount of vertices based on the buffer's primitive type.
*
* @author Bryce Booth
*
* @param _uiNumVertices		Number of vertices to convert to primitives.
*
*---------------------------------------------------------------------------------------------------------------------------*/

uint
CDX9VertexBuffer::CalculateNumPrimitives(uint _uiNumVertices)
{
	uint uiNumPrimitives = 0;


	/*
	// Caluclate number of vertices
	switch(m_ePrimitiveType)
	{
	case PRIMITIVETYPE_POINTLIST:
		uiNumPrimitives = _uiNumVertices;
		break;

	case PRIMITIVETYPE_LINELIST:
		uiNumPrimitives = _uiNumVertices / 2;
		break;

	case PRIMITIVETYPE_LINESTRIP:
		uiNumPrimitives = _uiNumVertices - 1;
		break;

	case PRIMITIVETYPE_TRIANGLELIST:
		uiNumPrimitives = _uiNumVertices / 3;
		break;

	case PRIMITIVETYPE_TRIANGLESTRIP:
		uiNumPrimitives = _uiNumVertices - 2;
		break;

	case PRIMITIVETYPE_TRIANGLEFAN:
		uiNumPrimitives = _uiNumVertices - 2;
		break;

	default:
		//TODO: Update error report. ("Unknown primitive type.");
		break;
	}
	*/


	return(uiNumPrimitives);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Calculates the number of vertices in a given amount of primitives based on the buffer's primitive type.
*
* @author Bryce Booth
*
* @param _uiNumPrimitives		Number of primitives to convert to vertices.
*
*---------------------------------------------------------------------------------------------------------------------------*/

uint
CDX9VertexBuffer::CalculateNumVertices(uint _uiNumPrimitives)
{
	//Default
	uint uiNumVertices = 0;


	/*
	//Caluclate number of vertices
	switch(m_ePrimitiveType)
	{
	case PRIMITIVETYPE_POINTLIST:
		uiNumVertices = _uiNumPrimitives;
		break;

	case PRIMITIVETYPE_LINELIST:
		uiNumVertices = _uiNumPrimitives * 2;
		break;

	case PRIMITIVETYPE_LINESTRIP:
		uiNumVertices = _uiNumPrimitives + 1;
		break;

	case PRIMITIVETYPE_TRIANGLELIST:
		uiNumVertices = _uiNumPrimitives * 3;
		break;

	case PRIMITIVETYPE_TRIANGLESTRIP:
		uiNumVertices = _uiNumPrimitives + 2;
		break;

	case PRIMITIVETYPE_TRIANGLEFAN:
		uiNumVertices = _uiNumPrimitives + 2;
		break;

	default:
		//TODO: Update error report. ("Unknown primitive type.");
		break;
	}
	*/


	return(uiNumVertices);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDX9VertexBuffer::Deinitialise()
{
	//FW_RELEASE(m_pDX9VertexBuffer);
}