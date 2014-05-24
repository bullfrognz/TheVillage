//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   Renderer.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Renderer_H__
#define __Renderer_H__


// Library Includes
#include <Windows.h>


// Local Includes
#include "Defines\DataTypes.h"
#include "Framework\Text.h"
#include "Framework\Texture.h"
#include "Framework\IndexBuffer.h"
#include "Framework\VertexBuffer.h"
#include "Framework\Effect.h"


// Types


// Constants


// Prototypes
struct TTextDesc;

class IEffect;
class CWorldMatrix;
class CViewMatrix;
class CMatrix;

enum EEffect;


class IRenderer
{

	// Member Types
public:


	enum EState
	{
		INVALID_STATE,

		STATE_BLEND			= 1 << 0,
		STATE_RASTERIZER	= 1 << 1,
		STATE_DEPTHSTENCIL	= 1 << 2,

		MAX_SATE
	};


	enum ECullMode
	{
		INVALID_CULLMODE,

		CULLMODE_NONE,	// Draw all triangles
		CULLMODE_FRONT,	// Do not draw front-facing triangles
		CULLMODE_BACK,	// Do not draw back-facing triangles

		MAX_CULLMODE
	};


	enum EFillMode
	{
		INVALID_FILLMODE,

		FILLMODE_SOLID,
		FILLMODE_WIREFRAME,

		MAX_FILLMODE
	};


	enum EFrontFacingDirection
	{
		INVALID_FRONTFACINGDIR,

		FRONTFACINGDIR_CLOCKWISE,
		FRONTFACINGDIR_ANTICLOCKWISE,

		MAX_FRONTFACINGDIR
	};


	struct TRasterizerDesc
	{
		ECullMode eCullMode;
		EFillMode eFillMode;
		EFrontFacingDirection eFrontFacingDi;
		bool bDepthClipEnabled;
		bool bMultisampleEnabled;
	};


	// Member Functions
public:


			 IRenderer() {};
	virtual ~IRenderer() {};


	virtual bool Initialise(HWND& _hrWindowHandle, uint _uiBufferWidth, uint _uiBufferHeight, bool _bFullscreen) = 0;
	virtual bool BeginRendering(bool _bClearTarget, bool _bClearDepth, bool _bClearStencil) = 0;
	virtual bool EndRendering() = 0;

	
	virtual bool SetActiveEffect(IEffect* _pEffect, const char* _kcpTechnique) = 0;
	virtual bool SetActiveVertexBuffer(IVertexBuffer* _pVertexBuffer, uint _uiOffset) = 0;


	virtual bool Draw(uint _uiNumVertices, uint _uiOffset) = 0;
	virtual bool DrawIndexed(IIndexBuffer* _pIndexBuffer, uint _uiNumIndices, uint _uiIndexOffset, uint _uiVertexOffset) = 0;
	virtual bool DrawIndexedMulti(IIndexBuffer* _pIndexBuffer, uint _uiDrawCount,  uint* _uipNumIndices, uint* _uipIndexOffsets, uint* _uipVertexOffsets) = 0;


	virtual bool InstanceEffect(const IEffect::TDesc& _ktrEffectDesc, IEffect*& _prEffect) = 0;
	virtual bool InstanceFont(const IText::TDesc& _ktrFontDesc, IText*& _prFont) = 0;
	virtual bool InstanceTexture(const ITexture::TDesc& _ktrTextureDesc, ITexture*& _prTexture) = 0;
	virtual bool InstanceVertexBuffer(const IVertexBuffer::TDesc& _ktrBufferDesc, IVertexBuffer*& _prVertexBuffer) = 0;
	virtual bool InstanceIndexBuffer(const IIndexBuffer::TDesc& _ktrBufferDesc, IIndexBuffer*& _prIndexBuffer) = 0;


	virtual bool RestoreDefaultStates(uint _uiStates) = 0;
	virtual bool EnableShadowDrawStates() = 0;
	virtual bool EnableLitDrawStates() = 0;


	virtual uint GetBufferWidth() const = 0;
	virtual uint GetBufferHeight() const = 0;


	// Inline Functions


protected:


private:


	IRenderer(const IRenderer& _krRenderer);
	IRenderer& operator = (const IRenderer& _krRenderer);


	// Member Variables
protected:


private:


};


#endif //__Renderer_H__