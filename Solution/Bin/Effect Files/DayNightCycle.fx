//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name   :   TerrainEffect.fx
//  Description :   ----------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Local Includes
#include "TransformationHelper.fx"
#include "TextureHelper.fx"


// Globals
struct VS_INPUT
{
	float3 vPosition	: POSITION;
	float3 vNormal		: NORMAL;
	float2 vTextureUV	: TEXCOORD_ONE;
};


struct GS_INPUT
{
	float4 vPosition	: SV_POSITION;
	float2 vTextureUV	: TEXCOORD;
};


// [Implementation]


GS_INPUT ProcessVertexShader(VS_INPUT _tInput)
{
	GS_INPUT tOutput;


	// Convert vertex to projection space
	tOutput.vPosition = mul(float4(_tInput.vPosition, 1.0f), g_xWorldViewProjection);


	tOutput.vTextureUV = _tInput.vTextureUV;


	return (tOutput);
}





float4 ProcessPixelShader(GS_INPUT _tInput) : SV_Target
{
	float4 vFinalColour = float4(0.0f, 0.0f, 0.0f, 0.0f);


	if (g_iTextureCount > 0)
	{
		float4 vTexelColour1 = g_TextureResources[0].Sample(linearSampler, _tInput.vTextureUV);
		vFinalColour = vTexelColour1;
	}


    return (vFinalColour);
}




BlendState AlphaEnabled
{
   BlendEnable[0]           = TRUE;
   SrcBlend                 = SRC_ALPHA;
   DestBlend                = INV_SRC_ALPHA;
   BlendOp                  = ADD;
   SrcBlendAlpha            = ONE;
   DestBlendAlpha           = ONE;
   BlendOpAlpha             = ADD;
   RenderTargetWriteMask[0] = 0x0F;
};



technique10 DefaultTechnique
{
    pass P0
    {
		SetBlendState(AlphaEnabled, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);


        SetVertexShader(CompileShader(vs_4_0, ProcessVertexShader()));
		SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, ProcessPixelShader()));
    }
}