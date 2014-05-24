//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   Macros.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __IGFEB11_IG500_MACROS_H__
#define __IGFEB11_IG500_MACROS_H__


// Library Includes
#include <map>
#include <vector>
#include <assert.h>


// Local Includes


// Implementation


#if _DEBUG

#define FW_BREAK() _CrtDbgBreak();

#else

#define FW_BREAK() ;

#endif


#define FW_VALIDATE(Function)\
if (Function == false)\
{\
	assert(false);\
	return (false);\
}


#define FW_RELEASE(Variable)\
{\
	if (Variable != 0)\
	{\
		Variable->Release();\
		Variable = 0;\
	}\
}


#define FW_DELETE(Variable)\
{\
	delete Variable;\
	Variable = 0;\
}


#define FW_ADELETE(ArrayVariable)\
{\
	delete[] ArrayVariable;\
	ArrayVariable = 0;\
}


#define FW_DELETEMAP(KeyType, ValueType, Variable)\
{\
	std::map<KeyType, ValueType>::iterator __iterElement;\
	__iterElement = Variable.begin();\
	\
	while (__iterElement != Variable.end())\
	{\
		FW_DELETE((*__iterElement).second);\
		\
		\
		__iterElement = Variable.erase(__iterElement);\
	}\
}


#define FW_DELETEVECTOR(Type, Variable)\
{\
	std::vector<Type>::iterator __iterElement;\
	__iterElement = Variable.begin();\
	\
	while (__iterElement != Variable.end())\
	{\
		FW_DELETE((*__iterElement));\
		\
		\
		__iterElement = Variable.erase(__iterElement);\
	}\
}


#define FW_DELETEARRAY(Variable, NumElements)\
{\
	for (uint __iIndex = 0; __iIndex < NumElements; ++__iIndex)\
	{\
		FW_DELETE(Variable[__iIndex]);\
	}\
}


#endif //__IGFEB11_IG500_MACROS_H__