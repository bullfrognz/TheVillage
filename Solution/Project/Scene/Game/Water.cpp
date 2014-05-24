//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   Water.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Defines\Macros.h"
#include "Framework\Renderer.h"
#include "Framework\Effect.h"
#include "Framework\VertexBuffer.h"
#include "Framework\IndexBuffer.h"
#include "Framework\Camera.h"


// This Include
#include "Water.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* Water constructors
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWater::CWater()
: m_pEffect(0)
, m_pVertexBuffer(0)
, m_pIndexBuffer(0)
, m_fHalfCycleTime(1.0f)
, m_fTime(0)
, m_uiWidth(0)
, m_uiLength(0)
, m_bGoingUp(true)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Water deconstructor
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWater::~CWater()
{
	Deinitialise();
}





bool
CWater::Initialise(IRenderer& _rRenderer, uint _uiWidth, uint _uiLength)
{
	m_uiWidth = _uiWidth;
	m_uiLength = _uiLength;


	// Force odd
	if ((m_uiWidth % 2) == 0)
	{
		m_uiWidth -= 1;
	}


	FW_VALIDATE(InitialiseEffect(_rRenderer));
	FW_VALIDATE(InitialiseVertexBuffer(_rRenderer));
	FW_VALIDATE(InitialiseIndexBuffer(_rRenderer));


	ITexture::TDesc tTextureDesc;
	tTextureDesc.eCPUAccess = ITexture::CPUACCESS_NONE;
	tTextureDesc.eBindFlag = ITexture::BINDFLAG_SHADERRESOURCE;
	tTextureDesc.eFormat = ITexture::FORMAT_R8G8B8A8;
	tTextureDesc.uiNumMipMaps = 5;
	tTextureDesc.kcpFile = "Assets/Textures/Water.png";


	FW_VALIDATE(_rRenderer.InstanceTexture(tTextureDesc, m_pTexture));


	m_pEffect->SetVariable("g_fHalfCycleTime", m_fHalfCycleTime);
	m_pEffect->SetVariable("g_fHalfHeight", 1.0f);
	m_pEffect->SetTextures(&m_pTexture, 1);


	return (true);
}





void
CWater::Process(float _fDeltatick)
{
	if (m_bGoingUp)
	{
		m_fTime += _fDeltatick;


		if (m_fTime > m_fHalfCycleTime)
		{
			m_bGoingUp = false;
		}
	}
	else
	{
		m_fTime -= _fDeltatick;


		if (m_fTime < m_fHalfCycleTime * -1)
		{
			m_bGoingUp = true;
		}
	}


	m_pEffect->SetVariable("g_fTime", m_fTime);
}





bool
CWater::Draw(IRenderer& _rRenderer, CCamera& _rPlayerCamera)
{
	FW_VALIDATE(_rRenderer.SetActiveVertexBuffer(m_pVertexBuffer, 0));
	FW_VALIDATE(_rRenderer.SetActiveEffect(m_pEffect, "DefaultTechnique"));


	FW_VALIDATE(m_pEffect->SetTransformations(CEntity::GetWorld(), _rPlayerCamera.GetView(), _rPlayerCamera.GetProjection()));


	FW_VALIDATE(_rRenderer.DrawIndexed(m_pIndexBuffer, m_pIndexBuffer->GetCapacity(), 0, 0));


	return (true);
}





/********************************
            Protected
*********************************/





bool
CWater::GenerateVertices(TVertex*& _tprVertices, uint& _rNumVertices)
{
	_rNumVertices = m_uiWidth * m_uiLength;


	_tprVertices = new TVertex[_rNumVertices];


	const float kfHalfWidth = m_uiWidth / 2.0f;
	const float kfHalfLength = m_uiLength / 2.0f;
	bool bDirection = false;


	float fUPerVertex = 1.0f / m_uiWidth;
	float fVPerVertex = 1.0f / m_uiLength;


	for (uint uiZ = 0; uiZ < m_uiLength; ++ uiZ)
	{
		for (uint uiX = 0; uiX < m_uiWidth; ++ uiX)
		{
			_tprVertices[uiZ * m_uiWidth + uiX].vPosition.Set((uiX - kfHalfWidth) * 16.0f,
															  0.0f,
															  (uiZ - kfHalfLength) * 16.0f);


			_tprVertices[uiZ * m_uiWidth + uiX].fU = fUPerVertex * uiX;
			_tprVertices[uiZ * m_uiWidth + uiX].fV = fVPerVertex * uiZ;
			_tprVertices[uiZ * m_uiWidth + uiX].bDirection = bDirection;


			bDirection = (bDirection) ? false : true;
		}
	}


	return (_tprVertices != 0);
}





