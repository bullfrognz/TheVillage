//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   D10IndexBuffer.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


IIndexBuffer::EUsage
CD10IndexBuffer::GetBufferUsage() const
{
	return (m_eUsage);
}


IIndexBuffer::EIndexSize
CD10IndexBuffer::GetIndexSize() const
{
	return (m_eIndexSize);
}


uint
CD10IndexBuffer::GetCapacity() const
{
	return (m_uiCapacity);
}


uint
CD10IndexBuffer::GetInstanceId() const
{
	return (m_uiInstanceId);
}


ID3D10Buffer*
CD10IndexBuffer::GetBuffer()
{
	return (m_pIndexBuffer);
}