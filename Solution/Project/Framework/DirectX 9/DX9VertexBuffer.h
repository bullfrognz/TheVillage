//
//  Bryce Booth
//  9 Park Hill Road
//  North Shore City
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   DX9VertexBuffer.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   brycebooth@hotmail.com
//


#pragma once


#ifndef __IGFEB11_IG500_DX9VertexBuffer_H__
#define __IGFEB11_IG500_DX9VertexBuffer_H__


// Library Includes


// Local Includes
#include "Defines\DataTypes.h"
#include "Defines\Buffer.h"
#include "Framework\VertexBuffer.h"


// Types


// Constants


// Prototypes
struct IDirect3DDX9VertexBuffer9;
class CRenderer;


class CDX9VertexBuffer : public IVertexBuffer
{

	// Member Functions
public:


			 CDX9VertexBuffer();
	virtual ~CDX9VertexBuffer();


	bool Initialise(CRenderer& _rRenderer, EBufferType _eBufferType, EMemoryPool _eMemoryPool, uint _uiVertexStride, ulong _ulFvF, EPrimitiveType _ePrimitiveType, uint _uiNumVertices);


	bool PrepareDevice(CRenderer& _rRenderer);


	bool Draw(CRenderer& _rRenderer, uint _uiNumPrimitives = 0, uint _uiStartPrimitive = 0);


	bool Lock(void** _ppVertexData, ulong _ulFlags, uint _uiNumVertices = 0);
	bool Unlock();


	bool ExpandCapacity(CRenderer& _rRenderer, uint _uiNumVertices, bool _bTransferData);


	// Inline Functions
	inline EBufferType GetBufferType() const;
	inline EPrimitiveType GetPrimitiveType() const;
	inline ulong GetFvF() const;
	inline uint GetVertexStride() const;
	inline uint GetNumVertices() const;


protected:


private:


	bool InitialiseBuffer(CRenderer& _rRenderer, EMemoryPool _eMemoryPool);


	uint CalculateNumPrimitives(uint _uiNumVertices);
	uint CalculateNumVertices(uint _uiNumPrimitives);


	void Deinitialise();


	CDX9VertexBuffer(const CDX9VertexBuffer& _krDX9VertexBuffer);
	CDX9VertexBuffer& operator = (const CDX9VertexBuffer& _krDX9VertexBuffer);


	// Member Variables
public:


protected:


	IDirect3DDX9VertexBuffer9* m_pDX9VertexBuffer;


	EMemoryPool m_ed3dPool;
	EBufferType m_eBufferType;
	EPrimitiveType m_ePrimitiveType;


	ulong m_ulUsageFlags;
	ulong m_ulFvF;


	uint m_uiCapacity;
	uint m_uiVertexStride;


	bool m_bLocked;


private:


};


#include "DX9VertexBuffer.inl"


#endif //__IGFEB11_IG500_DX9VertexBuffer_H__