void
CWater::GenerateIndices(std::vector<uint>& _arIndices)
{
	int iWidth = m_uiWidth;
	int iLength = m_uiLength;


    for (int i = 0; i < iLength - 1; ++i)
    {
        // Even rows move left to right, odd rows move right to left.
        if(i % 2 == 0)
		{
            // Even row
            int j;
            for(j = 0; j < iWidth; ++j)
            {
				_arIndices.push_back( (j + (i * iWidth)) );
                _arIndices.push_back( (j + (i * iWidth) + iWidth) );
            }


            // Insert degenerate vertex if this isn't the last row
            if(i != iLength - 2)
            {
			   //Vertex3 = &pVertexData[iIndex];
               _arIndices.push_back( (--j + (i * iWidth)) );
            }
        }
        else
        {
            // Odd row
            int j;
            for(j = iWidth - 1; j >= 0; --j)
            {
                _arIndices.push_back( (j + (i * iWidth)) );
                _arIndices.push_back( (j + (i * iWidth) + iWidth) );
            }


            // Insert degenerate vertex if this isn't the last row
            if(i != iLength - 2)
            {
                _arIndices.push_back( (++j + (i * iWidth)) );
            }
        }
    }
}





/********************************
            Private
*********************************/





bool
CWater::InitialiseEffect(IRenderer& _rRenderer)
{
	IEffect::TDesc tEffectDesc;
	tEffectDesc.kcpEffectFile = "Water.fx";
	tEffectDesc.bTransformationHelper = true;
	//tEffectDesc.bLightHelper = true;
	tEffectDesc.bTextureHelper = true;


	// Default technique
	IEffect::TTechnqiue tDefaultTechnique;
	tDefaultTechnique.kcpName = "DefaultTechnique";


	IEffect::TInput tPosition;
	tPosition.kcpName = "POSITION";
	tPosition.eVariableType = IEffect::VARIABLETYPE_FLOAT3;
	tDefaultTechnique.aInputLayout.push_back(tPosition);


	IEffect::TInput tTexCoord;
	tTexCoord.kcpName = "TEXCOORD";
	tTexCoord.eVariableType = IEffect::VARIABLETYPE_FLOAT2;
	tDefaultTechnique.aInputLayout.push_back(tTexCoord);


	IEffect::TInput tDirection;
	tDirection.kcpName = "DIRECTION";
	tDirection.eVariableType = IEffect::VARIABLETYPE_BOOL;
	tDefaultTechnique.aInputLayout.push_back(tDirection);


	tEffectDesc.aTechniques.push_back(tDefaultTechnique);


	// Variables
	tEffectDesc.aVariableNames.push_back("g_fHalfHeight");
	tEffectDesc.aVariableNames.push_back("g_fHalfCycleTime");
	tEffectDesc.aVariableNames.push_back("g_fTime");


	tEffectDesc.aVariableNames.push_back("g_fBrightness");


	FW_VALIDATE(_rRenderer.InstanceEffect(tEffectDesc, m_pEffect));


	return (true);
}





bool
CWater::InitialiseVertexBuffer(IRenderer& _rRenderer)
{
	TVertex* pVertexData = 0;
	uint uiNumVertices = 0;
	GenerateVertices(pVertexData, uiNumVertices);


	FW_DELETE(m_pVertexBuffer);

	
	IVertexBuffer::TDesc tVBufferDesc;
	memset(&tVBufferDesc, 0, sizeof(IVertexBuffer::TDesc));
	tVBufferDesc.eUsage = IVertexBuffer::USAGE_STATIC;
	tVBufferDesc.ePrimitiveType = IVertexBuffer::PRIMITIVETYPE_TRIANGLESTRIP;
	tVBufferDesc.uiStride = sizeof(CWater::TVertex);
	tVBufferDesc.uiNumVertices = uiNumVertices;
	tVBufferDesc.pInitialData = pVertexData;


	FW_VALIDATE(_rRenderer.InstanceVertexBuffer(tVBufferDesc, m_pVertexBuffer));
	FW_ADELETE(pVertexData);


	return (true);
}





bool
CWater::InitialiseIndexBuffer(IRenderer& _rRenderer)
{
	std::vector<uint> aIndices;
	aIndices.reserve(m_uiWidth * m_uiLength);


	GenerateIndices(aIndices);


	FW_DELETE(m_pIndexBuffer);


	IIndexBuffer::TDesc tIBufferDesc;
	tIBufferDesc.eIndexSize = IIndexBuffer::INDEXSIZE_32;
	tIBufferDesc.eUsage = IIndexBuffer::USAGE_STATIC;
	tIBufferDesc.uiIndicesCount = aIndices.size();
	tIBufferDesc.pInitialData = aIndices.data();


	FW_VALIDATE(_rRenderer.InstanceIndexBuffer(tIBufferDesc, m_pIndexBuffer));


	return (true);
}





void
CWater::Deinitialise()
{
	FW_DELETE(m_pEffect);
	FW_DELETE(m_pVertexBuffer);
	FW_DELETE(m_pIndexBuffer);
	FW_DELETE(m_pTexture);
}