//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   Cube.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Defines\Macros.h"
#include "Math\WorldMatrix.h"
#include "Math\ViewMatrix.h"
#include "Math\ProjMatrix.h"
#include "Framework\Renderer.h"
#include "Framework\VertexBuffer.h"
#include "Framework\IndexBuffer.h"
#include "Framework\Effect.h"
#include "Framework\Camera.h"


// This Include
#include "Cube.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CCube constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CCube::CCube()
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CCube deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CCube::~CCube()
{
	Deinitialise();
}





bool
CCube::Initialise(IRenderer& _rRenderer)
{
	FW_VALIDATE(InitialiseEffectFile(_rRenderer));
	FW_VALIDATE(InitialiseVertexBuffer(_rRenderer));
	FW_VALIDATE(InitialiseIndexBuffer(_rRenderer));


	FW_VALIDATE(FillVertexBuffer());
	FW_VALIDATE(FillIndexBuffer());


	return (true);
}





bool
CCube::Process(float _fDeltaTick)
{
	CEntity::AddRotationY(1.0f * _fDeltaTick);
	CEntity::AddRotationX(1.0f * _fDeltaTick);


	return (true);
}





bool
CCube::DrawShadow(IRenderer& _rRenderer, CCamera& _rActiveCamera, std::vector<CLight*>& _rActiveLights)
{
	return (true);
	m_pEffect->SetLights(&(*_rActiveLights.begin()), _rActiveLights.size(), _rActiveCamera.GetPosition());
	m_pEffect->SetTransformations(CEntity::GetWorld(), _rActiveCamera.GetProjection(), _rActiveCamera.GetProjection());


	_rRenderer.SetActiveEffect(m_pEffect, "RenderShadow");
	_rRenderer.SetActiveVertexBuffer(m_pVertexBuffer, 0);
	_rRenderer.DrawIndexed(m_pIndexBuffer, m_pIndexBuffer->GetCapacity(), 0, 0);


	return (true);
}





