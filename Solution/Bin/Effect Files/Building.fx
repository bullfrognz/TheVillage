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
#include "LightHelper.fx"
#include "TextureHelper.fx"
#include "ShadowHelper.fx"


// Globals
struct VS_INPUT
{
	float3 vPosition	: POSITION;
	float3 vNormal		: NORMAL;
	float2 vTextureUV	: TEXCOORD_ONE;
};


struct GS_INPUT
{
	float4 vPosition		: SV_POSITION;
	float4 vWorldPosition	: POSITION;
	float3 vWorldNormal		: NORMAL;
	float2 vTextureUV		: TEXCOORD;
};


// [Implementation]


GS_INPUT ProcessVertexShader(VS_INPUT _tInput)
{
	GS_INPUT tOutput;


	// Convert vertex to projection space
	tOutput.vPosition = mul(float4(_tInput.vPosition, 1.0f), g_xWorldViewProjection);


	// Transform to world space space.
	tOutput.vWorldPosition = mul(_tInput.vPosition, g_xWorld);
	tOutput.vWorldNormal = normalize(mul(_tInput.vNormal, (float3x3)g_xWorld));


	tOutput.vTextureUV = _tInput.vTextureUV;


	return (tOutput);
}





float4 ProcessPixelShader(GS_INPUT _tInput) : SV_Target
{
	TSurfaceInfo tSurfaceInfo = {_tInput.vWorldPosition, _tInput.vWorldNormal, float4(1.0f, 1.0f, 1.0f, 1.0f), float4(1.0f, 1.0f, 1.0f, 1.0f), float4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f};


	float3 vLitColour = (0.0f, 0.0f, 0.0f);
	for (int i = 0; i < g_iNumLights; ++ i)
	{
		// Parallel
		if(g_tLight[i].iType == 1) 
		{
			vLitColour += ParallelLight(tSurfaceInfo, g_tLight[i], g_xWorld);
		}


		// Point
		else if(g_tLight[i].iType == 2) 
		{
			vLitColour += PointLight(tSurfaceInfo, g_tLight[i], g_xWorld);
		}


		// Spot
		else if(g_tLight[i].iType == 3) 
		{
			vLitColour += Spotlight(tSurfaceInfo, g_tLight[i], g_xWorld);
		}
	}



	float4 vFinalColour = float4(saturate(vLitColour), 1.0f);


	if (g_iTextureCount > 0)
	{
		float4 vTexelColour1 = g_TextureResources[0].Sample(linearSampler, _tInput.vTextureUV);


		vFinalColour *= vTexelColour1;
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




/*----------------------------------------------------------------------
*
*	Used for segments using the INDEX_ONE group.
*
*----------------------------------------------------------------------*/

technique10 DefaultTechnique
{
    pass P0
    {
		//SetBlendState(AlphaEnabled, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);


        SetVertexShader(CompileShader(vs_4_0, ProcessVertexShader()));
		SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, ProcessPixelShader()));
    }
}













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
	float4 vPositionW = mul(float4(_tInput.vPosition, 1.0f), g_xWorld);
	tOutput.vPositionW = vPositionW.xyz;


	// Transform to world space space.
	tOutput.vNormalW = mul(_tInput.vNormal, (float3x3)g_xWorld);


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
	float3 v3LightPosition = g_tLight[0].vPosition;


	// Compute un-normalized triangle normal
    float3 N = cross(_tVertices[2].vPositionW - _tVertices[0].vPositionW, _tVertices[4].vPositionW - _tVertices[0].vPositionW);
    

    // Compute direction from this triangle to the light
    float3 lightDir = v3LightPosition - _tVertices[0].vPositionW;
    

    //if we're facing the light
    if(dot(N, lightDir) > 0.0f)
    {
        // For each edge of the triangle, determine if it is a silhouette edge
        DetectAndProcessSilhouette(lightDir, _tVertices[0], _tVertices[2], _tVertices[1], _ShadowTriangleStream, v3LightPosition);
        DetectAndProcessSilhouette(lightDir, _tVertices[2], _tVertices[4], _tVertices[3], _ShadowTriangleStream, v3LightPosition);
        DetectAndProcessSilhouette(lightDir, _tVertices[4], _tVertices[0], _tVertices[5], _ShadowTriangleStream, v3LightPosition);
        

        //near cap
        PS_SHADOW_INPUT tOut;
        for(int v = 0; v < 6; v += 2)
        {
            float3 extrude = normalize(_tVertices[v].vPositionW - v3LightPosition);
            
            float3 pos = _tVertices[v].vPositionW + g_fExtrudeBias * extrude;
			tOut.vPosition = mul(float4(pos, 1.0f), g_xView);
			tOut.vPosition = mul(tOut.vPosition, g_xProjection);


            _ShadowTriangleStream.Append(tOut);
        }
		

        _ShadowTriangleStream.RestartStrip();
        

        //far cap (reverse the order)
        for(int v = 4; v >= 0; v -= 2)
        {
            float3 extrude = normalize(_tVertices[v].vPositionW - v3LightPosition);
        

            float3 pos = _tVertices[v].vPositionW + g_fExtrudeAmt * extrude;
			tOut.vPosition = mul(float4(pos, 1.0f), g_xView);
			tOut.vPosition = mul(tOut.vPosition, g_xProjection);


            _ShadowTriangleStream.Append(tOut);
        }


        _ShadowTriangleStream.RestartStrip();
    }
}




float4
ShadowPixelShader(PS_SHADOW_INPUT input) : SV_Target
{   
    return (float4(0.1f, 0.1f, 0.1f, 1.0f));
}





technique10 RenderShadow
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_4_0, ShadowVertexShader() ) );
        SetGeometryShader( CompileShader( gs_4_0, ShadowGeometryShader() ) );
        SetPixelShader( CompileShader( ps_4_0, ShadowPixelShader() ) );
        

       // SetBlendState( DisableFrameBuffer, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
       // SetDepthStencilState( TwoSidedStencil, 0 );
      //  SetRasterizerState( DisableCulling );
    }  

   // pass p1
   // {
		//SetBlendState( AdditiveBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
		//SetDepthStencilState( RenderNonShadows, 0 );
		//SetRasterizerState( EnableCulling );
	//}
}