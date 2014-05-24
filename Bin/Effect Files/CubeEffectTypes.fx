
struct TLight
{
	float3 vPosition;
	float4 vDirection;
	float4 vDiffuse;
	float4 vAmbient;
	float4 vSpecular;
	float  fAttenuation0;
	float  fAttenuation1;
	float  fAttenuation2;
	float  fRange;
	float  fTheta;
	float  fPhi;
	float  fFalloff;
	int    iType;
};



struct TSurfaceInfo
{
	float3 vPosition;
    float3 vNormal;
    float4 vDiffuse;
    float4 vSpecular;
};




float3 ParallelLight(TSurfaceInfo _tSurfaceInfo, TLight _tLight, float3 _vCameraPosition)
{
	float3 vLitColor = float3(0.0f, 0.0f, 0.0f);


	// The light vector aims opposite the direction the light rays travel.
	float3 vLightVector = -(_tLight.vDirection);
	

	// Add the ambient term.
	vLitColor += _tSurfaceInfo.vDiffuse * _tLight.vAmbient;
	

	// Add diffuse and specular term, provided the surface is in 
	// the line of site of the light.
	float fDiffuseFactor = dot(vLightVector, _tSurfaceInfo.vNormal);


	[branch]
	if(fDiffuseFactor > 0.0f)
	{
		float fSpecularPower	= max(_tSurfaceInfo.vSpecular.a, 1.0f);
		float3 vToEye			= normalize(_vCameraPosition - _tSurfaceInfo.vPosition);
		float3 vReflection		= reflect(-vLightVector, _tSurfaceInfo.vNormal);
		float fSpecularFactor	= pow(max(dot(vReflection, vToEye), 0.0f), fSpecularPower);
					
		// diffuse and specular terms
		vLitColor += fDiffuseFactor * _tSurfaceInfo.vDiffuse * _tLight.vDiffuse;
		vLitColor += fSpecularFactor * _tSurfaceInfo.vSpecular * _tLight.vSpecular;
	}

	
	return (vLitColor);
}




/*
float3 PointLight(TSurfaceInfo v, TLight _tLight, float3 _vCameraPosition)
{
	float3 litColor = float3(0.0f, 0.0f, 0.0f);
	
	// The vector from the surface to the light.
	float3 lightVec = L.pos - v.pos;
		
	// The distance from surface to light.
	float d = length(lightVec);
	
	if( d > L.range )
		return float3(0.0f, 0.0f, 0.0f);
		
	// Normalize the light vector.
	lightVec /= d; 
	
	// Add the ambient light term.
	litColor += v.diffuse * L.ambient;	
	
	// Add diffuse and specular term, provided the surface is in 
	// the line of site of the light.
	
	float diffuseFactor = dot(lightVec, v.normal);
	[branch]
	if( diffuseFactor > 0.0f )
	{
		float specPower  = max(v.spec.a, 1.0f);
		float3 toEye     = normalize(eyePos - v.pos);
		float3 R         = reflect(-lightVec, v.normal);
		float specFactor = pow(max(dot(R, toEye), 0.0f), specPower);
	
		// diffuse and specular terms
		litColor += diffuseFactor * v.diffuse * L.diffuse;
		litColor += specFactor * v.spec * L.spec;
	}
	
	// attenuate
	return litColor / dot(L.att, float3(1.0f, d, d*d));
}





float3 Spotlight(TSurfaceInfo v, TLight _tLight, float3 eyePos)
{
	float3 litColor = PointLight(v, L, eyePos);
	
	// The vector from the surface to the light.
	float3 lightVec = normalize(L.pos - v.pos);
	
	float s = pow(max(dot(-lightVec, L.dir), 0.0f), L.spotPower);
	
	// Scale color by spotlight factor.
	return litColor*s;
}





float3 CalculateAmbient(float3 MatirialColour, float3 _LightColour)
{
	float3 vAmbient = MatirialColour * _LightColour;


	return vAmbient;
}






float3 CalculateDiffuse(float3 _vBaseColour, float3 _vLightColour, float3 _vVertexNormal, float3 _vLightDirection)
{
	float3 vDiffuse;
	vDiffuse  = _vBaseColour;
	vDiffuse *= _vLightColour;
	vDiffuse *= saturate(dot(_vVertexNormal, _vLightDirection));


	return (vDiffuse);
}





float CalculateSpecular(float3 _vCameraDirection, float3 _vLightDirection, float3 _vVertexNormal)
{
	float3 vReflect = reflect(_vLightDirection, _vVertexNormal);


	float fSpecular = 0.0f;
	fSpecular = dot(vReflect, _vCameraDirection);
	fSpecular = saturate(fSpecular);
	fSpecular = pow(fSpecular, 2.0f);


	return (fSpecular);
}
*/