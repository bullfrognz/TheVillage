//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   RawImage.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __RawImage_H__
#define __RawImage_H__


// Library Includes


// Local Includes


// Types


// Prototypes
class CFile;


class CRawImage
{

	// Member Functions
public:


	 CRawImage();
	~CRawImage();


	bool Initialise(const char* _kcpFile, uint _uiWidth, uint _uiHeight, ushort _usStride);


	bool ReadLine(uint _uiStartRow, uint _uiStartColumn, uint _uiNumTexels, void* _pData);
	bool ReadSection();


	// Inline Functions
	inline uint   GetWidth() const;
	inline uint   GetHeight() const;
	inline ushort GetStride() const;


protected:


private:


	bool InitialiseFile(const char* _kcpFile);


	void Deinitialise();


	CRawImage(const CRawImage& _krRawImage);
	CRawImage& operator = (const CRawImage& _krRawImage);


	// Member Variables
protected:


private:


	CFile* m_pFile;


	uint m_uiWidth;
	uint m_uiHeight;
	uint m_uiRowStride;


	ushort m_usStride;


};


#include "RawImage.inl"


#endif //__RawImage_H__