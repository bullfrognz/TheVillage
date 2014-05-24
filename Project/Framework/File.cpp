//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   File.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// This Include
#include "File.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* File constructors
*
*---------------------------------------------------------------------------------------------------------------------------*/

CFile::CFile()
: m_uiSize(0)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* File deconstructor
*
*---------------------------------------------------------------------------------------------------------------------------*/

CFile::~CFile()
{
	Deinitialise();
}





bool
CFile::Initialise(const char* _kcpFile)
{
	m_FileStream.open(_kcpFile, std::fstream::binary | std::fstream::in);


	return (m_FileStream.is_open());
}





bool
CFile::Read(uint _uiByteOffset, uint _uiNumBytes, void* _pBuffer)
{
	m_FileStream.seekg (0, std::fstream::end);
	//long	length = m_FileStream.tellg();


	m_FileStream.seekg(_uiByteOffset, std::fstream::beg);


	//uint GBefore = m_FileStream.gcount();


	m_FileStream.read(reinterpret_cast<char*>(_pBuffer), _uiNumBytes);


	//uint GAfter = m_FileStream.gcount();


	return (m_FileStream.fail());
}


bool
CFile::Write(void* _pData, uint _uiNumBytes)
{
	return (true);
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





void
CFile::Deinitialise()
{
	m_FileStream.close();
}