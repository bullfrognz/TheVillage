//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   Segment.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Defines\Macros.h"
#include "Utilities\MathUtilities.h"
#include "Framework\Texture.h"
#include "Framework\Renderer.h"
#include "Scene\Game\TerrainVertex.h"


// This Include
#include "Segment.h"


// Static Variables
uint CSegment::s_uiReffCount = 0;
CSegment::TIndicesInfo CSegment::s_tIndicesInfo[MAX_TYPE];


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* Segment constructors
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSegment::CSegment()
: m_pAABBox(0)
, m_uspHeightmap(0)
, m_eType(INVALID_TYPE)
, m_fPositionX(0)
, m_fPositionZ(0)
, m_fHeightScale(0)
, m_uiVerticesOffset(0)
, m_uiNumVertices(0)
, m_bActive(false)
, m_bUpdateBounds(false)
{
	memset(&m_tNeighbourHood, 0, sizeof(TNeighbourhood));
	memset(&m_tLayoutDesc, 0, sizeof(TLayout));


	++ s_uiReffCount;
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Segment deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSegment::~CSegment()
{
	Deinitialise();


	-- s_uiReffCount;
}





bool
CSegment::Initialise(const TLayout& _ktrLayoutDesc, const TNeighbourhood& _ktrNeighbourhood)
{
	m_tNeighbourHood = _ktrNeighbourhood;
	m_tLayoutDesc = _ktrLayoutDesc;
	m_uiNumVertices = m_tLayoutDesc.uiWidth * m_tLayoutDesc.uiLength;
	m_uiVerticesOffset = (m_uiNumVertices * m_tLayoutDesc.uiCountX * m_tLayoutDesc.uiIndexZ) + m_tLayoutDesc.uiIndexX * m_uiNumVertices;


	FW_VALIDATE(InitialiseHeightmap());
	FW_VALIDATE(InitialiseAABBox());


	UpdateIndicesGroup();
	

	return (true);
}





void
CSegment::ApplyVertexPositions(CTerrainVertex* _pVertexData)
{
	const float kfHalfWidth = static_cast<float>(m_tLayoutDesc.uiLength) / 2.0f;
	const float kfHalfHeight = static_cast<float>(m_tLayoutDesc.uiWidth)  / 2.0f;


	for (uint uiZ = 0; uiZ < m_tLayoutDesc.uiLength; ++ uiZ)
	{
		const float kfVertexOffsetZ  = static_cast<float>(uiZ);
		const uint kuiLengthmapRowOffset = uiZ * m_tLayoutDesc.uiWidth;


		for(uint uiX = 0; uiX < m_tLayoutDesc.uiWidth; ++ uiX)
		{
			const float kfVertexOffsetX = static_cast<float>(uiX);


			_pVertexData[uiZ * m_tLayoutDesc.uiLength + uiX].Position().Set(kfVertexOffsetX + m_fPositionX,
																			static_cast<float>(m_uspHeightmap[kuiLengthmapRowOffset + uiX]) / m_fHeightScale,
																			kfVertexOffsetZ + m_fPositionZ);
		}
	}


	// Update AABBox
	if (m_bUpdateBounds)
	{
		UpdateAABBoxBounds();


		m_bUpdateBounds = false;
	}
}





void
CSegment::ApplyVertexNormals(CTerrainVertex* _pVertexData, const CSegment* _kpSegments)
{
	for (uint uiZ = 0; uiZ < m_tLayoutDesc.uiLength; ++ uiZ)
	{
		for (uint uiX = 0; uiX < m_tLayoutDesc.uiWidth; ++ uiX)
		{
			CTerrainVertex& rCurrentVertex = _pVertexData[(uiZ * m_tLayoutDesc.uiLength) + uiX];
			CTerrainVertex* pBelow = 0;
			CTerrainVertex* pLeft = 0;


			// Clear previous normal
			rCurrentVertex.Normal().Set(0.0f, 0.0f, 0.0f);


			if (uiZ > 0)
			{
				pBelow = &_pVertexData[(uiZ - 1) * m_tLayoutDesc.uiLength + uiX];
			}


			if (uiX > 0)
			{
				pLeft = &_pVertexData[uiZ * m_tLayoutDesc.uiLength + (uiX - 1)];
			}


			if (pBelow != 0 &&
				pLeft != 0)
			{
				CVector3 vU = pBelow->Position() - rCurrentVertex.Position();
				CVector3 vV = pLeft->Position() - rCurrentVertex.Position();


				CVector3 vNormal = vU.Cross(vV);


				pBelow->Normal() += vNormal;
				pLeft->Normal() += vNormal;
				rCurrentVertex.Normal() += vNormal;
			}
		}
	}


	// Normalise normals
	for(uint uiZ = 0; uiZ < m_tLayoutDesc.uiLength; ++ uiZ)
	{
		for(uint uiX = 0; uiX < m_tLayoutDesc.uiWidth; ++ uiX)
		{
			_pVertexData[uiZ * m_tLayoutDesc.uiLength + uiX].Normal().Normalise();
		}
	}
}





void
CSegment::ApplyVertexTextureCoords(CTerrainVertex* _pVertexData)
{
	const float kfPerVertexU = 4.0f / m_tLayoutDesc.uiWidth;
	const float kfPerVertexV = 4.0f / m_tLayoutDesc.uiLength;


	for (uint uiZ = 0; uiZ < m_tLayoutDesc.uiLength; ++ uiZ)
	{
		const float kfTextureV = (4.0f * m_tLayoutDesc.uiIndexZ) + (kfPerVertexU * uiZ);


		for(uint uiX = 0; uiX < m_tLayoutDesc.uiWidth; ++ uiX)
		{
			const float kfTextureU = (4.0f * m_tLayoutDesc.uiIndexX) + (kfPerVertexV * uiX);


			_pVertexData[uiZ * m_tLayoutDesc.uiLength + uiX].UV().Set(kfTextureU, kfTextureV);
		}
	}
}





CSegment&
CSegment::operator = (const CSegment& _krSegment)
{
	m_uspHeightmap = _krSegment.m_uspHeightmap;
	m_pAABBox = _krSegment.m_pAABBox;
	m_bUpdateBounds = _krSegment.m_bUpdateBounds;
	m_bActive = _krSegment.m_bActive;


	return (*this);
}





void
CSegment::GenerateGlobalIndices(const TLayout& _ktrLayoutDesc, uint*& _prIndexData, uint& _uirNumIndices)
{
	// Indices groups
	std::vector<uint> aSelfOnlyIndices;
	std::vector<uint> aRightOnlyIndices;
	std::vector<uint> aAboveOnlyIndices;
	std::vector<uint> aRightAboveIndices;


	// Generate indices
	GenerateIndices(_ktrLayoutDesc, false, false, aSelfOnlyIndices);
	GenerateIndices(_ktrLayoutDesc, false, true, aRightOnlyIndices);
	GenerateIndices(_ktrLayoutDesc, true, false, aAboveOnlyIndices);
	GenerateIndices(_ktrLayoutDesc, true, true, aRightAboveIndices);


	// Calculate total indices
	_uirNumIndices = aSelfOnlyIndices.size();
	_uirNumIndices += aRightOnlyIndices.size();
	_uirNumIndices += aAboveOnlyIndices.size();
	_uirNumIndices += aRightAboveIndices.size();


	// Create pool
	_prIndexData = new uint[_uirNumIndices];


	// Transfer generated indices
	uint uiOffset = 0;


	memcpy(_prIndexData + uiOffset, &aSelfOnlyIndices[0], sizeof(uint) * aSelfOnlyIndices.size());
	s_tIndicesInfo[TYPE_ONE].uiCount = aSelfOnlyIndices.size();
	s_tIndicesInfo[TYPE_ONE].uiOffset = uiOffset;
	uiOffset += aSelfOnlyIndices.size();


	memcpy(_prIndexData + uiOffset, &aRightOnlyIndices[0], sizeof(uint) * aRightOnlyIndices.size());
	s_tIndicesInfo[TYPE_TWO].uiCount = aRightOnlyIndices.size();
	s_tIndicesInfo[TYPE_TWO].uiOffset = uiOffset;
	uiOffset += aRightOnlyIndices.size();


	memcpy(_prIndexData + uiOffset, &aAboveOnlyIndices[0], sizeof(uint) * aAboveOnlyIndices.size());
	s_tIndicesInfo[TYPE_THREE].uiCount = aAboveOnlyIndices.size();
	s_tIndicesInfo[TYPE_THREE].uiOffset = uiOffset;
	uiOffset += aAboveOnlyIndices.size();


	memcpy(_prIndexData + uiOffset, &aRightAboveIndices[0], sizeof(uint) * aRightAboveIndices.size());
	s_tIndicesInfo[TYPE_FOUR].uiCount = aRightAboveIndices.size();
	s_tIndicesInfo[TYPE_FOUR].uiOffset = uiOffset;
}





/********************************
            Protected
*********************************/





void
CSegment::UpdateAABBoxBounds()
{
	const float kfHalfWidth = m_tLayoutDesc.uiWidth / 2.0f;
	const float kfHalfLength = m_tLayoutDesc.uiLength / 2.0f;
	
	
	// Find max & min height
	ushort usMinHeight = -1;
	ushort usMaxHeight = 0;


	for (uint uiZ = 0; uiZ < m_tLayoutDesc.uiLength; ++ uiZ)
	{
		for (uint uiX = 0; uiX < m_tLayoutDesc.uiWidth; ++ uiX)
		{
			ushort usVertexHeight = m_uspHeightmap[uiZ * m_tLayoutDesc.uiWidth + uiX];


			usMinHeight = MathUtilities::Min(usMinHeight, usVertexHeight);
			usMaxHeight = MathUtilities::Max(usMaxHeight, usVertexHeight);
		}
	}


	// Scale heights
	float fMinHeight = static_cast<float>(usMinHeight) / m_fHeightScale;
	float fMaxHeight = static_cast<float>(usMaxHeight) / m_fHeightScale;


	float fDifference = fMaxHeight - fMinHeight;
	const float kfHalfHeight = fDifference / 2.0f;



	float fPositionX = m_fPositionX + kfHalfWidth;
	float fPositionY = fMaxHeight - kfHalfHeight;
	float fPositionZ = m_fPositionZ + kfHalfLength;
	CVector3 vPosition(fPositionX, fPositionY, fPositionZ);


	m_pAABBox->SetBounds(vPosition, kfHalfWidth, kfHalfHeight);
}





void
CSegment::UpdateIndicesGroup()
{
	if (m_tNeighbourHood.uiNorthId != -1 && m_tNeighbourHood.uiEastId != -1)
	{
		m_eType = TYPE_FOUR;
	}
	else if (m_tNeighbourHood.uiNorthId != -1)
	{
		m_eType = TYPE_THREE;
	}
	else if (m_tNeighbourHood.uiEastId != -1)
	{
		m_eType = TYPE_TWO;
	}
	else
	{
		m_eType = TYPE_ONE;
	}
}





/********************************
            Private
*********************************/





bool
CSegment::InitialiseHeightmap()
{
	FW_ADELETE(m_uspHeightmap);


	m_uspHeightmap = new ushort[m_uiNumVertices];
	memset(m_uspHeightmap, 0, sizeof(ushort) * m_uiNumVertices);


	return (m_uspHeightmap != 0);
}





bool
CSegment::InitialiseAABBox()
{
	m_pAABBox = new CAABB();


	return (m_pAABBox != 0);
}





void
CSegment::Deinitialise()
{
	FW_ADELETE(m_uspHeightmap);
	FW_DELETE(m_pAABBox);
}





void
CSegment::GenerateIndices(const TLayout& _ktrLayoutDesc, bool _bNeighbourAbove, bool _bNeighbourRight, std::vector<uint>& _arIndices)
{
	uint uiCurrentRow = 0;


	// Generate indices
    for (uint uiCurrentRow = 0; uiCurrentRow <= _ktrLayoutDesc.uiLength - 2 || (_bNeighbourAbove && uiCurrentRow <= _ktrLayoutDesc.uiLength - 1); ++ uiCurrentRow)
    {
		// Vertices offset for current row
		uint uiCurrentRowOffset = (uiCurrentRow * _ktrLayoutDesc.uiWidth);
		uint uiAboveRowOffset = 0;


		// Has neighbour in front. On last row of this segment
		if (_bNeighbourAbove != 0 &&
			uiCurrentRow == _ktrLayoutDesc.uiLength - 1)
		{
			// Stitch this segment with the bottom vertices
			// of front neighbours' vertices
			uiAboveRowOffset  = _ktrLayoutDesc.uiWidth *  _ktrLayoutDesc.uiLength * _ktrLayoutDesc.uiCountX;
		}
		else
		{
			uiAboveRowOffset  = uiCurrentRowOffset;
			uiAboveRowOffset += _ktrLayoutDesc.uiWidth;
		}


		// Even row - Left to right
        if (uiCurrentRow % 2 == 0)
		{
			GenerateEvenRowIndices(_ktrLayoutDesc, uiCurrentRow, uiCurrentRowOffset, uiAboveRowOffset, _bNeighbourAbove, _bNeighbourRight, _arIndices);
        }


		// Odd row - Right to left
        else
        {
			GenerateOddRowIndices(_ktrLayoutDesc, uiCurrentRow, uiCurrentRowOffset, uiAboveRowOffset, _bNeighbourAbove, _bNeighbourRight, _arIndices);
        }
    }
}





void
CSegment::GenerateEvenRowIndices(const TLayout& _ktrLayoutDesc, uint _uiCurrentRow, uint _uiCurrentRowOffset, uint _uiAboveRowOffset, bool _bNeighbourAbove, bool _bNeighbourRight, std::vector<uint>& _arIndices)
{
	// Right stitching
	for (uint uiX = 0; uiX < _ktrLayoutDesc.uiWidth; ++ uiX)
	{
		_arIndices.push_back( _uiCurrentRowOffset + uiX );
		_arIndices.push_back( _uiAboveRowOffset   + uiX );
	}


	
	// Has right neighbour - Stitch together 
	// with neighbours left side vertices
	if (_bNeighbourRight)
	{
		uint uiNeighbourVerticesOffset = _ktrLayoutDesc.uiWidth * _ktrLayoutDesc.uiLength;


		// Match neighbours row with
		// the current row we are on
		uint uiMatchRowOffset = uiNeighbourVerticesOffset + (_ktrLayoutDesc.uiWidth * _uiCurrentRow);
		uint uiMatchAboveRowOffset = uiMatchRowOffset + _ktrLayoutDesc.uiWidth;


		// Have above neighbour
		// Check we are on last row in right neighbour
		if (_bNeighbourAbove &&
			_uiCurrentRow == _ktrLayoutDesc.uiLength - 1)
		{
			uiMatchAboveRowOffset = _ktrLayoutDesc.uiWidth *  _ktrLayoutDesc.uiLength * (_ktrLayoutDesc.uiCountX + 1);
		}


		_arIndices.push_back( uiMatchRowOffset );
		_arIndices.push_back( uiMatchAboveRowOffset );

		
		// Insert degenerate vertex
		_arIndices.push_back( uiMatchAboveRowOffset );
	}
	else
	{

		// Check this is not last row
		if (_uiCurrentRow < _ktrLayoutDesc.uiLength - 1)
		{
			// Insert degenerate vertex
			_arIndices.push_back( _uiAboveRowOffset +  (_ktrLayoutDesc.uiWidth - 1) );
		}
	}
}





void
CSegment::GenerateOddRowIndices(const TLayout& _ktrLayoutDesc, uint _uiCurrentRow, uint _uiCurrentRowOffset, uint _uiAboveRowOffset, bool _bNeighbourAbove, bool _bNeighbourRight, std::vector<uint>& _arIndices)
{
	// Has right neighbour, stitch together 
	// with neighbours left vertices
	if (_bNeighbourRight)
	{
		uint uiNeighbourVerticesOffset = _ktrLayoutDesc.uiWidth * _ktrLayoutDesc.uiLength;


		// Find neightbour row to match
		// the current row we are on
		uint uiNeighbourRow = uiNeighbourVerticesOffset + (_ktrLayoutDesc.uiWidth * _uiCurrentRow);
		uint uiNeighbourAboveRow = uiNeighbourRow + _ktrLayoutDesc.uiWidth;


		// Check we are on last row in right neighbour
		if (_uiCurrentRow == _ktrLayoutDesc.uiLength - 1 &&
			_bNeighbourAbove)
		{
			uiNeighbourAboveRow = _ktrLayoutDesc.uiWidth *  _ktrLayoutDesc.uiLength * (_ktrLayoutDesc.uiCountX + 1);
		}


		_arIndices.push_back( uiNeighbourRow );
		_arIndices.push_back( uiNeighbourAboveRow );
	}


	for (uint uiX = _ktrLayoutDesc.uiWidth - 1; uiX != -1; -- uiX)
	{
		_arIndices.push_back( _uiCurrentRowOffset + uiX );
		_arIndices.push_back( _uiAboveRowOffset + uiX );
	}


	// Check this is not last row
	if (_uiCurrentRow < _ktrLayoutDesc.uiLength - 1)
	{
		// Insert degenerate vertex
		_arIndices.push_back( _uiAboveRowOffset );
	}
}