//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Model.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Model_H__
#define __Model_H__


// Library Includes
#include <vector>






// Local Includes
#include "Framework\Effect.h"
#include "Math\Material.h"


// Types


// Prototypes
class IIndexBuffer;
class IVertexBuffer;
class ITexture;

struct aiMesh;
struct aiScene;
struct aiMaterial;


struct ID3DX10Mesh;

namespace Assimp
{
	struct aiFace;
}


class CModel
{
	
	// Member Types
public:


	enum EInputType
	{
		INVALID_INPUTTYPE,

		INPUTTYPE_POSITION,
		INPUTTYPE_NORMAL,
		INPUTTYPE_TEXTCOORDS1,
		INPUTTYPE_TEXTCOORDS2,

		MAX_INPUTTYPE
	};


	struct TMaterial
	{
		ITexture** ppTextures;
		uint uiNumTextures;
	};


	struct TSubset
	{
		char* pName;
		uint uiNumIndices;
		uint uiIndexOffset;
		uint uiMaterialId;
	};


	// Member Functions
public:


	 CModel();
	~CModel();


	bool Initialise(IRenderer& _rRenderer, const char* _kcpFile, const std::vector<EInputType>& _karInputLayout);


	bool Draw(IRenderer& _rRenderer, IEffect& _rEffect);


	// Inline Functions
	inline uint GetNumSubsets() const;
	inline const TSubset& GetSubset(uint _uiId) const;
	inline uint GetNumMaterials() const;
	inline TMaterial& GetMaterial(uint _uiId);


protected:


	bool DrawSubset(IRenderer& _rRenderer, uint _uiSubsetId, IEffect& _rEffect);


	uint ComputeStride();


	bool ExtractVertexData(const aiMesh* _tpMesh, std::vector<float>& _arVertexData);
	bool ExtractIndexData(const aiMesh* _tpMesh, uint _uiVertexCount, std::vector<uint>& _arIndices);


	bool AddMaterial(IRenderer& _rRenderer, const aiMaterial* _ktpSceneMaterial);
	bool AddSubset(const aiMesh* _ktpMesh, std::vector<float>& _arVertexData, std::vector<uint>& _arIndexData);


private:


	bool InitialiseMaterials(IRenderer& _rRenderer, const aiScene* _ktpScene);
	bool InitialiseSubsets(IRenderer& _rRenderer, const aiScene* _ktpScene, std::vector<float>& _arVertexData, std::vector<uint>& _arIndexData);
	bool InitialiseVertexBuffer(IRenderer& _rRenderer, std::vector<float>& _arVertexData);
	bool InitialiseIndexBuffer(IRenderer& _rRenderer, std::vector<uint>& _arIndexData);


	void Deinitialise();


	CModel(const CModel& _krModel);
	CModel& operator = (const CModel& _krModel);


	// Member Variables
protected:


private:


	ID3DX10Mesh* pMesh;


	char* m_cpFile;
	IVertexBuffer* m_pVertexBuffer;
	IIndexBuffer* m_pIndexBuffer;
	

	std::vector<TSubset> m_aSubsets;
	std::vector<TMaterial> m_aMaterials;
	std::vector<EInputType> m_aInputLayout;


	std::vector<uint> m_aAttribruteTable;


};


#include "Model.inl"


#endif //__Model_H__