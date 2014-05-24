//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   Model.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <vector>


#include <D3DX10.h>
#include <D3dx9mesh.h>


// Local Includes
#include "Framework\Renderer.h"
#include "Framework\VertexBuffer.h"
#include "Framework\IndexBuffer.h"
#include "Framework\Texture.h"
#include "Math\Vector3.h"
#include "Math\Vector2.h"
#include "Utilities\StrUtilities.h"
#include "Defines\Macros.h"


#include "Framework\DirectX 10\D10Renderer.h"


// This Include
#include "Model.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* Model constructors
*
*---------------------------------------------------------------------------------------------------------------------------*/

CModel::CModel()
: m_cpFile(0)
, m_pVertexBuffer(0)
, m_pIndexBuffer(0)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Model deconstructor
*
*---------------------------------------------------------------------------------------------------------------------------*/

CModel::~CModel()
{
	Deinitialise();
}





bool
CModel::Initialise(IRenderer& _rRenderer, const char* _kcpFile, const std::vector<EInputType>& _karInputLayout)
{
	StrUtilities::Copy(_kcpFile, m_cpFile);
	m_aInputLayout = _karInputLayout;


	std::vector<float> aVertexData;
	std::vector<uint> aIndices;


	Assimp::Importer Importer;
	const aiScene* ktpScene = Importer.ReadFile(_kcpFile, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_FlipWindingOrder | aiProcess_MakeLeftHanded);


	FW_VALIDATE(ktpScene != 0);
	

	// Create vertex buffer
	FW_VALIDATE(InitialiseMaterials(_rRenderer, ktpScene));
	FW_VALIDATE(InitialiseSubsets(_rRenderer, ktpScene, aVertexData, aIndices));
	//FW_VALIDATE(InitialiseIndexBuffer(_rRenderer, aIndices));
	//FW_VALIDATE(InitialiseVertexBuffer(_rRenderer, aVertexData));



	const D3D10_INPUT_ELEMENT_DESC g_vertexLitTexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0},
	};


	D3DX10CreateMesh(static_cast<CD10Renderer&>(_rRenderer).GetDevice(),
												g_vertexLitTexDesc,
												3,
												"POSITION",
												aVertexData.size() / (ComputeStride() / sizeof(float)),
												aIndices.size() / 3,
												D3DX10_MESH_32_BIT,
												&pMesh);


	pMesh->SetVertexData(0, aVertexData.data());
	pMesh->SetIndexData(aIndices.data(), aIndices.size());
	pMesh->SetAttributeData(m_aAttribruteTable.data());


	pMesh->GenerateAdjacencyAndPointReps(0.1f);
	pMesh->Optimize(D3DXMESHOPT_ATTRSORT , 0, 0);


	pMesh->GenerateGSAdjacency();
	pMesh->CommitToDevice();


	return (true);
}





bool 
CModel::Draw(IRenderer& _rRenderer, IEffect& _rEffect)
{
	//FW_VALIDATE(_rRenderer.SetActiveVertexBuffer(m_pVertexBuffer, 0))


	const uint kuiNumSubsets = m_aSubsets.size();


	for (uint uiSubset = 0; uiSubset < kuiNumSubsets; ++ uiSubset)
	{
		FW_VALIDATE(DrawSubset(_rRenderer, uiSubset, _rEffect));
	}


	return (true);
}





/********************************
            Protected
*********************************/





bool
CModel::DrawSubset(IRenderer& _rRenderer, uint _uiSubsetId, IEffect& _rEffect)
{
	const CModel::TSubset& ktrSubset = GetSubset(_uiSubsetId);
	const CModel::TMaterial& ktrMaterial = GetMaterial(ktrSubset.uiMaterialId);


	if (ktrMaterial.uiNumTextures > 0)
	{
		FW_VALIDATE(_rEffect.SetTextures(ktrMaterial.ppTextures, ktrMaterial.uiNumTextures));
	}
	else
	{
		FW_VALIDATE(_rEffect.SetTextures(0, 0));
	}


	for (uint i = 0; i < static_cast<CD10Renderer&>(_rRenderer).GetActiveEffect().uiNumDrawPasses; ++ i)
	{
		HRESULT hResutlt = static_cast<CD10Renderer&>(_rRenderer).GetActiveEffect().pTechnique->GetPassByIndex(i)->Apply(0);
		assert(SUCCEEDED(hResutlt));


		pMesh->DrawSubset(_uiSubsetId);


		//FW_VALIDATE(_rRenderer.DrawIndexed(m_pIndexBuffer, m_aSubsets[_uiSubsetId].uiNumIndices, m_aSubsets[_uiSubsetId].uiIndexOffset, 0));
	}


	return (true);
}





