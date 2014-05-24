//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name   :   Star.fx
//  Description :   ----------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Local Includes


// Globals
cbuffer cbPerObject
{
	float4x4 g_xWorld;
	float4x4 g_xView;
	float4x4 g_xProjection;
	float4x4 g_xWorldViewProjection;
};


struct VS_INPUT
{
	float3 vPosition	: POSITION;
	float4 vDiffuse		: DIFFUSE;
};


struct VS_OUTPUT
{
	float4 vPosition	: SV_POSITION;
	float4 vDiffuse		: DIFFUSE;
};


// [Implementation]


VS_OUTPUT ProcessVertexShader(VS_INPUT _tInput)
{
	VS_OUTPUT tOutput;


	// Convert vertex to projection space
	tOutput.vPosition = mul(float4(_tInput.vPosition, 1.0f), g_xWorld);
	tOutput.vPosition = mul(tOutput.vPosition, g_xView);
	tOutput.vPosition = mul(tOutput.vPosition, g_xProjection);

	
	// Output vertex attributes for interpolation across triangle.
	tOutput.vDiffuse = _tInput.vDiffuse;


	return (tOutput);
}





/*
[maxvertexcount(4)]
void GS(point VS_OUTPUT input[1], inout TriangleStream<VS_OUTPUT> triangleStream)
{
}
*/




float4 ProcessPixelShader(VS_OUTPUT _tInput) : SV_Target
{
    return (_tInput.vDiffuse);
}





technique10 DefaultTechnique
{
    pass Pass0
    {
        SetVertexShader(CompileShader(vs_4_0, ProcessVertexShader()));

       // SetGeometryShader( CompileShader( gs_4_0, GS() ) );	

        SetPixelShader(CompileShader(ps_4_0, ProcessPixelShader()));
    }
}