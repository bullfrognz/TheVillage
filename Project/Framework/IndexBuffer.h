//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   IndexBuffer.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __IndexBuffer_H__
#define __IndexBuffer_H__


// Library Includes


// Local Includes
#include "Buffer.h"


// Types


// Constants


// Prototypes


class IIndexBuffer : public IBuffer
{

	// Member Types
public:


	enum EIndexSize
	{
		INVALID_INDEXSIZE = -1,

		INDEXSIZE_16,
		INDEXSIZE_32,

		MAX_INDEXSIZE
	};


	struct TDesc
	{
		TDesc()
		{
			memset(this, 0, sizeof(TDesc));
		}


		uint* pInitialData;

		EUsage eUsage;
		EIndexSize eIndexSize;

		uint uiIndicesCount;
	};


	// Member Functions
public:


			 IIndexBuffer() {};
	virtual ~IIndexBuffer() {};


	virtual bool Lock(ELockFlag _eLockFlag, void** _ppBufferData) = 0;
	virtual void Unlock() = 0;


	// Inline Functions
	virtual inline EUsage GetBufferUsage() const = 0;
	virtual inline EIndexSize GetIndexSize() const = 0;
	virtual inline uint GetCapacity() const = 0;
	virtual inline uint GetInstanceId() const = 0;


protected:


private:


	IIndexBuffer(const IIndexBuffer& _krIndexBuffer);
	IIndexBuffer& operator = (const IIndexBuffer& _krIndexBuffer);


	// Member Variables
protected:


private:


};


#endif //__IndexBuffer_H__