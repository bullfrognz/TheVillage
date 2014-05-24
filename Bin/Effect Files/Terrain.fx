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
#include "FogHelper.fx"


// Globals
bool g_bFogEnabled = false;



// Types
struct VS_INPUT
{
	float3 vPosition		: POSITION;
	float3 vNormal			: NORMAL;
	float2 vTextureUV		: TEXCOORD;
	float fTex1Alpha		: TEXALPHA0;
	float fTex2Alpha		: TEXALPHA1;
	float fTex3Alpha		: TEXALPHA2;
	float fTex4Alpha		: TEXALPHA3;
};


struct GS_INPUT
{
	float4 vPosition		: SV_POSITION;
	float4 vWorldPosition	: POSITION;
	float3 vWorldNormal		: NORMAL;
	float2 vTextureUV		: TEXCOORD;
	float fTex1Alpha		: TEXALPHA0;
	float fTex2Alpha		: TEXALPHA1;
	float fTex3Alpha		: TEXALPHA2;
	float fTex4Alpha		: TEXALPHA3;
	float fVertexDistance	: DISTANCE;
};


// [Implementation]


GS_INPUT ProcessVertexShader(VS_INPUT _tInput)
{
	GS_INPUT tOutput;


	// Convert vertex to projection space
	tOutput.vPosition = mul(float4(_tInput.vPosition, 1.0f), g_xWorldViewProjection);


	// Transform to world space space.
	tOutput.vWorldPosition = mul(float4(_tInput.vPosition, 1.0f), g_xWorld);
	tOutput.vWorldNormal   = normalize( mul(_tInput.vNormal, (float3x3)g_xWorld) );


	tOutput.vTextureUV = _tInput.vTextureUV;
	tOutput.fTex1Alpha = _tInput.fTex1Alpha;
	tOutput.fTex2Alpha = _tInput.fTex2Alpha;
	tOutput.fTex3Alpha = _tInput.fTex3Alpha;
	tOutput.fTex4Alpha = _tInput.fTex4Alpha;


    // Calculate the camera position.
	tOutput.fVertexDistance = distance(tOutput.vPosition, float4(0.0f, 0.0f, 0.0f, 0.0f));


	return (tOutput);
}





float4 ProcessPixelShader(GS_INPUT _tInput) : SV_Target
{
	TSurfaceInfo tSurfaceInfo = {_tInput.vWorldPosition, _tInput.vWorldNormal, float4(1.0f, 1.0f, 1.0f, 1.0f), float4(0.0f, 0.0f, 0.0f, 1.0f), float4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f};


	float3 vLitColour = float3(0.0f, 0.0f, 0.0f);
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


	float3 vTexelColour1 = float3(0.0f, 0.0f, 0.0f);
	vTexelColour1  = g_TextureResources[0].Sample(linearSampler, _tInput.vTextureUV);
	vTexelColour1 *= _tInput.fTex1Alpha;


	float3 vTexelColour2 = float3(0.0f, 0.0f, 0.0f);
	vTexelColour2  = g_TextureResources[1].Sample(linearSampler, _tInput.vTextureUV);
	vTexelColour2 *= _tInput.fTex2Alpha;


	float3 vTexelColour3 = float3(0.0f, 0.0f, 0.0f);
	vTexelColour3  = g_TextureResources[2].Sample(linearSampler, _tInput.vTextureUV);
	vTexelColour3 *= _tInput.fTex3Alpha;


	float3 vTexelColour4 = float3(0.0f, 0.0f, 0.0f);
	vTexelColour4  = g_TextureResources[3].Sample(linearSampler, _tInput.vTextureUV);
	vTexelColour4 *= _tInput.fTex4Alpha;

	
	float3 vFinalColour = saturate(vLitColour * (vTexelColour1 + vTexelColour2 + vTexelColour3 + vTexelColour4)); // ; 


	if (g_bFogEnabled)
	{
		vFinalColour = ComputeVertexFog(vFinalColour, _tInput.fVertexDistance);
	}


    return (float4(vFinalColour, 1.0f));
}




// tristrip, linestrip, and pointlist
[maxvertexcount(3)]
void GS_INDEXGROUP_ONE(uint  _uiPrimitiveId : SV_PrimitiveID,
					   triangle  GS_INPUT _Vertices[3],
					   inout LineStream<GS_INPUT> _triStream )
{
	_triStream.Append(_Vertices[0]);
	_triStream.Append(_Vertices[1]);
	//_triStream.Append(_Vertices[2]);
}



/*----------------------------------------------------------------------
*
*	Used for segments using the INDEX_ONE group.
*
*----------------------------------------------------------------------*/

technique10 Technique1
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_4_0, ProcessVertexShader()));
		SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, ProcessPixelShader()));
    }
}


