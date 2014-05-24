//
//  Bryce Booth
//  9 Park Hill Road
//  North Shore City
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   DX9IndexBuffer.inl
//
//  Author    :   Bryce Booth
//  Mail      :   brycebooth@hotmail.com
//


// Library Includes
#include <assert.h>


// Local Includes


// Implementation


void
CDX9IndexBuffer::SetIndexDrawCount(uint _uiNumIndices)
{
	assert(_uiNumIndices <= m_uiCapacity);


	m_uiDrawIndexCount = _uiNumIndices;
}


void
CDX9IndexBuffer::SetMinIndex(uint _uiMinIndex)
{
	assert(_uiMinIndex < m_uiCapacity);


	m_uiMinIndex = _uiMinIndex;
}


uint
CDX9IndexBuffer::GetIndexCapacity()
{
	return (m_uiCapacity);
}