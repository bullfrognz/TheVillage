//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Segment.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Segment_H__
#define __Segment_H__


// Library Includes


// Local Includes
#include "Library\AABB.h"


// Types


// Prototypes
class IRenderer;
class ITexture;
class CTerrainVertex;
class CAABB;


class CSegment
{

	// Members Types
public:


	/* Neighbours of segment in layout */
	struct TNeighbourhood
	{
		uint uiNorthId;
		uint uiSouthId;
		uint uiEastId;
		uint uiWestId;
		uint uiNorthEastId;
		uint uiSouthEastId;
		uint uiSouthWestId;
		uint uiNorthWestId;
	};


	/* Describes the layout of the segments group */
	struct TLayout
	{
		uint uiWidth;		// Width of single segment in group
		uint uiLength;		// Height of single segment in group
		uint uiCountX;		// Number of segments horizontally in array
		uint uiCountZ;		// Number of segments vertically in array
		uint uiIndexX;		// This X position in segment layout 
		uint uiIndexZ;		// This Y position in segment layout
	};


	/* Specifies which index data to
	   use when drawing */
	enum EType
	{
		INVALID_TYPE = -1,

		TYPE_ONE,
		TYPE_TWO,
		TYPE_THREE,
		TYPE_FOUR,

		MAX_TYPE
	};


protected:


	/* Index info based on the segments location.
	   Used internally for sharing indices between segments */
	struct TIndicesInfo
	{
		uint uiOffset;
		uint uiCount;
	};


	// Member Functions
public:


	 CSegment();
	~CSegment();


	bool Initialise(const TLayout& _ktrLayoutDesc, const TNeighbourhood& _ktrNeighbourhood);


	void ApplyVertexPositions(CTerrainVertex* _pVertexData);
	void ApplyVertexNormals(CTerrainVertex* _pVertexData, const CSegment* _kpSegments);
	void ApplyVertexTextureCoords(CTerrainVertex* _pVertexData);


	CSegment& operator = (const CSegment& _krSegment);


	static void GenerateGlobalIndices(const TLayout& _ktrLayoutDesc, uint*& _prIndexData, uint& _uirNumIndices);


	// Inline Functions
	inline void SetHeight(uint _uiX, uint _uiZ, ushort _usHeight);
	inline void SetHeightScale(float _fScale);
	inline void SetPosition(float _fX, float _fZ);
	inline void SetVerticesOffset(uint _uiOffset);
	inline void SetActive(bool _bActive);


	inline float GetHeight(uint _uiX, uint _uiZ) const;
	inline float GetPositionX() const;
	inline float GetPositionZ() const;
	inline uint  GetWidth() const;
	inline uint  GetLength() const;
	inline uint  GetVerticesOffset() const;
	inline uint  GetIndicesOffset() const;
	inline uint  GetVerticesCount() const;
	inline uint  GetIndicesCount() const;
	inline uint  GetIndexX() const;
	inline uint  GetIndexZ() const;
	inline const CAABB& GetAABBox() const;
	inline const TNeighbourhood& GetNeighbourhood() const;


	inline bool IsActive() const;


protected:


	void UpdateAABBoxBounds();
	void UpdateIndicesGroup();


private:


	bool InitialiseHeightmap();
	bool InitialiseAABBox();


	void Deinitialise();


	static void GenerateIndices(const TLayout& _ktrLayoutDesc, bool _bNeighbourAbove, bool _bNeighbourRight, std::vector<uint>& _arIndices);

	static void GenerateEvenRowIndices(const TLayout& _ktrLayoutDesc, uint _uiCurrentRow, uint _uiCurrentRowOffset, uint _uiAboveRowOffset,
									   bool _bNeighbourAbove, bool _bNeighbourRight, std::vector<uint>& _arIndices);

	static void GenerateOddRowIndices(const TLayout& _ktrLayoutDesc, uint _uiCurrentRow, uint _uiCurrentRowOffset, uint _uiAboveRowOffset,
									  bool _bNeighbourAbove, bool _bNeighbourRight, std::vector<uint>& _arIndices);


	CSegment(const CSegment& _krSegment);


	// Member Variables
protected:


private:


	TNeighbourhood m_tNeighbourHood;
	TLayout m_tLayoutDesc;


	CAABB* m_pAABBox;
	ushort* m_uspHeightmap;


	EType m_eType;


	float m_fPositionX;
	float m_fPositionZ;
	float m_fHeightScale;


	uint m_uiVerticesOffset;
	uint m_uiNumVertices;


	bool m_bActive;
	bool m_bUpdateBounds;


	static uint s_uiReffCount;
	static TIndicesInfo s_tIndicesInfo[MAX_TYPE];


};


#include "Segment.inl"


#endif //__Segment_H__