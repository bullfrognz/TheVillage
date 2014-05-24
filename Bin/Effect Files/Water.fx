//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name   :   Water.fx
//  Description :   ----------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// [Local Includes]
#include "TransformationHelper.fx"
#include "TextureHelper.fx"
#include "LightHelper.fx"


// [Globals]
float g_fHalfHeight;
float g_fHalfCycleTime;
float g_fTime;
float g_fBrightness = 1.0f;


// [Types]
struct VS_INPUT
{
	float3 vPosition	: POSITION;
	float2 vTexCoord	: TEXCOORD;
	bool   bUp			: DIRECTION;
};


struct PS_INPUT
{
	float4 vPosition		: SV_POSITION;
	float4 vWorldPosition	: POSITION;
	float2 vTexCoord	: TEXCOORD;
};


// [Shaders]


PS_INPUT
DefaultVertexShader(VS_INPUT _tInput)
{
	PS_INPUT tOutput;


	// Convert vertex to projection space
	tOutput.vPosition = mul(float4(_tInput.vPosition, 1.0f), g_xWorldViewProjection);


	float fHeightAdj = g_fHalfHeight * (g_fTime / g_fHalfCycleTime);


	if (_tInput.bUp)
	{
		tOutput.vPosition.y += fHeightAdj;
	}
	else
	{
		tOutput.vPosition.y -= fHeightAdj;
	}


	tOutput.vWorldPosition = mul(float4(_tInput.vPosition, 1.0f), g_xWorld);
	tOutput.vTexCoord = _tInput.vTexCoord;


	return (tOutput);
}



float4
DefaultPixelShader(PS_INPUT _tInput) : SV_Target
{
	float3 v3FinalColour = g_TextureResources[0].Sample(linearSampler, _tInput.vTexCoord);


    return (float4(v3FinalColour * g_fBrightness, 0.7f));
}





// [Techniques]
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


        SetVertexShader(CompileShader(vs_4_0, DefaultVertexShader()));
		SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, DefaultPixelShader()));
    }
}