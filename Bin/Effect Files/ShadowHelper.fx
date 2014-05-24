//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name   :   ShadowHelper.fx
//  Description :   ----------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Globals
#define LIGHT_FALLOFF 1.2f


// Types
struct GS_SHADOW_INPUT
{
    float3 vPositionW	: POSITION; 
    float3 vNormalW		: NORMAL;
};


struct PS_SHADOW_INPUT
{
	float4 vPosition	: SV_Position;
};


#define g_fExtrudeBias 0.1f
#define g_fExtrudeAmt 168.0f


/*---------------------------------------------------------------------------------------------------------------------------
*
*	 Helper to detect a silhouette edge and extrude a volume from it
*
*---------------------------------------------------------------------------------------------------------------------------*/

void DetectAndProcessSilhouette( float3 N,         // Un-normalized triangle normal
                                 GS_SHADOW_INPUT v1,    // Shared vertex
                                 GS_SHADOW_INPUT v2,    // Shared vertex
                                 GS_SHADOW_INPUT vAdj,  // Adjacent triangle vertex
                                 inout TriangleStream<PS_SHADOW_INPUT> _ShadowTriangleStream,
								 float3 _v3LightPosition)// triangle stream
{    
    //float3 NAdj = cross( v2.vPositionW - vAdj.vPositionW, v1.vPositionW - vAdj.vPositionW );


	float3 outpos[4];
    float3 extrude1 = normalize(v1.vPositionW - _v3LightPosition);
    float3 extrude2 = normalize(v2.vPositionW - _v3LightPosition);


    outpos[0] = v1.vPositionW + g_fExtrudeBias * extrude1;
    outpos[1] = v1.vPositionW + g_fExtrudeAmt  * extrude1;
    outpos[2] = v2.vPositionW + g_fExtrudeBias * extrude2;
    outpos[3] = v2.vPositionW + g_fExtrudeAmt  * extrude2;
        

    // Extrude silhouette to create two new triangles
    PS_SHADOW_INPUT tOutput;


    for(int v = 0; v < 4; ++ v)
    {
		tOutput.vPosition = mul(float4(outpos[v], 1.0f), g_xView);
		tOutput.vPosition = mul(tOutput.vPosition, g_xProjection);


        _ShadowTriangleStream.Append(tOutput);
    }


    _ShadowTriangleStream.RestartStrip();
}