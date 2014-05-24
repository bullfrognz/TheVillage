

#define MAX_TEXTURES 8


Texture2D g_TextureResources[MAX_TEXTURES];


cbuffer cbTextureBuffer
{
	int g_iTextureTypes[MAX_TEXTURES];
	int g_iTextureCount;
};


SamplerState linearSampler
{
	Filter = ANISOTROPIC;
	AddressU = Wrap;
	AddressV = Wrap;
	MaxAnisotropy = 4;
};