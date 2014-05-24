//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   Terrain.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <map>


// Local Includes
#include "Defines\Macros.h"
#include "Utilities\StrUtilities.h"
#include "Math\Vector2.h"
#include "Math\Vector3.h"
#include "Math\WorldMatrix.h"
#include "Math\ViewMatrix.h"
#include "Math\ProjMatrix.h"
#include "Math\Colour.h"
#include "Framework\Renderer.h"
#include "Framework\VertexBuffer.h"
#include "Framework\IndexBuffer.h"
#include "Framework\Light.h"
#include "Framework\Effect.h"
#include "Framework\Texture.h"
#include "Framework\Camera.h"
#include "Framework\File.h"
#include "Library\RawImage.h"


#include "Scene\Game\TerrainVertex.h"


// This Include
#include "Terrain.h"


// Static Variables
const float CTerrain::s_kfHeightScale = 50.0f;


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CTerrain constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CTerrain::CTerrain()
: m_pSegments(0)
, m_pAABBBuffer(0)
, m_pAABBEffect(0)
, m_pVertexBuffer(0)
, m_pIndexBuffer(0)
, m_pHeightmapFile(0)
, m_pEffect(0)
, m_DirtyProcessThreadId(0)
, m_eViewRange(INVALID_VIEWRANGE)
, m_uiSegmentCountX(0)
, m_uiSegmentCountZ(0)
, m_iPositionX(0)
, m_iPositionZ(0)
, m_bFogEnabled(false)
, m_bProcessingDirtySegments(false)
, m_bQuitting(false)
{
	memset(m_pTextures, 0, sizeof(ITexture*) * TEXTURES_MAX);
	memset(m_pAlphamapFiles, 0, sizeof(CFile*) * TEXTURES_MAX);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CTerrain deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CTerrain::~CTerrain()
{
	Deinitialise();
}





bool
CTerrain::Initialise(IRenderer& _rRenderer, const TFiles& _ktrFiles)
{
	FW_VALIDATE(InitialiseEffect(_rRenderer))
	FW_VALIDATE(InitialiseAABBEffect(_rRenderer))
	FW_VALIDATE(InitialiseFiles(_ktrFiles))
	FW_VALIDATE(IntiailiseTextures(_rRenderer, _ktrFiles))
	

	ChangeViewRange(_rRenderer, VIEWRANGE_GODLIKE);


	return (true);
}





bool
CTerrain::Process(IRenderer& _rRenderer, float _fDeltaTick)
{
	if (!m_bProcessingDirtySegments &&
		!m_bQuitting)
	{
		if (m_aDirtySegments.size() > 0)
		{
			TDirtyProgressData* tpDirtyProcessData = new TDirtyProgressData;
			tpDirtyProcessData->pSelfInstance = this;
			tpDirtyProcessData->pRenderer = &_rRenderer;


			m_DirtyProcessThreadId = _beginthread(&CTerrain::StartProcessDirtySegments, 0, reinterpret_cast<void*>(tpDirtyProcessData));	


			m_bProcessingDirtySegments = true;
		}
	}


	//ProcessDirtySegments(&_rRenderer);


	return (true);
}





bool
CTerrain::DrawAmbient(IRenderer& _rRenderer, CCamera& _rPlayerCamera, std::vector<CLight*>& _rActiveLights)
{
	_rRenderer.SetActiveEffect(m_pEffect, "Technique1");


	return (Draw(_rRenderer, _rPlayerCamera, _rActiveLights));
}





bool
CTerrain::DrawLit(IRenderer& _rRenderer, CCamera& _rPlayerCamera, std::vector<CLight*>& _rActiveLights)
{
	_rRenderer.SetActiveEffect(m_pEffect, "Technique1");


	return (Draw(_rRenderer, _rPlayerCamera, _rActiveLights));
}





bool
CTerrain::DrawBoundingBoxes(IRenderer& _rRenderer, CCamera& _rPlayerCamera)
{
	if (m_pAABBBuffer != 0)
	{
		_rRenderer.SetActiveVertexBuffer(m_pAABBBuffer, 0);
		_rRenderer.SetActiveEffect(m_pAABBEffect, "DefaultTechnique");


		// Set transformations
		FW_VALIDATE(m_pAABBEffect->SetTransformations(CEntity::GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()))


		// Draw
		FW_VALIDATE(_rRenderer.Draw(m_pAABBBuffer->GetCapacity(), 0))
	}


	return (true);
}





bool
CTerrain::UpdatePosition(const CVector3& _kvrCameraPosition)
{
	static bool bonce= false;


	if (bonce)
		return (bonce);


	bonce = true;


	// Convert position to terrain position
	float fPositionDifferenceX = _kvrCameraPosition.GetX() - static_cast<float>(m_iPositionX);
	float fPositionDifferenceZ = _kvrCameraPosition.GetZ() - static_cast<float>(m_iPositionZ);
	int kiTranslationX = static_cast<int>(fPositionDifferenceX) / SEGMENT_WIDTH;
	int kiTranslationZ = static_cast<int>(fPositionDifferenceZ) / SEGMENT_LENGTH;


	if (fPositionDifferenceX < 0.0f)
	{
		kiTranslationX -= 1;
	}


	if (fPositionDifferenceZ < 0.0f)
	{
		kiTranslationZ -= 1;
	}


	//const int kiTranslationX = m_iPositionX - iTerrainPositionX;
	//const int kiTranslationZ = m_iPositionZ - iTerrainPositionZ;


	if (kiTranslationX != 0 ||
		kiTranslationZ != 0)
	{
		//TranslateSegments(kiTranslationX, kiTranslationZ);


		m_iPositionX = m_iPositionX + (kiTranslationX) * SEGMENT_WIDTH;
		m_iPositionZ = m_iPositionZ + (kiTranslationZ) * SEGMENT_LENGTH;
	}


	return (true);
}





bool
CTerrain::ChangeViewRange(IRenderer& _rRenderer, EViewRange _eRange)
{
	m_eViewRange = _eRange;


	// Update segments count based on view range
	const uint kuiSegmentCountX = ((m_eViewRange * 2) + 1);
	const uint kuiSegmentCountZ = ((m_eViewRange * 2) + 1);


	FW_VALIDATE(CreateSegments(kuiSegmentCountX, kuiSegmentCountZ))
	FW_VALIDATE(CreateVertexBuffer(_rRenderer))
	FW_VALIDATE(CreateIndexBuffer(_rRenderer))


	// Update fog start distance
	const uint kuiFogStartDistance = m_eViewRange * SEGMENT_WIDTH - (SEGMENT_WIDTH / 2);
	m_pEffect->SetVariable("g_fFogStartDistance",  kuiFogStartDistance);


	return (true);
}





bool
CTerrain::GetMeshHeight(const CVector3& _kvrPosition, float& _frHeight)
{
	bool bReturn = false;


	const int kiSegmentCountX = m_uiSegmentCountX;
	const int kiSegmentCountZ = m_uiSegmentCountZ;


	// Position relative to terrain
	const float kfRelativePositionX = _kvrPosition.GetX() - m_iPositionX;
	const float kfRelativePositionZ = _kvrPosition.GetZ() - m_iPositionZ;


	// Position relative to 0, 0 segment
	const float kfSegmentPositionX = kfRelativePositionX + ((kiSegmentCountX / 2) * SEGMENT_WIDTH);
	const float kfSegmentPositionZ = kfRelativePositionZ + ((kiSegmentCountZ / 2) * SEGMENT_LENGTH);


	// If within bounds
	if (kfSegmentPositionX > 0.0f &&
		kfSegmentPositionZ > 0.0f)
	{
		// Position to segment index
		const int kiSegmentIndexX = static_cast<int>(kfSegmentPositionX) / SEGMENT_WIDTH;
		const int kiSegmentIndexZ = static_cast<int>(kfSegmentPositionZ) / SEGMENT_LENGTH;


		// If within segment index bounds
		if (kiSegmentIndexX >= 0 &&
			kiSegmentIndexZ >= 0 &&
			kiSegmentIndexX < kiSegmentCountX &&
			kiSegmentIndexZ < kiSegmentCountZ)
		{
			const uint uiSegmentId = GenerateSegmentId(kiSegmentIndexX, kiSegmentIndexZ);


			if (m_pSegments[uiSegmentId].IsActive())
			{
				const float kfPointX = _kvrPosition.GetX() - m_pSegments[uiSegmentId].GetPositionX();
				const float kfPointZ = _kvrPosition.GetZ() - m_pSegments[uiSegmentId].GetPositionZ();


				bReturn = ComputeVertexHeight(uiSegmentId, kfPointX, kfPointZ, _frHeight);


				bReturn = true;
			}
			else
			{
				// Out of bounds
			}
		}
		else
		{
			// Out of bounds
		}
	}
	else
	{
		// Out of bounds
	}


	return (bReturn);
}





/********************************
            Protected
*********************************/






bool
CTerrain::Draw(IRenderer& _rRenderer, CCamera& _rPlayerCamera, std::vector<CLight*>& _rActiveLights)
{
	m_pEffect->SetTextures(m_pTextures, 4);


	// Set effect
	FW_VALIDATE(_rRenderer.SetActiveVertexBuffer(m_pVertexBuffer, 0))


	// Set transformations
	FW_VALIDATE(m_pEffect->SetTransformations(CEntity::GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()))


	// Set lights
	FW_VALIDATE(m_pEffect->SetLights(&(*_rActiveLights.begin()), _rActiveLights.size(), _rPlayerCamera.GetPosition()))
	

	// Draw active segments in camera frustum
	for (uint i = 0; i < m_aSegmentsDrawOrdered.size(); ++ i)
	{
		const uint kuiSegmentId = m_aSegmentsDrawOrdered[i];


		if (m_pSegments[kuiSegmentId].IsActive() &&
			_rPlayerCamera.IsInFrustum(m_pSegments[kuiSegmentId].GetAABBox()))
		{
			const uint kuiVerticesOffset = m_pSegments[kuiSegmentId].GetVerticesOffset();
			const uint kuiIndicesOffset = m_pSegments[kuiSegmentId].GetIndicesOffset();
			const uint kuiIndicesCount = m_pSegments[kuiSegmentId].GetIndicesCount();


			FW_VALIDATE(_rRenderer.DrawIndexed(m_pIndexBuffer, kuiIndicesCount, kuiIndicesOffset, kuiVerticesOffset))
		}
		else
		{
			// Don't draw
		}
	}


	return (true);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
*	
*
* 	@param	_rRenderer		Renderer that contains the vertex buffer
*
*	@return	
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CTerrain::ProcessDirtySegments(IRenderer* _pRenderer)
{
	m_bProcessingDirtySegments = true;


	if (m_aDirtySegments.size() > 0)
	{
		std::vector<uint>::iterator StartSegmentId = m_aDirtySegments.begin();
		std::vector<uint>::iterator EndSegmentId = m_aDirtySegments.end();
		std::vector<uint>::iterator CurrentSegmentId;


		const int kiHalfSegmentCountX = m_uiSegmentCountX / 2;
		const int kiHalfSegmentCountZ = m_uiSegmentCountZ / 2;


		const uint kuiHalfHeightmapWidth  = m_pHeightmapFile->GetWidth() / 2;
		const uint kuiHalfHeightmapHeight = m_pHeightmapFile->GetHeight() / 2;


		// Position
		for (CurrentSegmentId = StartSegmentId; !m_bQuitting && CurrentSegmentId != EndSegmentId; ++ CurrentSegmentId)
		{
			const uint kuiSegmentId = (*CurrentSegmentId);


			const int kiSegmentIndexX = m_pSegments[kuiSegmentId].GetIndexX();
			const int kiSegmentIndexZ = m_pSegments[kuiSegmentId].GetIndexZ();


			const int kiSegmentPositionX = (m_iPositionX /** SEGMENT_LENGTH*/) + ((kiSegmentIndexX - kiHalfSegmentCountX) * SEGMENT_WIDTH);
			const int kiSegmentPositionZ = (m_iPositionZ /** SEGMENT_LENGTH*/) + ((kiSegmentIndexZ - kiHalfSegmentCountZ) * SEGMENT_LENGTH);


			m_pSegments[kuiSegmentId].SetPosition(static_cast<float>(kiSegmentPositionX),
												  static_cast<float>(kiSegmentPositionZ));
		}


		// Heightmap
		for (CurrentSegmentId = StartSegmentId; !m_bQuitting && CurrentSegmentId != EndSegmentId; ++ CurrentSegmentId)
		{
			LoadSegmentHeightmap((*CurrentSegmentId));
		}


		// Upload vertices
		for (CurrentSegmentId = StartSegmentId; !m_bQuitting && CurrentSegmentId != EndSegmentId; ++ CurrentSegmentId)
		{
			UploadSegmentVertices(*_pRenderer, (*CurrentSegmentId));
			m_pSegments[(*CurrentSegmentId)].SetActive(true);
		}


		m_aDirtySegments.resize(0);
	}


	if (!m_bQuitting)
	{
		FW_VALIDATE(CompileAABBVertices(*_pRenderer));
	}


	m_bProcessingDirtySegments = false;
	m_DirtyProcessThreadId = 0;


	return (true);
}





bool
CTerrain::LoadSegmentHeightmap(uint _uiSegmentId)
{
	const int kiHeightmapWidth  = m_pHeightmapFile->GetWidth();
	const int kiHeightmapHegith = m_pHeightmapFile->GetHeight();
	const int kiHalfHeightmapWidth = kiHeightmapWidth / 2;
	const int kiHalfHeightmapHeight = kiHeightmapHegith / 2;
	bool bWithinBounds = true;


	const int kiStartTexelRow    = static_cast<int>(m_pSegments[_uiSegmentId].GetPositionZ()) + kiHalfHeightmapHeight;
	const int kiStartTexelColumn = static_cast<int>(m_pSegments[_uiSegmentId].GetPositionX()) + kiHalfHeightmapWidth;


	if (kiStartTexelRow < 0 &&
		kiStartTexelColumn < 0 &&
		kiStartTexelRow > kiHeightmapHegith &&
		kiStartTexelColumn > kiHeightmapWidth)
	{
		bWithinBounds = false;
	}


	ushort* uspRowHeightData = new ushort[SEGMENT_WIDTH];
	memset(uspRowHeightData, 0, sizeof(ushort) * SEGMENT_WIDTH);


	for (uint uiRow = 0; uiRow < SEGMENT_LENGTH; ++ uiRow)
	{
		if (bWithinBounds)
		{
			m_pHeightmapFile->ReadLine(kiStartTexelRow + uiRow, kiStartTexelColumn, SEGMENT_WIDTH, uspRowHeightData);
		}
		else
		{
			// Keep 0 height
		}


		// Apply height data to row
		for (uint uiColumn = 0; uiColumn < SEGMENT_WIDTH; ++ uiColumn)
		{
			m_pSegments[_uiSegmentId].SetHeight(uiColumn, uiRow, uspRowHeightData[uiColumn]);
		}
	}


	FW_ADELETE(uspRowHeightData);


	return (true);
}





bool
CTerrain::UploadSegmentVertices(IRenderer& _rRenderer, uint _uiSegmentId)
{
	CTerrainVertex* pVertexData = new CTerrainVertex[SEGMENT_WIDTH * SEGMENT_LENGTH];


	// Apply data to segment vertices
	m_pSegments[_uiSegmentId].ApplyVertexPositions(pVertexData);
	m_pSegments[_uiSegmentId].ApplyVertexNormals(pVertexData, m_pSegments);
	m_pSegments[_uiSegmentId].ApplyVertexTextureCoords(pVertexData);
	ApplyAlphamaps(pVertexData, _uiSegmentId);


	// Update segment section in vertex buffer
	uint uiNumVertices = m_pSegments[_uiSegmentId].GetVerticesCount();
	uint uiVerticesOffset = m_pSegments[_uiSegmentId].GetVerticesOffset();


	m_pVertexBuffer->UpdateRegion(_rRenderer, pVertexData, uiNumVertices, uiVerticesOffset);


	FW_ADELETE(pVertexData);


	return (true);
}





void
CTerrain::ApplyAlphamaps(CTerrainVertex* _pVertexData, uint _uiSegmentId)
{
	// Compute heightmap section for segment 
	const int kiHeightmapWidth  = m_pHeightmapFile->GetWidth();
	const int kiHeightmapHegith = m_pHeightmapFile->GetHeight();
	const int kiHalfHeightmapWidth = kiHeightmapWidth / 2;
	const int kiHalfHeightmapHeight = kiHeightmapHegith / 2;
	bool bWithinBounds = true;


	const int kiStartTexelRow    = static_cast<int>(m_pSegments[_uiSegmentId].GetPositionZ()) + kiHalfHeightmapHeight;
	const int kiStartTexelColumn = static_cast<int>(m_pSegments[_uiSegmentId].GetPositionX()) + kiHalfHeightmapWidth;


	if (kiStartTexelRow < 0 &&
		kiStartTexelColumn < 0 &&
		kiStartTexelRow > kiHeightmapHegith &&
		kiStartTexelColumn > kiHeightmapWidth)
	{
		bWithinBounds = false;
	}


	uchar* ucpRowAlpha = new uchar[SEGMENT_WIDTH];
	memset(ucpRowAlpha, 0, sizeof(uchar) * SEGMENT_WIDTH);



	for (uint i = 0; i < TEXTURES_MAX; ++ i)
	{
		if (m_pAlphamapFiles[i] != 0)
		{
			for (uint uiZ = 0; uiZ < SEGMENT_LENGTH; ++ uiZ)
			{
				m_pAlphamapFiles[i]->ReadLine(kiStartTexelRow + uiZ, kiStartTexelColumn, SEGMENT_WIDTH, ucpRowAlpha);


				for (uint uiX = 0; uiX < SEGMENT_WIDTH; ++ uiX)
				{
					_pVertexData[uiZ * SEGMENT_WIDTH + uiX].TextureAlpha(i) = ucpRowAlpha[uiX] / 255.0f;
				}
			}
		}
		else
		{
			// Skip
		}
	}


	FW_ADELETE(ucpRowAlpha);
}





void
CTerrain::GenerateSegmentNeighbours(uint _uiX, uint _uiZ, CSegment::TNeighbourhood& _rNeighbourhood)
{
	_rNeighbourhood.uiNorthId = -1;
	_rNeighbourhood.uiSouthId = -1;
	_rNeighbourhood.uiEastId = -1;
	_rNeighbourhood.uiWestId = -1;
	_rNeighbourhood.uiNorthEastId = -1;
	_rNeighbourhood.uiNorthWestId = -1;
	_rNeighbourhood.uiSouthEastId = -1;
	_rNeighbourhood.uiSouthWestId = -1;


	// North
	if (_uiZ < m_uiSegmentCountZ - 1)
	{
		_rNeighbourhood.uiNorthId = GenerateSegmentId(_uiX, _uiZ + 1);
	}


	// South
	if (_uiZ > 0)
	{
		_rNeighbourhood.uiSouthId = GenerateSegmentId(_uiX, _uiZ - 1);
	}


	// East
	if (_uiX < m_uiSegmentCountX - 1)
	{
		_rNeighbourhood.uiEastId = GenerateSegmentId(_uiX + 1, _uiZ);


		// North East
		if (_rNeighbourhood.uiNorthId != -1)
		{
			_rNeighbourhood.uiNorthEastId = GenerateSegmentId(_uiX + 1, _uiZ + 1);
		}


		// South East
		if (_rNeighbourhood.uiSouthId != -1)
		{
			_rNeighbourhood.uiSouthEastId = GenerateSegmentId(_uiX + 1, _uiZ - 1);
		}
	}


	// West
	if (_uiX > 0)
	{
		_rNeighbourhood.uiWestId = GenerateSegmentId(_uiX - 1, _uiZ);


		// North West
		if (_rNeighbourhood.uiNorthId != -1)
		{
			_rNeighbourhood.uiNorthWestId = GenerateSegmentId(_uiX - 1, _uiZ + 1);
		}


		// South West
		if (_rNeighbourhood.uiSouthId != -1)
		{
			_rNeighbourhood.uiSouthWestId = GenerateSegmentId(_uiX - 1, _uiZ - 1);
		}
	}
}





/*---------------------------------------------------------------------------------------------------------------------------
*
*	Updates the draw list for the segments, ordered by the closest to furtherest based on the segment X, Z index.
*	Segments that are out of view range + 1 will be culled.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CTerrain::UpdateDrawOrder()
{
	m_aSegmentsDrawOrdered.clear();


	// Find segments index distances
	std::multimap<float, uint> mOrderedSegments;


	for (uint uiZ = 0; uiZ < m_uiSegmentCountZ; ++ uiZ)
	{
		for (uint uiX = 0; uiX < m_uiSegmentCountX; ++ uiX)
		{
			const uint kuiSegmentId = GenerateSegmentId(uiX, uiZ);


			CVector2 vSegmentIndex;
			vSegmentIndex.SetX(static_cast<float>(m_pSegments[kuiSegmentId].GetIndexX()) - m_eViewRange);
			vSegmentIndex.SetY(static_cast<float>(m_pSegments[kuiSegmentId].GetIndexZ()) - m_eViewRange);


			const float kfIndexDistance = vSegmentIndex.Magnitude();


			mOrderedSegments.insert( std::pair<float, uint>(kfIndexDistance, kuiSegmentId) );
		}
	}

	
	// Create list and cull out of range segments
	std::multimap<float, uint>::const_iterator kCurrent = mOrderedSegments.begin();
	std::multimap<float, uint>::const_iterator kEnd = mOrderedSegments.end();
	m_aSegmentsDrawOrdered.reserve(mOrderedSegments.size());


	for (kCurrent; kCurrent != kEnd; ++ kCurrent)
	{
		const float kfSegmentIndexDistance = (*kCurrent).first;
		const uint kuiSegmentId = (*kCurrent).second;


		if (kfSegmentIndexDistance <= m_eViewRange + 1)
		{
			m_aSegmentsDrawOrdered.push_back(kuiSegmentId);
		}
		else
		{
			// Don't add to list
		}


		// Mark segment as dirty
		AddDirtySegment(kuiSegmentId);
	}
}





void
CTerrain::TranslateSegments(int _iTranslateX, int _iTranslateZ)
{
	/*
	CSegment Tmp;
	int iXStart  = (_iTranslateX >= 0) ? 0   : _iTranslateX - 1;
	int iXEnd    = (_iTranslateX >= 0) ? _iTranslateX : -1;


	// Translate horizontal
	if (_iTranslateX != 0)
	{
		for (uint uiZ = 0; uiZ < m_uiSegmentCountZ; ++ uiZ)
		{
			for (int iX = iXStart; iX != iXEnd; iX += _iTranslateX)
			{
				if (iX + iXChange == iXEnd)
				{
					break;
				}


				//Tmp = m_pSegments[uiZ * m_uiSegmentCountX + (iX + iXChange)];
				//m_pSegments[uiZ * m_uiSegmentCountX + (iX + iXChange)] = m_pSegments[uiZ * m_uiSegmentCountX + iX];




			}
		}
	}
	*/
}





bool
CTerrain::ComputeVertexHeight(uint _uiSegmentId, float _fPointX, float _fPointZ, float& _frHeight)
{
	const CSegment& krSegment = m_pSegments[_uiSegmentId];
	const CSegment::TNeighbourhood& ktrNeighbourhood = krSegment.GetNeighbourhood();
	bool bReturn = true;


	float fTopLeftHeight = 0.0f;
	float fTopRightHeight = 0.0f;
	float fBottomRightHeight = 0.0f;
	bool bTopLeftFound = true;
	bool bTopRightFound = true;
	bool bBottomRightFound = true;


	// Top points in north neighbour
	if (_fPointZ >= SEGMENT_LENGTH - 1)
	{
		if (ktrNeighbourhood.uiNorthId != -1)
		{
			fTopLeftHeight  = m_pSegments[ktrNeighbourhood.uiNorthId].GetHeight(static_cast<uint>(_fPointX), 0);


			// Point is in north east segment
			if (_fPointX >= SEGMENT_WIDTH - 1)
			{
				fTopRightHeight = m_pSegments[ktrNeighbourhood.uiNorthEastId].GetHeight(0, 0);
			}
			else
			{
				fTopRightHeight = m_pSegments[ktrNeighbourhood.uiNorthId].GetHeight(static_cast<uint>(_fPointX + 1.0f), 0);
			}
		}
		else
		{
			bTopLeftFound = false;
			bTopRightFound = false;
		}
	}
	else
	{
		fTopLeftHeight  = krSegment.GetHeight(static_cast<uint>(_fPointX), static_cast<uint>(_fPointZ + 1.0f));


		// Right point is in east neighbour
		if (_fPointX >= SEGMENT_WIDTH - 1)
		{
			if (ktrNeighbourhood.uiEastId != -1)
			{
				fTopRightHeight = m_pSegments[ktrNeighbourhood.uiEastId].GetHeight(0, static_cast<uint>(_fPointZ + 1.0f));
			}
			else
			{
				bTopRightFound = false;
			}
		}
		else
		{
			fTopRightHeight = krSegment.GetHeight(static_cast<uint>(_fPointX + 1.0f), static_cast<uint>(_fPointZ + 1.0f));
		}
	}



	// Right neighbour
	if (_fPointX >= SEGMENT_WIDTH - 1)
	{
		if (ktrNeighbourhood.uiEastId != -1)
		{
			fBottomRightHeight = m_pSegments[ktrNeighbourhood.uiEastId].GetHeight(0, static_cast<uint>(_fPointZ));
		}
		else
		{
			bBottomRightFound = false;
		}
	}
	else
	{
		fBottomRightHeight = krSegment.GetHeight(static_cast<uint>(_fPointX + 1.0f), static_cast<uint>(_fPointZ));
	}



	if (bTopLeftFound &&
		bTopRightFound &&
		bBottomRightFound)
	{
		// Top left
		CVector3 vVertex1(1,
						  fTopLeftHeight,
						  2);


		// Top right
		CVector3 vVertex2(2,
						  fTopRightHeight,
						  2);


		// Bottom left
		CVector3 vVertex3(1,
						  krSegment.GetHeight(static_cast<uint>(_fPointX), static_cast<uint>(_fPointZ)),
						  1);


		// Bottom right 
		CVector3 vVertex4(2,
						  fBottomRightHeight,
						  1);


		// Compute point height on quad
		const float kfS = 1.0f - (vVertex1.GetX() / vVertex2.GetX() - vVertex1.GetX());
		const float kfT = 1.0f - (vVertex1.GetZ() / vVertex3.GetZ() - vVertex1.GetZ());


		const float kfY1 = vVertex1.GetY() + kfS * (vVertex2.GetY() - vVertex1.GetY());
		const float kfY2 = vVertex3.GetY() + kfS * (vVertex4.GetY() - vVertex3.GetY());


		_frHeight = kfY1 + kfT * (kfY2 - kfY1);
	}
	else
	{
		// Point is not on segemnt
		bReturn = false;
	}

	return (bReturn);
}





/********************************
            Private
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
*	Creates terrain effect description and loads effect file for renderering the terrain.
*
* 	@param	_rRenderer		Renderer to register effect with.
*
*	@return	Succeeded/Failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CTerrain::InitialiseEffect(IRenderer& _rRenderer)
{
	IEffect::TDesc tEffectDesc;
	tEffectDesc.kcpEffectFile = "Terrain.fx";


	// Helpers
	tEffectDesc.bTransformationHelper = true;
	tEffectDesc.bLightHelper = true;
	tEffectDesc.bTextureHelper = true;
	tEffectDesc.bFogHelper = true;


	// Input layout
	IEffect::TInput tPosition;
	tPosition.kcpName = "POSITION";
	tPosition.eVariableType = IEffect::VARIABLETYPE_FLOAT3;


	IEffect::TInput tNormal;
	tNormal.kcpName = "NORMAL";
	tNormal.eVariableType = IEffect::VARIABLETYPE_FLOAT3;


	IEffect::TInput tTexCoords1;
	tTexCoords1.kcpName = "TEXCOORD";
	tTexCoords1.eVariableType = IEffect::VARIABLETYPE_FLOAT2;


	IEffect::TInput tAlphamap1;
	tAlphamap1.kcpName = "TEXALPHA";
	tAlphamap1.eVariableType = IEffect::VARIABLETYPE_FLOAT1;
	tAlphamap1.uiSemanticIndex = 0;


	IEffect::TInput tAlphamap2;
	tAlphamap2.kcpName = "TEXALPHA";
	tAlphamap2.eVariableType = IEffect::VARIABLETYPE_FLOAT1;
	tAlphamap2.uiSemanticIndex = 1;


	IEffect::TInput tAlphamap3;
	tAlphamap3.kcpName = "TEXALPHA";
	tAlphamap3.eVariableType = IEffect::VARIABLETYPE_FLOAT1;
	tAlphamap3.uiSemanticIndex = 2;


	IEffect::TInput tAlphamap4;
	tAlphamap4.kcpName = "TEXALPHA";
	tAlphamap4.eVariableType = IEffect::VARIABLETYPE_FLOAT1;
	tAlphamap4.uiSemanticIndex = 3;



	// Techniques
	IEffect::TTechnqiue tTechnique1;
	tTechnique1.kcpName = "Technique1";
	tTechnique1.aInputLayout.push_back(tPosition);
	tTechnique1.aInputLayout.push_back(tNormal);
	tTechnique1.aInputLayout.push_back(tTexCoords1);
	tTechnique1.aInputLayout.push_back(tAlphamap1);
	tTechnique1.aInputLayout.push_back(tAlphamap2);
	tTechnique1.aInputLayout.push_back(tAlphamap3);
	tTechnique1.aInputLayout.push_back(tAlphamap4);

	tEffectDesc.aTechniques.push_back(tTechnique1);


	// Varaibles
	tEffectDesc.aVariableNames.push_back("g_bFogEnabled");


	FW_DELETE(m_pEffect);
	FW_VALIDATE(_rRenderer.InstanceEffect(tEffectDesc, m_pEffect));


	// Set default fog
	SetFogEnabled(m_bFogEnabled);


	return (true);
}





bool
CTerrain::InitialiseAABBEffect(IRenderer& _rRenderer)
{
	IEffect::TDesc tEffectDesc;
	CAABB::GenerateEffectDesc(tEffectDesc);


	FW_VALIDATE(_rRenderer.InstanceEffect(tEffectDesc, m_pAABBEffect));


	return (true);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
*	Opens heightmap and alphamap files used for setting up the terrain.
*
* 	@param	_ktrFiles	Files information
*
*	@return	Succeeded/Failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CTerrain::InitialiseFiles(const TFiles& _ktrFiles)
{
	// Open heightmap file
	m_pHeightmapFile = new CRawImage();
	FW_VALIDATE(m_pHeightmapFile->Initialise(_ktrFiles.cpHeightmap, _ktrFiles.uiHeightmapWidth, _ktrFiles.uiHeightmapHeight, sizeof(ushort)));


	// Open alphamap files
	for (uint i = 0; i < TEXTURES_MAX; ++ i)
	{
		if (_ktrFiles.cpAlphamap[i] != 0)
		{
			m_pAlphamapFiles[i] = new CRawImage();
			FW_VALIDATE(m_pAlphamapFiles[i]->Initialise(_ktrFiles.cpAlphamap[i], _ktrFiles.uiHeightmapWidth, _ktrFiles.uiHeightmapHeight, sizeof(char)));
		}
		else
		{
			// Do nothing
		}
	}


	return (true);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
*	Loads textures to renderer for texture splatting. Sends texture resources to effect file.
*
* 	@param	_rRenderer		Renderer to register textures with
*   @param	_ktrFiles		Texture files for terrain
*
*	@return	Succeeded/Failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CTerrain::IntiailiseTextures(IRenderer& _rRenderer, const TFiles& _ktrFiles)
{
	ITexture::TDesc tTextureDesc;
	memset(&tTextureDesc, 0, sizeof(ITexture::TDesc));


	tTextureDesc.eUsage = ITexture::USAGE_STATIC;
	tTextureDesc.eBindFlag = ITexture::BINDFLAG_SHADERRESOURCE;
	tTextureDesc.eFormat = ITexture::FORMAT_R8G8B8A8;
	tTextureDesc.eCPUAccess = ITexture::CPUACCESS_NONE;
	tTextureDesc.uiNumMipMaps = 8;


	uint uiNumTextures = 0;


	for (uint i = 0; i < TEXTURES_MAX; ++ i)
	{
		if (_ktrFiles.cpTextures[i] != 0)
		{
			FW_DELETE(m_pTextures[i]);


			tTextureDesc.kcpFile = _ktrFiles.cpTextures[i];


			FW_VALIDATE(_rRenderer.InstanceTexture(tTextureDesc, m_pTextures[i]));


			uiNumTextures = i + 1;
		}
	}


	// Upload texture resources to effect
	m_pEffect->SetTextures(m_pTextures, uiNumTextures);


	return (true);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
*	Creates and initialises segments for the terrain.
*
* 	@param	_uiSegmentCountX	Number of segments horizontally
* 	@param	_uiSegmentCountZ	Number of segments vertically
*
*	@return	Succeeded/Failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CTerrain::CreateSegments(uint _uiSegmentCountX, uint _uiSegmentCountZ)
{
	m_uiSegmentCountX = _uiSegmentCountX;
	m_uiSegmentCountZ = _uiSegmentCountZ;
	bool bReturn = true;


	// Create new segmnets
	FW_ADELETE(m_pSegments);

	m_pSegments = new CSegment[m_uiSegmentCountX * m_uiSegmentCountZ];


	if (m_pSegments == 0)
	{
		// Out of memory
		assert(false);
		bReturn = false;
	}
	else
	{
		// Discribe the layout of the segments
		CSegment::TLayout tSegmentLayout;
		tSegmentLayout.uiWidth = SEGMENT_WIDTH;
		tSegmentLayout.uiLength = SEGMENT_LENGTH;
		tSegmentLayout.uiCountX = m_uiSegmentCountX;
		tSegmentLayout.uiCountZ = m_uiSegmentCountZ;


		for (uint uiZ = 0; uiZ < m_uiSegmentCountZ; ++ uiZ)
		{
			tSegmentLayout.uiIndexZ = uiZ;


			for (uint uiX = 0; uiX < m_uiSegmentCountX; ++ uiX)
			{
				tSegmentLayout.uiIndexX = uiX;


				const uint kuiSegmentId = GenerateSegmentId(uiX, uiZ);


				// Neighbours
				CSegment::TNeighbourhood tNeighbourhood;
				GenerateSegmentNeighbours(uiX, uiZ, tNeighbourhood);


				FW_VALIDATE(m_pSegments[kuiSegmentId].Initialise(tSegmentLayout, tNeighbourhood))
				m_pSegments[kuiSegmentId].SetHeightScale(s_kfHeightScale);
			}
		}


		UpdateDrawOrder();
	}


	return (bReturn);
}





bool
CTerrain::CreateVertexBuffer(IRenderer& _rRenderer)
{
	FW_DELETE(m_pVertexBuffer);


	const uint kuiTotalSegmenetCount = SEGMENT_WIDTH * SEGMENT_LENGTH;
	const uint kuiNumVerticesPerSegment = m_uiSegmentCountX * m_uiSegmentCountZ;
	const uint kuiTotalVerticesCount = kuiTotalSegmenetCount * kuiNumVerticesPerSegment;


	IVertexBuffer::TDesc tVBufferDesc;
	memset(&tVBufferDesc, 0, sizeof(IVertexBuffer::TDesc));


	tVBufferDesc.ePrimitiveType = IVertexBuffer::PRIMITIVETYPE_TRIANGLESTRIP;
	tVBufferDesc.eUsage = IVertexBuffer::USAGE_STATIC;
	tVBufferDesc.uiNumVertices = kuiTotalVerticesCount;
	tVBufferDesc.uiStride = sizeof(CTerrainVertex);
	tVBufferDesc.pInitialData = 0;


	FW_VALIDATE(_rRenderer.InstanceVertexBuffer(tVBufferDesc, m_pVertexBuffer));


	return (true);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
*	Creates index buffer that is filled with generated indices used by the segments.
*
* 	@param	_rRenderer		Renderer to register the index buffer with
*
*	@return	Succeeded/Failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CTerrain::CreateIndexBuffer(IRenderer& _rRenderer)
{
	uint uiNumGeneratedIndices = 0;
	uint uiIndicesOffset = 0;
	uint* uipIndexData = 0;


	CSegment::TLayout tSegmentLayout;
	tSegmentLayout.uiWidth = SEGMENT_WIDTH;
	tSegmentLayout.uiLength = SEGMENT_LENGTH;
	tSegmentLayout.uiCountX = m_uiSegmentCountX;
	tSegmentLayout.uiCountZ = m_uiSegmentCountZ;
	tSegmentLayout.uiIndexX = 0;
	tSegmentLayout.uiIndexZ = 0;


	CSegment::GenerateGlobalIndices(tSegmentLayout, uipIndexData, uiNumGeneratedIndices);


	IIndexBuffer::TDesc tIBufferDesc;
	tIBufferDesc.eIndexSize = IIndexBuffer::INDEXSIZE_32;
	tIBufferDesc.eUsage = IIndexBuffer::USAGE_STATIC;
	tIBufferDesc.uiIndicesCount = uiNumGeneratedIndices;
	tIBufferDesc.pInitialData = uipIndexData;


	FW_DELETE(m_pIndexBuffer);
	FW_VALIDATE(_rRenderer.InstanceIndexBuffer(tIBufferDesc, m_pIndexBuffer));


	FW_ADELETE(uipIndexData);


	return (true);
}





bool
CTerrain::CompileAABBVertices(IRenderer& _rRenderer)
{
	FW_DELETE(m_pAABBBuffer);


	const uint kuiTotalSegmentsCount = m_uiSegmentCountX * m_uiSegmentCountZ;
	std::vector<CAABB::TVertex> aVertices;


	for (uint i = 0; i < kuiTotalSegmentsCount; ++i)
	{
		m_pSegments[i].GetAABBox().GenerateVertices(aVertices);
	}


	IVertexBuffer::TDesc tVBufferDesc;
	memset(&tVBufferDesc, 0, sizeof(IVertexBuffer::TDesc));


	tVBufferDesc.ePrimitiveType = CAABB::TVertex::s_kePrimitiveType;
	tVBufferDesc.eUsage = IVertexBuffer::USAGE_STATIC;
	tVBufferDesc.uiNumVertices = aVertices.size();
	tVBufferDesc.uiStride = sizeof(CAABB::TVertex);
	tVBufferDesc.pInitialData = aVertices.data();


	FW_VALIDATE(_rRenderer.InstanceVertexBuffer(tVBufferDesc, m_pAABBBuffer));


	return (true);
}





void
CTerrain::Deinitialise()
{
	m_bQuitting = true;


	int lol = 2;


	// wait for thread to stop/finish
	while (m_DirtyProcessThreadId != 0 &&
		   m_bProcessingDirtySegments)
	{
		++ lol;
	}


	FW_DELETE(m_pVertexBuffer)
	FW_DELETE(m_pIndexBuffer)
	FW_DELETE(m_pHeightmapFile)
	FW_DELETE(m_pEffect)
	FW_DELETE(m_pHeightmapFile)
	FW_ADELETE(m_pSegments)
	FW_DELETE(m_pAABBEffect)
	FW_DELETE(m_pAABBBuffer)


	for (uint i = 0; i < TEXTURES_MAX; ++ i)
	{
		FW_DELETE(m_pTextures[i])
		FW_DELETE(m_pAlphamapFiles[i])
	}
}





void
CTerrain::StartProcessDirtySegments(void* _rArgs)
{
	TDirtyProgressData tDirtyProcessData = *reinterpret_cast<TDirtyProgressData*>(_rArgs);
	FW_DELETE(_rArgs);


	tDirtyProcessData.pSelfInstance->ProcessDirtySegments(tDirtyProcessData.pRenderer);
}