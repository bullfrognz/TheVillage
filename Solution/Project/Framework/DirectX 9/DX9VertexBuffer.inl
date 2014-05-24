//
//  Bryce Booth
//  9 Park Hill Road
//  North Shore City
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   DX9VertexBuffer.inl
//
//  Author    :   Bryce Booth
//  Mail      :   brycebooth@hotmail.com
//


// Library Includes


// Local Includes


// Implementation


EBufferType
CDX9VertexBuffer::GetBufferType() const
{
	return (m_eBufferType);
}


EPrimitiveType
CDX9VertexBuffer::GetPrimitiveType() const
{
	return (m_ePrimitiveType);
}


ulong
CDX9VertexBuffer::GetFvF() const
{
	return (m_ulFvF);
}


uint
CDX9VertexBuffer::GetVertexStride() const
{
	return (m_uiVertexStride);
}


uint
CDX9VertexBuffer::GetNumVertices() const
{
	return (m_uiCapacity);
}