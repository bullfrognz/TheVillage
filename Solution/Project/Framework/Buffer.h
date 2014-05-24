//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Buffer.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Buffer_H__
#define __Buffer_H__


// Library Includes


// Local Includes
#include "Defines\DataTypes.h"


// Types


// Prototypes


class IBuffer
{

	// Member Types
public:


	enum EUsage
	{
		INVALID_BUFFERUSAGE	= -1,

		USAGE_STATIC,		// CPUACCESS_NONE
		USAGE_DYNAMIC,		// CPUACCESS_READWRITE
		USAGE_STAGING,		// DirectX 10 Only

		MAX_USAGE
	};


	enum ELockFlag
	{
		INVALID_LOCKFLAG			= -1,

		LOCKFLAG_READONLY			= 1,
		LOCKFLAG_READWRITE			= 1 << 1,
		LOCKFLAG_WRITEONLY			= 1 << 2,
		LOCKFLAG_WRITEDISCARD		= 1 << 3,
		LOCKFLAG_WRITENOOVERWRITE	= 1 << 4,

		MAX_LOCKFLAG
	};


	enum ECPUAccess
	{ 
		INVALID_CPUACCESS = -1,

		CPUACCESS_NONE,
		CPUACCESS_WRITE,
		CPUACCESS_READ,
		CPUACCESS_READWRITE,

		MAX_CPUACCESS
	};


	// Member Functions
public:


			 IBuffer() {};
	virtual ~IBuffer() {};


	// Inline Functions
	virtual inline uint GetInstanceId() const = 0;


protected:


private:


	// Member Variables
protected:


private:


};


#endif //__Buffer_H__