uint
CModel::ComputeStride()
{
	uint uiStride = 0;


	for (uint i = 0; i < m_aInputLayout.size(); ++ i)
	{
		switch (m_aInputLayout[i])
		{
		case INPUTTYPE_POSITION:
		case INPUTTYPE_NORMAL:
			uiStride += 12;
			break;

		case INPUTTYPE_TEXTCOORDS1:
		case INPUTTYPE_TEXTCOORDS2:
			uiStride += 8;
			break;
		}
	}


	return (uiStride);
}





bool
CModel::ExtractVertexData(const aiMesh* _tpMesh, std::vector<float>& _arVertexData)
{
	std::vector<CVector3> aVertexPositions;
	std::vector<CVector3> aVertexNormals;
	std::vector<CVector2> aVertexTextureCoords;


	// Extract vertex info
	for (uint uiVertex = 0; uiVertex < _tpMesh->mNumVertices; ++ uiVertex)
	{
		CVector3 Position(_tpMesh->mVertices[uiVertex].x, _tpMesh->mVertices[uiVertex].y, _tpMesh->mVertices[uiVertex].z);
		aVertexPositions.push_back(Position);


		// Vertex normals
		if (_tpMesh->HasNormals())
		{
			CVector3 Normal(_tpMesh->mNormals[uiVertex].x, _tpMesh->mNormals[uiVertex].y, _tpMesh->mNormals[uiVertex].z);
			aVertexNormals.push_back(Normal);
		}


		// Vertex texture coordinates
		if (_tpMesh->HasTextureCoords(0))
		{
			CVector2 TextureCoords(_tpMesh->mTextureCoords[0][uiVertex].x, _tpMesh->mTextureCoords[0][uiVertex].y);
			aVertexTextureCoords.push_back(TextureCoords);
		}
	}


	// Sort vertex data
	for (uint uiVertex = 0; uiVertex < _tpMesh->mNumVertices; ++ uiVertex)
	{
		for (uint i = 0; i < m_aInputLayout.size(); ++ i)
		{
			switch (m_aInputLayout[i])
			{
			case INPUTTYPE_POSITION:
				_arVertexData.push_back(aVertexPositions[uiVertex].GetX());
				_arVertexData.push_back(aVertexPositions[uiVertex].GetY());
				_arVertexData.push_back(aVertexPositions[uiVertex].GetZ());
				break;

			case INPUTTYPE_NORMAL:
				_arVertexData.push_back(aVertexNormals[uiVertex].GetX());
				_arVertexData.push_back(aVertexNormals[uiVertex].GetY());
				_arVertexData.push_back(aVertexNormals[uiVertex].GetZ());
				break;

			case INPUTTYPE_TEXTCOORDS1:
				_arVertexData.push_back(aVertexTextureCoords[uiVertex].GetX());
				_arVertexData.push_back(aVertexTextureCoords[uiVertex].GetY());
				break;

			case INPUTTYPE_TEXTCOORDS2:
			default:
				// Unknown component
				assert(false);
				break;
			}
		}
	}


	return (true);
}





bool
CModel::ExtractIndexData(const aiMesh* _tpMesh, uint _uiVertexCount, std::vector<uint>& _arIndices)
{
	// Extract indices
	for (uint uiFace = 0; uiFace < _tpMesh->mNumFaces; ++ uiFace)
	{
		aiFace& trFace = _tpMesh->mFaces[uiFace];


		for (uint uiIndex = 0; uiIndex < trFace.mNumIndices; ++ uiIndex)
		{
			_arIndices.push_back(_uiVertexCount + trFace.mIndices[uiIndex]);
		}
	}


	return (true);
}





bool
CModel::AddMaterial(IRenderer& _rRenderer, const aiMaterial* _ktpSceneMaterial)
{
	TMaterial tMaterial;
	tMaterial.ppTextures = 0;
	tMaterial.uiNumTextures = _ktpSceneMaterial->GetTextureCount(aiTextureType_DIFFUSE);


	if (tMaterial.uiNumTextures > 0)
	{
		tMaterial.ppTextures = new ITexture*[tMaterial.uiNumTextures];


		ITexture::TDesc tTextureDesc;
		memset(&tTextureDesc, 0, sizeof(ITexture::TDesc));
		tTextureDesc.eBindFlag = ITexture::BINDFLAG_SHADERRESOURCE;
		tTextureDesc.eCPUAccess = ITexture::CPUACCESS_NONE;
		tTextureDesc.eFormat = ITexture::FORMAT_R8G8B8A8;
		tTextureDesc.eUsage = ITexture::USAGE_STATIC;
		tTextureDesc.uiNumMipMaps = 1;


		for (uint uiTexture = 0; uiTexture < tMaterial.uiNumTextures; ++ uiTexture)
		{
			// Get texture file path
			aiString* pString = new aiString;
			_ktpSceneMaterial->GetTexture(aiTextureType_DIFFUSE, 0, pString);


			std::string TextureFile;
			TextureFile = StrUtilities::DirectoryPath(m_cpFile);
			TextureFile += pString->C_Str();


			tTextureDesc.kcpFile = TextureFile.c_str();


			FW_VALIDATE(_rRenderer.InstanceTexture(tTextureDesc, tMaterial.ppTextures[uiTexture]));


			FW_DELETE(pString);
		}
	}


	m_aMaterials.push_back(tMaterial);


	return (true);
}





