//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Terrain.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Terrain_H__
#define __Terrain_H__


// Library Includes
#include <vector>
#include <process.h>


// Local Includes
#include "Defines\DataTypes.h"
#include "Library\Entity.h"
#include "Scene\Game\Segment.h"
#include "Framework\Effect.h"
#include "Framework\Application.h"
#include "Framework\Window.h"
#include "Framework\Renderer.h"


// Types


// Prototypes
class IRenderer;
class ITexture;
class IVertexBuffer;
class IIndexBuffer;
class ITexture;
class IEffect;
class CFile;
class CLight;
class CViewMatrix;
class CProjMatrix;
class CCamera;
class CRawImage;


class CTerrain : public CEntity
{

	// Member Types
public:


	enum EViewRange
	{
		INVALID_VIEWRANGE	= 0,

		VIEWRANGE_TINY		= 1,
		VIEWRANGE_SMALL		= 2,
		VIEWRANGE_MEDIUM	= 4,
		VIEWRANGE_LARGE		= 6,
		VIEWRANGE_EXTREME	= 8,
		VIEWRANGE_ULTRA		= 10,
		VIEWRANGE_GODLIKE	= 4,
	};


	enum ESetting
	{
		SEGMENT_WIDTH	= 128,
		SEGMENT_LENGTH	= 128,


		TEXTURES_MAX	= 5
	};


	struct TFiles
	{
		char* cpHeightmap;
		char* cpTextures[TEXTURES_MAX];
		char* cpAlphamap[TEXTURES_MAX];


		uint uiHeightmapWidth;
		uint uiHeightmapHeight;
	};


	struct TDirtyProgressData
	{
		CTerrain* pSelfInstance;
		IRenderer* pRenderer;
	};


	static const float s_kfHeightScale;


	// Member Functions
public:


	 CTerrain();
	~CTerrain();


	bool Initialise(IRenderer& _rRenderer, const TFiles& _ktrFiles);
	bool Process(IRenderer& _rRenderer, float _fDeltaTick);
	bool DrawAmbient(IRenderer& _rRenderer, CCamera& _rPlayerCamera, std::vector<CLight*>& _rActiveLights);
	bool DrawLit(IRenderer& _rRenderer, CCamera& _rPlayerCamera, std::vector<CLight*>& _rActiveLights);
	bool DrawBoundingBoxes(IRenderer& _rRenderer, CCamera& _rPlayerCamera);


	bool UpdatePosition(const CVector3& _kvrCameraPosition);


	bool ChangeViewRange(IRenderer& _rRenderer, EViewRange _eRange);


	bool GetMeshHeight(const CVector3& _kvrPosition, float& _frHeight);


	void IncrementViewRange()
	{
		if (m_eViewRange < 12 &&
			m_aDirtySegments.size() == 0)
		{
			ChangeViewRange(CApplication::GetInstance().GetWindow().GetRenderer(), static_cast<EViewRange>(m_eViewRange + 1));
		}
	}


	void DerementViewRange()
	{
		if (m_eViewRange > 2 &&
			m_aDirtySegments.size() == 0)
		{
			ChangeViewRange(CApplication::GetInstance().GetWindow().GetRenderer(), static_cast<EViewRange>(m_eViewRange - 1));
		}
	}


	// Inline Functions
	inline void SetFogEnabled(bool _bEnabled);
	inline bool IsBusy();
	

protected:


	bool Draw(IRenderer& _rRenderer, CCamera& _rPlayerCamera, std::vector<CLight*>& _rActiveLights);


	bool ProcessDirtySegments(IRenderer* _pRenderer);


	bool LoadSegmentHeightmap(uint _uiSegmentId);
	bool UploadSegmentVertices(IRenderer& _rRenderer, uint _uiSegmentId);
	void ApplyAlphamaps(CTerrainVertex* _pVertexData, uint _uiSegmentId);


	void GenerateSegmentNeighbours(uint _uiX, uint _uiZ, CSegment::TNeighbourhood& _rNeighbourhood);
	void GenerateSegmentFileSection(uint _uiSegmentId, int& _irLeft, int& _irRight, int& _irTop, int& _irBottom);


	void UpdateDrawOrder();
	void TranslateSegments(int _iX, int _iZ);


	bool ComputeVertexHeight(uint _uiSegmentId, float _fPointX, float _fPointZ, float& _frHeight);


	// Inline functions
	inline void AddDirtySegment(uint _uiSegmentId);
	inline int  GenerateSegmentId(uint _uiX, uint _uiZ);


private:


	bool InitialiseEffect(IRenderer& _rRenderer);
	bool InitialiseAABBEffect(IRenderer& _rRenderer);
	bool InitialiseFiles(const TFiles& _ktrFiles);
	bool IntiailiseTextures(IRenderer& _rRenderer, const TFiles& _ktrFiles);


	bool CreateSegments(uint _uiSegmentCountX, uint _uiSegmentCountZ);
	bool CreateVertexBuffer(IRenderer& _rRenderer);
	bool CreateIndexBuffer(IRenderer& _rRenderer);
	bool CompileAABBVertices(IRenderer& _rRenderer);


	void Deinitialise();


	static void StartProcessDirtySegments(void* _rArgs);


	CTerrain(const CTerrain& _krTerrain);
	CTerrain& operator = (const CTerrain& _krTerrain);


	// Member Variables
protected:


private:

	
	CSegment* m_pSegments;
	IEffect* m_pEffect;
	IEffect* m_pAABBEffect;
	IVertexBuffer* m_pAABBBuffer;
	IVertexBuffer* m_pVertexBuffer;
	IIndexBuffer* m_pIndexBuffer;
	ITexture* m_pTextures[TEXTURES_MAX];
	CRawImage* m_pAlphamapFiles[TEXTURES_MAX];
	CRawImage* m_pHeightmapFile;
	uintptr_t m_DirtyProcessThreadId;
	

	EViewRange m_eViewRange;


	uint m_uiSegmentCountX;
	uint m_uiSegmentCountZ;


	int m_iPositionX;
	int m_iPositionZ;
	

	bool m_bFogEnabled;
	bool m_bProcessingDirtySegments;
	bool m_bQuitting;


	std::vector<uint> m_aDirtySegments;
	std::vector<uint> m_aSegmentsDrawOrdered;


};


#include "Terrain.inl"


#endif //__Terrain_H__