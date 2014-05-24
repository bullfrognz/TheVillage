//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name   :   AABB.fx
//  Description :   ----------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// [Local Includes]
#include "TransformationHelper.fx"


// [Globals]


// [Types]
struct VS_INPUT
{
	float3 vPosition	: POSITION;
};


struct PS_INPUT
{
	float4 vPosition	: SV_POSITION;
};


// [Shaders]


PS_INPUT
DefaultVertexShader(VS_INPUT _tInput)
{
	PS_INPUT tOutput;


	// Convert vertex to projection space
	tOutput.vPosition = mul(float4(_tInput.vPosition, 1.0f), g_xWorldViewProjection);


	return (tOutput);
}


float4
DefaultPixelShader(PS_INPUT _tInput) : SV_Target
{
    return (float4(1.0f, 1.0f, 0.0f, 1.0f));
}





// [Techniques]


technique10 DefaultTechnique
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_4_0, DefaultVertexShader()));
		SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, DefaultPixelShader()));
    }
}