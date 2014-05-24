//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   D10VertexBuffer.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


IVertexBuffer::EPrimitiveType
CD10VertexBuffer::GetPrimitiveType() const
{
	return (m_ePrimitiveType);
}


IVertexBuffer::EUsage
CD10VertexBuffer::GetBufferUsage() const
{
	return (m_eUsage);
}


ulong
CD10VertexBuffer::GetFvF() const
{
	return (m_ulFvF);
}


uint
CD10VertexBuffer::GetSize() const
{
	return (m_uiCapacity * m_uiStride);
}


uint
CD10VertexBuffer::GetStride() const
{
	return (m_uiStride);
}


uint
CD10VertexBuffer::GetCapacity() const
{
	return (m_uiCapacity);
}


ID3D10Buffer*
CD10VertexBuffer::GetBuffer()
{
	return (m_pVertexBuffer);
}


uint
CD10VertexBuffer::GetInstanceId() const
{
	return (m_uiInstanceId);
}