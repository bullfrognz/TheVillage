//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   RawImage.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


uint
CRawImage::GetWidth() const
{
	return (m_uiWidth);
}


uint
CRawImage::GetHeight() const
{
	return (m_uiHeight);
}


ushort
CRawImage::GetStride() const
{
	return (m_usStride);
}