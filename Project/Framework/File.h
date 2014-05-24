//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   File.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __File_H__
#define __File_H__


// Library Includes
#include <iostream>
#include <fstream>
#include <string>


// Local Includes
#include "Defines\DataTypes.h"


// Types


// Prototypes


class CFile
{

	// Member Functions
public:


	 CFile();
	~CFile();


	bool Initialise(const char* _kcpFile);


	bool Read(uint _uiByteOffset, uint _uiNumBytes, void* _pBuffer);
	bool Write(void* _pData, uint _uiNumBytes);


	// Inline Functions
	inline uint GetSize() const;


protected:


private:


	void Deinitialise();


	CFile(const CFile& _krFile);
	CFile& operator = (const CFile& _krFile);


	// Member Variables
protected:


private:


	std::fstream m_FileStream;


	uint m_uiSize;


};


#include "File.inl"


#endif //__File_H__