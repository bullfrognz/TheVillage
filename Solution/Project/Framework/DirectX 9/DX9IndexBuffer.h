//
//  Bryce Booth
//  9 Park Hill Road
//  North Shore City
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   DX9IndexBuffer.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   brycebooth@hotmail.com
//


#pragma once


#ifndef __IGFEB11_IG500_INDEXEDBUFFER_H__
#define __IGFEB11_IG500_INDEXEDBUFFER_H__


// Library Includes


// Local Includes
#include "Framework\IndexBuffer.h"


// Types


// Constants


// Prototypes
class CRenderer;
class CVertexBuffer;
enum EBufferType;
enum EPrimitiveType;


class CDX9IndexBuffer : public IIndexBuffer
{

	// Member Functions
public:


	 CDX9IndexBuffer();
	~CDX9IndexBuffer();


	bool Initialise(CRenderer& _rRenderer, EBufferType _eBufferType, EIndexSize _eIndexSize, uint _uiNumIndices);


	bool Draw(CRenderer& _rRenderer, CVertexBuffer& _rVertexBuffer);


	bool Lock(void** _ppIndexData, ulong _ulFlags, uint _uiNumIndices = 0);
	bool Unlock();


	bool ExpandCapacity(CRenderer& _rRenderer, uint _uiNumIndices, bool _bTransferData);


	// Inline Functions
	inline void SetIndexDrawCount(uint _uiNumIndices);
	inline void SetMinIndex(uint _uiMinIndex);


	inline uint GetIndexCapacity();


protected:


private:


	bool InitialiseBuffer(CRenderer& _rRenderer);


	uint CalculateNumPrimitives(EPrimitiveType _ePrimitiveType, uint _uiNumPrimitives);


	void Deinitialise();


	CDX9IndexBuffer(const CDX9IndexBuffer& _krDX9IndexBuffer);
	CDX9IndexBuffer& operator = (const CDX9IndexBuffer& _krDX9IndexBuffer);


	// Member Variables
protected:


	IDirect3DDX9IndexBuffer9* m_pDX9IndexBuffer;


	EMemoryPool m_ePool;
	EBufferType m_eBufferType;
	EIndexSize m_eIndexSize;


	ulong m_ulUsageFlags;


	uint m_uiCapacity;
	uint m_uiMinIndex;
	uint m_uiDrawIndexCount;


	bool m_bLocked;


private:


};


#include "DX9IndexBuffer.inl"


#endif //__IGFEB11_IG500_INDEXEDBUFFER_H__