bool
CCube::Draw(IRenderer& _rRenderer, CCamera& _rActiveCamera, std::vector<CLight*>& _rActiveLights)
{
	m_pEffect->SetLights(&(*_rActiveLights.begin()), _rActiveLights.size(), _rActiveCamera.GetPosition());
	m_pEffect->SetTransformations(CEntity::GetWorld(), _rActiveCamera.GetView(), _rActiveCamera.GetProjection());


	_rRenderer.SetActiveEffect(m_pEffect, "RenderDefault");
	_rRenderer.SetActiveVertexBuffer(m_pVertexBuffer, 0);
	_rRenderer.DrawIndexed(m_pIndexBuffer, m_pIndexBuffer->GetCapacity(), 0, 0);


	return (true);
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





bool
CCube::InitialiseEffectFile(IRenderer& _rRenderer)
{
	IEffect::TDesc tEffectDesc;
	tEffectDesc.kcpEffectFile = "Cube.fx";
	tEffectDesc.bTransformationHelper = true;
	tEffectDesc.bLightHelper = true;


	// Default technique
	IEffect::TTechnqiue tDefaultTechnique;
	tDefaultTechnique.kcpName = "RenderDefault";


	IEffect::TInput tPosition;
	tPosition.kcpName = "POSITION";
	tPosition.eVariableType = IEffect::VARIABLETYPE_FLOAT3;
	tDefaultTechnique.aInputLayout.push_back(tPosition);


	IEffect::TInput tNormal;
	tNormal.kcpName = "NORMAL";
	tNormal.eVariableType = IEffect::VARIABLETYPE_FLOAT3;
	tDefaultTechnique.aInputLayout.push_back(tNormal);


	// Shadow technique
	IEffect::TTechnqiue tShadowTechnique;
	tShadowTechnique.kcpName = "RenderShadow";
	tShadowTechnique.aInputLayout = tDefaultTechnique.aInputLayout;


	tEffectDesc.aTechniques.push_back(tDefaultTechnique);
	tEffectDesc.aTechniques.push_back(tShadowTechnique);


	FW_VALIDATE(_rRenderer.InstanceEffect(tEffectDesc, m_pEffect));


	return (true);
}





bool
CCube::InitialiseVertexBuffer(IRenderer& _rRenderer)
{
	IVertexBuffer::TDesc tVBufferDesc;


	tVBufferDesc.ePrimitiveType = IVertexBuffer::PRIMITIVETYPE_TRIANGLELIST;
	tVBufferDesc.eUsage = IVertexBuffer::USAGE_DYNAMIC;
	tVBufferDesc.uiNumVertices = 24;
	tVBufferDesc.uiStride = sizeof(TVertex);


	FW_VALIDATE(_rRenderer.InstanceVertexBuffer(tVBufferDesc, m_pVertexBuffer));


	return (true);
}





bool
CCube::InitialiseIndexBuffer(IRenderer& _rRenderer)
{
	IIndexBuffer::TDesc tIBufferDesc;


	tIBufferDesc.eIndexSize = IIndexBuffer::INDEXSIZE_32;
	tIBufferDesc.eUsage = IIndexBuffer::USAGE_DYNAMIC;
	tIBufferDesc.uiIndicesCount = 36;


	FW_VALIDATE(_rRenderer.InstanceIndexBuffer(tIBufferDesc, m_pIndexBuffer));


	return (true);
}





bool
CCube::FillVertexBuffer()
{
	TVertex* pVertexData = 0;
	FW_VALIDATE(m_pVertexBuffer->Lock(IVertexBuffer::LOCKFLAG_WRITEDISCARD, reinterpret_cast<void**>(&pVertexData)));

	
	// Back
	(pVertexData ++)->mPosition.Set(-1.0f,  1.0f, -1.0f);
	(pVertexData ++)->mPosition.Set( 1.0f,  1.0f, -1.0f);
	(pVertexData ++)->mPosition.Set( 1.0f, -1.0f, -1.0f);
	(pVertexData ++)->mPosition.Set(-1.0f, -1.0f, -1.0f);
	(pVertexData - 4)->mNormal.Set( 0.0f,  0.0f, -1.0f);
	(pVertexData - 3)->mNormal.Set( 0.0f,  0.0f, -1.0f);
	(pVertexData - 2)->mNormal.Set( 0.0f,  0.0f, -1.0f);
	(pVertexData - 1)->mNormal.Set( 0.0f,  0.0f, -1.0f);


	// Top
	(pVertexData ++)->mPosition.Set(-1.0f,  1.0f,  1.0f);
	(pVertexData ++)->mPosition.Set( 1.0f,  1.0f,  1.0f);
	(pVertexData ++)->mPosition.Set( 1.0f,  1.0f, -1.0f);
	(pVertexData ++)->mPosition.Set(-1.0f,  1.0f, -1.0f);
	(pVertexData - 4)->mNormal.Set( 0.0f,  1.0f,  0.0f);
	(pVertexData - 3)->mNormal.Set( 0.0f,  1.0f,  0.0f);
	(pVertexData - 2)->mNormal.Set( 0.0f,  1.0f,  0.0f);
	(pVertexData - 1)->mNormal.Set( 0.0f,  1.0f,  0.0f);
	

	// Bottom
	(pVertexData ++)->mPosition.Set(-1.0f, -1.0f, -1.0f);
	(pVertexData ++)->mPosition.Set( 1.0f, -1.0f, -1.0f);
	(pVertexData ++)->mPosition.Set( 1.0f, -1.0f,  1.0f);
	(pVertexData ++)->mPosition.Set(-1.0f, -1.0f,  1.0f);
	(pVertexData - 4)->mNormal.Set( 0.0f, -1.0f,  0.0f);
	(pVertexData - 3)->mNormal.Set( 0.0f, -1.0f,  0.0f);
	(pVertexData - 2)->mNormal.Set( 0.0f, -1.0f,  0.0f);
	(pVertexData - 1)->mNormal.Set( 0.0f, -1.0f,  0.0f);
	

	// Front
	(pVertexData ++)->mPosition.Set(-1.0f, -1.0f,  1.0f);	
	(pVertexData ++)->mPosition.Set( 1.0f, -1.0f,  1.0f);
	(pVertexData ++)->mPosition.Set( 1.0f,  1.0f,  1.0f);	
	(pVertexData ++)->mPosition.Set(-1.0f,  1.0f,  1.0f);	
	(pVertexData - 4)->mNormal.Set( 0.0f,  0.0f,  1.0f);
	(pVertexData - 3)->mNormal.Set( 0.0f,  0.0f,  1.0f);
	(pVertexData - 2)->mNormal.Set( 0.0f,  0.0f,  1.0f);
	(pVertexData - 1)->mNormal.Set( 0.0f,  0.0f,  1.0f);
	

	// Right
	(pVertexData ++)->mPosition.Set( 1.0f,  1.0f, -1.0f);
	(pVertexData ++)->mPosition.Set( 1.0f,  1.0f,  1.0f);
	(pVertexData ++)->mPosition.Set( 1.0f, -1.0f,  1.0f);
	(pVertexData ++)->mPosition.Set( 1.0f, -1.0f, -1.0f);
	(pVertexData - 4)->mNormal.Set( 1.0f,  0.0f,  0.0f);
	(pVertexData - 3)->mNormal.Set( 1.0f,  0.0f,  0.0f);
	(pVertexData - 2)->mNormal.Set( 1.0f,  0.0f,  0.0f);
	(pVertexData - 1)->mNormal.Set( 1.0f,  0.0f,  0.0f);


	// Left
	(pVertexData ++)->mPosition.Set(-1.0f,  1.0f,  1.0f);
	(pVertexData ++)->mPosition.Set(-1.0f,  1.0f, -1.0f);
	(pVertexData ++)->mPosition.Set(-1.0f, -1.0f, -1.0f);
	(pVertexData ++)->mPosition.Set(-1.0f, -1.0f,  1.0f);
	(pVertexData - 4)->mNormal.Set(-1.0f,  0.0f,  0.0f);
	(pVertexData - 3)->mNormal.Set(-1.0f,  0.0f,  0.0f);
	(pVertexData - 2)->mNormal.Set(-1.0f,  0.0f,  0.0f);
	(pVertexData - 1)->mNormal.Set(-1.0f,  0.0f,  0.0f);


	m_pVertexBuffer->Unlock();


	return (true);
}





bool
CCube::FillIndexBuffer()
{
	int* pIndexData = 0;
	FW_VALIDATE(m_pIndexBuffer->Lock(IIndexBuffer::LOCKFLAG_WRITEDISCARD, reinterpret_cast<void**>(&pIndexData)));


	int g_Indices[36] = {0,1,2,0,2,3,						
						 4,5,6,4,6,7,							
						 8,9,10,8,10,11,							
						 12,13,14,12,14,15,							
						 16,17,18,16,18,19,							
						 20,21,22,20,22,23};

	memcpy(pIndexData, g_Indices, sizeof(int) * 36);


	m_pIndexBuffer->Unlock();


	return (true);
}





void
CCube::Deinitialise()
{
	FW_DELETE(m_pVertexBuffer);
	FW_DELETE(m_pIndexBuffer);
	FW_DELETE(m_pEffect);
}