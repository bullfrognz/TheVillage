//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name   :   CubeEffect.fx
//  Description :   ----------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Local Includes
#include "TransformationHelper.fx"
#include "LightHelper.fx"
#include "ShadowHelper.fx"


// Globals


// [Implementation]


// Types
struct VS_INPUT
{
	float3 vPosition	: POSITION;
	float3 vNormal		: NORMAL;
};


struct PS_INPUT
{
	float4 vPosition	: SV_POSITION;
	float3 vPositionW	: POSITION;
	float3 vNormalW		: NORMAL;
};


// Shaders


PS_INPUT
DefaultVertexShader(VS_INPUT _tInput)
{
	PS_INPUT tOutput;


	// Convert vertex to projection space
	tOutput.vPosition = mul(float4(_tInput.vPosition, 1.0f), g_xWorldViewProjection);


	// Transform to world space space.
	tOutput.vPositionW = mul(float4(_tInput.vPosition, 1.0f), g_xWorld);
	tOutput.vNormalW = mul(float4(_tInput.vNormal, 0.0f), g_xWorld);


	return (tOutput);
}


float4
DefaultPixelShader(PS_INPUT _tInput) : SV_Target
{
	TSurfaceInfo tSurfaceInfo = {_tInput.vPositionW, _tInput.vNormalW, float4(1.0f, 1.0f, 1.0f, 1.0f), float4(1.0f, 1.0f, 1.0f, 1.0f)};


	float3 vLitColour = float3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < g_iNumLights; ++ i)
	{
		// Parallel
		if(g_tLight[i].iType == 1) 
		{
			vLitColour += ParallelLight(tSurfaceInfo, g_tLight[i], g_vCameraPosition);
		}


		// Point
		else if(g_tLight[i].iType == 2) 
		{
			vLitColour += PointLight(tSurfaceInfo, g_tLight[i], g_vCameraPosition);
		}


		// Spot
		else if(g_tLight[i].iType == 3) 
		{
			vLitColour += Spotlight(tSurfaceInfo, g_tLight[i], g_vCameraPosition);
		}
	}


    return (float4(vLitColour, 1.0f));
}


// Techniques

technique10 RenderDefault
{
    pass Pass0
    {
        SetVertexShader(CompileShader(vs_4_0, DefaultVertexShader()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, DefaultPixelShader()));
    }
}





// [Shadow Implementation]


// Types


// Shaders





/*---------------------------------------------------------------------------------------------------------------------------
*
*	 GS for generating shadow volumes
*
*---------------------------------------------------------------------------------------------------------------------------*/

GS_SHADOW_INPUT
ShadowVertexShader(VS_INPUT _tInput)
{
	GS_SHADOW_INPUT tOutput;


	// Convert vertex to projection space
	tOutput.vPosition = mul(float4(_tInput.vPosition, 1.0f), g_xWorldViewProjection);


	// Transform to world space space.
	tOutput.vNormalW = mul(float4(_tInput.vNormal, 0.0f), g_xWorld);


	return (tOutput);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
*	 GS for generating shadow volumes
*
*---------------------------------------------------------------------------------------------------------------------------*/

[maxvertexcount(18)]
void
ShadowGeometryShader(triangleadj GS_SHADOW_INPUT _tVertices[6], inout TriangleStream<PS_SHADOW_INPUT> _ShadowTriangleStream)
{
	PS_SHADOW_INPUT tOutput;
	tOutput.vPosition = float4(_tVertices[0].vPosition, 1.0f);


	_ShadowTriangleStream.Append(tOutput);
}




float4
ShadowPixelShader(PS_SHADOW_INPUT input) : SV_Target
{   
    return float4(0.0f, 0.0f, 0.0f, 0.5f );
}





technique10 RenderShadow
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_4_0, ShadowVertexShader() ) );
        SetGeometryShader( CompileShader( gs_4_0, ShadowGeometryShader() ) );
        SetPixelShader( CompileShader( ps_4_0, ShadowPixelShader() ) );
        

        //SetBlendState( DisableFrameBuffer, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
       // SetDepthStencilState( TwoSidedStencil, 1 );
      //  SetRasterizerState( DisableCulling );
    }  

   // pass p1
   // {
		//SetBlendState( AdditiveBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
		//SetDepthStencilState( RenderNonShadows, 0 );
		//SetRasterizerState( EnableCulling );
	//}
}