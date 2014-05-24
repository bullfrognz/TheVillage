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
float4 g_v4Diffuse;


// Types
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
	float3 vFinalColour = float3(0.0f, 0.0f, 0.0f);


	if (g_iTextureCount > 0)
	{
		float3 vTexelColour1 = g_TextureResources[0].Sample(linearSampler, _tInput.vTextureUV);
		vFinalColour = vTexelColour1;
	}


	vFinalColour = saturate(vFinalColour * g_v4Diffuse);


    return (float4(vFinalColour, 1.0f));
}






technique10 DefaultTechnique
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_4_0, ProcessVertexShader()));
		SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, ProcessPixelShader()));
    }
}