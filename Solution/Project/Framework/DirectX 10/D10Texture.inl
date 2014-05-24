//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   D10Texture.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


ID3D10ShaderResourceView*
CD10Texture::GetResourceView()
{
	return (m_pResourceView);
}


uint
CD10Texture::GetWidth() const
{
	return (m_uiWidth);
}


uint
CD10Texture::GetHeight() const
{
	return (m_uiHeight);
}


ITexture::EFormat
CD10Texture::GetFormat() const
{
	return (m_eFormat);
}


uint
CD10Texture::GetTexelSize() const
{
	return (m_uiTexelSize);
}


uint
CD10Texture::GetRowPitch() const
{
	return (m_uiRowPitch);
}


uint
CD10Texture::GetDepthPitch() const
{
	return (m_uiDepthPitch);
}


uint
CD10Texture::GetInstanceId() const
{
	return (m_uiInstanceId);
}