bool
CModel::AddSubset(const aiMesh* _ktpMesh, std::vector<float>& _arVertexData, std::vector<uint>& _arIndexData)
{
	uint uiStartIndexCount = _arIndexData.size();
	uint uiStartVertexCount = _arVertexData.size() / (ComputeStride() / sizeof(float));


	ExtractVertexData(_ktpMesh, _arVertexData);
	ExtractIndexData(_ktpMesh, uiStartVertexCount, _arIndexData);


	// Create subset info
	TSubset tSubset;
	tSubset.pName = 0;
	tSubset.uiNumIndices = _arIndexData.size() - uiStartIndexCount;
	tSubset.uiIndexOffset = uiStartIndexCount;
	tSubset.uiMaterialId = _ktpMesh->mMaterialIndex;


	// Set subset name
	if (_ktpMesh->mName.length > 0)
	{
		StrUtilities::Copy(_ktpMesh->mName.C_Str(), tSubset.pName);
	}


	m_aSubsets.push_back(tSubset);



	return (true);
}





/********************************
            Private
*********************************/





bool
CModel::InitialiseMaterials(IRenderer& _rRenderer, const aiScene* _ktpScene)
{

	for (uint uiMaterial = 0; uiMaterial < _ktpScene->mNumMaterials; ++ uiMaterial)
	{
		AddMaterial(_rRenderer, _ktpScene->mMaterials[uiMaterial]);
	}


	return (true);
}





bool
CModel::InitialiseSubsets(IRenderer& _rRenderer, const aiScene* _ktpScene, std::vector<float>& _arVertexData, std::vector<uint>& _arIndexData)
{
	for (uint  i = 0; i < _ktpScene->mNumMeshes; ++ i)
	{
		AddSubset(_ktpScene->mMeshes[i], _arVertexData, _arIndexData);


		for (uint uiFace = 0; uiFace < _ktpScene->mMeshes[i]->mNumFaces; ++ uiFace)
		{
			m_aAttribruteTable.push_back(i);
		}
	}


	return (true);
}





bool
CModel::InitialiseVertexBuffer(IRenderer& _rRenderer, std::vector<float>& _arVertexData)
{
	FW_DELETE(m_pVertexBuffer);

	
	IVertexBuffer::TDesc tVBufferDesc;
	memset(&tVBufferDesc, 0, sizeof(IVertexBuffer::TDesc));
	tVBufferDesc.eUsage = IVertexBuffer::USAGE_STATIC;
	tVBufferDesc.ePrimitiveType = IVertexBuffer::PRIMITIVETYPE_TRIANGLELIST;
	tVBufferDesc.uiStride = ComputeStride();
	tVBufferDesc.uiNumVertices = _arVertexData.size() / (tVBufferDesc.uiStride / sizeof(float));
	tVBufferDesc.pInitialData = _arVertexData.data();


	FW_VALIDATE(_rRenderer.InstanceVertexBuffer(tVBufferDesc, m_pVertexBuffer));


	return (true);
}





bool
CModel::InitialiseIndexBuffer(IRenderer& _rRenderer, std::vector<uint>& _arIndexData)
{
	FW_DELETE(m_pIndexBuffer);


	IIndexBuffer::TDesc tIBufferDesc;
	tIBufferDesc.eIndexSize = IIndexBuffer::INDEXSIZE_32;
	tIBufferDesc.eUsage = IIndexBuffer::USAGE_STATIC;
	tIBufferDesc.uiIndicesCount = _arIndexData.size();
	tIBufferDesc.pInitialData = _arIndexData.data();


	FW_VALIDATE(_rRenderer.InstanceIndexBuffer(tIBufferDesc, m_pIndexBuffer));


	return (true);
}





void
CModel::Deinitialise()
{
	FW_DELETE(m_pVertexBuffer);
	FW_DELETE(m_pIndexBuffer);
	FW_ADELETE(m_cpFile);


	for (uint i = 0; i < m_aMaterials.size(); ++ i)
	{
		for (uint j = 0; j < m_aMaterials[i].uiNumTextures; ++ j)
		{
			FW_DELETE(m_aMaterials[i].ppTextures[j]);
		}


		FW_ADELETE(m_aMaterials[i].ppTextures);
	}


	FW_RELEASE(pMesh);
}