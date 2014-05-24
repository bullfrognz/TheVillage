//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   Light.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


void
CLight::SetType(ELightType _eType)
{
	m_eType = _eType;
}


void
CLight::SetPosition(float _fX, float _fY, float _fZ)
{
	m_vPosition.Set(_fX, _fY, _fZ);
}


void
CLight::SetDirection(float _fX, float _fY, float _fZ)
{
	m_vDirection.Set(_fX, _fY, _fZ);
}


void
CLight::SetDiffue(float _fRed, float _fGreen, float _fBlue, float _fAlpha)
{
	m_vDiffuse.Set(_fRed, _fGreen, _fBlue, _fAlpha);
}


void
CLight::SetAmbient(float _fRed, float _fGreen, float _fBlue, float _fAlpha)
{
	m_vAmbient.Set(_fRed, _fGreen, _fBlue, _fAlpha);
}


void
CLight::SetSpecular(float _fRed, float _fGreen, float _fBlue, float _fAlpha)
{
	m_vSpecular.Set(_fRed, _fGreen, _fBlue, _fAlpha);
}


void
CLight::SetAttenuation(float _f0, float _f1, float _f2)
{
	m_fAttenuation0 = _f0;
	m_fAttenuation1 = _f1;
	m_fAttenuation2 = _f2;
}


void
CLight::SetAttenuation0(float _fValue)
{
	m_fAttenuation0 = _fValue;
}


void
CLight::SetAttenuation1(float _fValue)
{
	m_fAttenuation1 = _fValue;
}


void
CLight::SetAttenuation2(float _fValue)
{
	m_fAttenuation2 = _fValue;
}


void
CLight::SetRange(float _fValue)
{
	m_fRange = _fValue;
}


void
CLight::SetTheta(float _fValue)
{
	m_fTheta = _fValue;
}


void
CLight::SetPhi(float _fValue)
{
	m_fPhi = _fValue;
}


void 
CLight::SetFalloff(float _fValue)
{
	m_fFalloff = _fValue;
}


void
CLight::SetPosition(const CVector3& _kvrPosition)
{
	m_vPosition = _kvrPosition;
}


void
CLight::SetDirection(const CVector3& _kvrDirection)
{
	m_vDirection = _kvrDirection;
}


void
CLight::SetDiffue(const CColour& _kvrDiffuse)
{
	m_vDiffuse = _kvrDiffuse;
}


void
CLight::SetAmbient(const CColour& _kvrAmbient)
{
	m_vAmbient = _kvrAmbient;
}


void
CLight::SetSpecular(const CColour& _kvrSpecular)
{
	m_vSpecular = _kvrSpecular;
}