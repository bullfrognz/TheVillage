//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   D10IndexBuffer.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __D10IndexBuffer_H__
#define __D10IndexBuffer_H__


// Library Includes


// Local Includes
#include "Framework\IndexBuffer.h"


// Types


// Constants


// Prototypes
struct ID3D10Buffer;

class CD10Renderer;


class CD10IndexBuffer : public IIndexBuffer
{

	// Member Functions
public:


			 CD10IndexBuffer();
	virtual ~CD10IndexBuffer();


	bool Initiailise(CD10Renderer* _pD10Renderer, const TDesc& _ktrBufferDesc);


	virtual bool Lock(ELockFlag _eLockFlag, void** _ppBufferData);
	virtual void Unlock();


	// Inline Functions
	virtual inline EUsage GetBufferUsage() const;
	virtual inline EIndexSize GetIndexSize() const;
	virtual inline uint GetCapacity() const;
	virtual inline uint GetInstanceId() const;


	inline ID3D10Buffer* GetBuffer();


protected:


private:


	void Deinitialise();


	CD10IndexBuffer(const CD10IndexBuffer& _krD10IndexBuffer);
	CD10IndexBuffer& operator = (const CD10IndexBuffer& _krD10IndexBuffer);


	// Member Variables
protected:


private:


	ID3D10Buffer* m_pIndexBuffer;


	EUsage m_eUsage;
	EIndexSize m_eIndexSize;


	uint m_uiCapacity;
	uint m_uiInstanceId;


	bool m_bLocked;


	static uint s_uiInstanceCount;


};


#include "D10IndexBuffer.inl"


#endif //__D10IndexBuffer_H__