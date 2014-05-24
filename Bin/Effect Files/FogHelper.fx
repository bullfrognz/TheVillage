//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name   :  FogHelper.fx
//  Description :   ----------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Globals


// Types


// [Implementation]


#define g_fNaturalLogBase 2.71828f



float g_fFogStartDistance	= 1200.0f;
float g_fFogDensity			= 0.006f;
float4 g_vFogColour			= float4(0.86f, 0.91f, 0.93f, 1.0f);



float3
ComputeVertexFog(float3 _vPixelColour,
				 float _fVertexDistance)
{
	float3 vOutputColour = _vPixelColour;


	if (_fVertexDistance > g_fFogStartDistance)
	{
		float fPixelFog = (1.0f / pow(g_fNaturalLogBase,  (_fVertexDistance - g_fFogStartDistance) * g_fFogDensity));


		vOutputColour  = fPixelFog * vOutputColour;
		vOutputColour += (1.0f - fPixelFog) * g_vFogColour;	// Add colour
	}


	return (vOutputColour);
}