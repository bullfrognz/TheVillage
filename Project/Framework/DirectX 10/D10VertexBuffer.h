//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   D10VertexBuffer.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __D10VertexBuffer_H__
#define __D10VertexBuffer_H__


// Library Includes


// Local Includes
#include "Framework\VertexBuffer.h"


// Types


// Constants


// Prototypes
class CD10Renderer;


class CD10VertexBuffer : public IVertexBuffer
{

	// Member Functions
public:


			 CD10VertexBuffer();
	virtual ~CD10VertexBuffer();


	bool Initiailise(CD10Renderer* _pD10Renderer, const TDesc& _ktrBufferDesc);


	virtual bool Lock(ELockFlag _eLockFlag, void** _ppBufferData);
	virtual void Unlock();


	virtual bool UpdateRegion(IRenderer& _rRenderer, const void* _kpVertexData, uint _uiNumVertices, uint _uiIndexOffset);


	// Inline Functions
	virtual inline EPrimitiveType GetPrimitiveType() const;
	virtual inline EUsage GetBufferUsage() const;
	virtual inline ulong GetFvF() const;
	virtual inline uint GetSize() const;
	virtual inline uint GetStride() const;
	virtual inline uint GetCapacity() const;
	virtual inline uint GetInstanceId() const;


	inline ID3D10Buffer* GetBuffer();


protected:


	bool LockStatic(D3D10_MAP _eD10LockFlag, void** _ppVertexData);
	bool LockDynamic(D3D10_MAP _eD10LockFlag, void** _ppVertexData);


	bool ConvertLockFlag(ELockFlag _eLockFlag, D3D10_MAP& _erD10LockFlag);


private:


	void Deinitialise();


	CD10VertexBuffer(const CD10VertexBuffer& _krD10VertexBuffer);
	CD10VertexBuffer& operator = (const CD10VertexBuffer& _krD10VertexBuffer);


	// Member Variables
protected:


private:


	ID3D10Buffer* m_pVertexBuffer;


	EPrimitiveType m_ePrimitiveType;
	EUsage m_eUsage;


	ulong m_ulFvF;


	uint m_uiCapacity;
	uint m_uiStride;
	uint m_uiInstanceId;


	bool m_bLocked;


	static uint s_uiInstanceCount;


};


#include "D10VertexBuffer.inl"


#endif //__D10VertexBuffer_H__