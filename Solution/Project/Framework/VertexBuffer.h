//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   VertexBuffer.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __VertexBuffer_H__
#define __VertexBuffer_H__


// Library Includes


// Local Includes
#include "Framework\Buffer.h"


// Types


// Constants


// Prototypes


class IVertexBuffer : public IBuffer
{

	// Member Functions
public:


	enum EPrimitiveType
	{
		INVALID_PRIMITIVETYPE = -1,

		PRIMITIVETYPE_POINTLIST,
		PRIMITIVETYPE_LINELIST,
		PRIMITIVETYPE_LINESTRIP,
		PRIMITIVETYPE_TRIANGLELIST,
		PRIMITIVETYPE_TRIANGLESTRIP,
		PRIMITIVETYPE_TRIANGLEFAN,

		MAX_PRIMITIVETYPE
	};


	struct TDesc
	{
		TDesc()
		{
			memset(this, 0, sizeof(TDesc));
		}

		void* pInitialData;

		EPrimitiveType ePrimitiveType;
		EUsage eUsage;

		ulong ulFVF;
		uint uiNumVertices;
		uint uiStride;
	};


			 IVertexBuffer() {};
	virtual ~IVertexBuffer() {};


	virtual bool Lock(ELockFlag _eLockFlag, void** _ppBufferData) = 0;
	virtual void Unlock() = 0;


	virtual bool UpdateRegion(IRenderer& _rRenderer, const void* _kpVertexData, uint _uiNumVertices, uint _uiIndexOffset) = 0;


	// Inline Functions
	virtual inline EPrimitiveType GetPrimitiveType() const = 0;
	virtual inline EUsage GetBufferUsage() const = 0;
	virtual inline ulong GetFvF() const = 0;
	virtual inline uint GetSize() const = 0;
	virtual inline uint GetStride() const = 0;
	virtual inline uint GetCapacity() const = 0;
	virtual inline uint GetInstanceId() const = 0;


protected:


private:


	IVertexBuffer(const IVertexBuffer& _krVertexBuffer);
	IVertexBuffer& operator = (const IVertexBuffer& _krVertexBuffer);


	// Member Variables
protected:


private:


};


#endif //__VertexBuffer_H__