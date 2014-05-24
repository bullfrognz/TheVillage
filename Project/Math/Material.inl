//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   Material.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


void
CMaterial::SetDiffuseR(float _fR)
{
	m_Diffuse.SetRed(_fR);
}


void
CMaterial::SetDiffuseG(float _fG)
{
	m_Diffuse.SetGreen(_fG);
}


void
CMaterial::SetDiffuseB(float _fB)
{
	m_Diffuse.SetBlue(_fB);
}


void
CMaterial::SetDiffuseA(float _fA)
{
	m_Diffuse.SetOpacity(_fA);
}


void
CMaterial::SetDiffuse(float _fR, float _fG, float _fB, float _fA)
{
	m_Diffuse.Set(_fR, _fG, _fB, _fA);
}


void
CMaterial::SetAmbientR(float _fR)
{
	m_Ambient.SetRed(_fR);
}


void
CMaterial::SetAmbientG(float _fG)
{
	m_Ambient.SetGreen(_fG);
}


void
CMaterial::SetAmbientB(float _fB)
{
	m_Ambient.SetBlue(_fB);
}


void
CMaterial::SetAmbientA(float _fA)
{
	m_Ambient.SetOpacity(_fA);
}


void
CMaterial::SetAmbient(float _fR, float _fG, float _fB, float _fA)
{
	m_Ambient.Set(_fR, _fG, _fB, _fA);
}


void
CMaterial::SetSpecularR(float _fR)
{
	m_Specular.SetRed(_fR);
}


void
CMaterial::SetSpecularG(float _fG)
{
	m_Specular.SetGreen(_fG);
}


void
CMaterial::SetSpecularB(float _fB)
{
	m_Specular.SetBlue(_fB);
}


void
CMaterial::SetSpecularA(float _fA)
{
	m_Specular.SetOpacity(_fA);
}


void
CMaterial::SetSpecular(float _fR, float _fG, float _fB, float _fA)
{
	m_Specular.Set(_fR, _fG, _fB, _fA);
}


void
CMaterial::SetEmissiveR(float _fR)
{
	m_Emissive.SetRed(_fR);
}


void
CMaterial::SetEmissiveG(float _fG)
{
	m_Emissive.SetGreen(_fG);
}


void
CMaterial::SetEmissiveB(float _fB)
{
	m_Emissive.SetBlue(_fB);
}


void
CMaterial::SetEmissiveA(float _fA)
{
	m_Emissive.SetOpacity(_fA);
}


void
CMaterial::SetEmissive(float _fR, float _fG, float _fB, float _fA)
{
	m_Emissive.Set(_fR, _fG, _fB, _fA);
}


void
CMaterial::SetSpecularPower(float _fPower)
{
	m_fSpecularPower = _fPower;
}


const CColour&
CMaterial::GetDiffuse() const
{
	return (m_Diffuse);
}


const CColour&
CMaterial::GetAmbient() const
{
	return (m_Ambient);
}


const CColour&
CMaterial::GetSpecular() const
{
	return (m_Specular);
}


const CColour&
CMaterial::GetEmissive() const
{
	return (m_Emissive);
}


float
CMaterial::GetSpecularPower() const
{
	return (m_fSpecularPower);
}

