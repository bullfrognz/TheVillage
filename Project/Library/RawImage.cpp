//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   RawImage.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Framework\File.h"
#include "Defines\Macros.h"


// This Include
#include "RawImage.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* RawImage constructors
*
*---------------------------------------------------------------------------------------------------------------------------*/

CRawImage::CRawImage()
:m_pFile(0)
, m_uiWidth(0)
, m_uiHeight(0)
, m_usStride(0)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* RawImage deconstructor
*
*---------------------------------------------------------------------------------------------------------------------------*/

CRawImage::~CRawImage()
{
	Deinitialise();
}





bool
CRawImage::Initialise(const char* _kcpFile, uint _uiWidth, uint _uiHeight, ushort _usStride)
{
	m_uiWidth = _uiWidth;
	m_uiHeight = _uiHeight;
	m_usStride = _usStride;
	m_uiRowStride = m_uiWidth * m_usStride;


	FW_VALIDATE(InitialiseFile(_kcpFile))


	return (true);
}





bool
CRawImage::ReadLine(uint _uiStartRow, uint _uiStartColumn, uint _uiNumTexels, void* _pData)
{
	const uint kuiRowOffset    = _uiStartRow * m_uiRowStride;
	const uint kuiColumnOffset = _uiStartColumn * m_usStride;
	const uint kuiStartOffset  = kuiRowOffset + kuiColumnOffset;
	const uint kuiNumByteRead  = _uiNumTexels * m_usStride;


	//uint uiByteOffset = (tSection.iTop * uiHeightmapRowSize + uiRow * uiHeightmapRowSize) + (tSection.iLeft * sizeof(ushort));
	//uint uiNumBuyes = (tSection.iRight - tSection.iLeft) * sizeof(ushort);


	// Read height data for row
	m_pFile->Read(kuiStartOffset, kuiNumByteRead, _pData);



	return (true);
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





bool
CRawImage::InitialiseFile(const char* _kcpFile)
{
	m_pFile = new CFile();
	FW_VALIDATE(m_pFile->Initialise(_kcpFile));


	return (true);
}





void
CRawImage::Deinitialise()
{
	FW_DELETE(m_pFile)
}