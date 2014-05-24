//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name   :   TransformationHelper.fx
//  Description :   ----------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Globals


// Types


// [Implementation]


cbuffer cbPerObject
{
	float4x4 g_xWorld;
	float4x4 g_xView;
	float4x4 g_xProjection;
	float4x4 g_xWorldViewProjection;
}