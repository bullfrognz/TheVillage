//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   Entity.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation
void
CEntity::SetPositionX(float _fX)
{
	m_vPosition.SetX(_fX);
	SetWorldDirty(true);
}


void
CEntity::SetPositionY(float _fY)
{
	m_vPosition.SetY(_fY);
	SetWorldDirty(true);
}


void
CEntity::SetPositionZ(float _fZ)
{
	m_vPosition.SetZ(_fZ);
	SetWorldDirty(true);
}


void
CEntity::SetPosition(const CVector3& _krPosition)
{
	m_vPosition = _krPosition;
	SetWorldDirty(true);
}


void
CEntity::TranslateX(float _fX)
{
	m_vPosition.AddX(_fX);
	SetWorldDirty(true);
}


void
CEntity::TranslateY(float _fY)
{
	m_vPosition.AddY(_fY);
	SetWorldDirty(true);
}


void
CEntity::TranslateZ(float _fZ)
{
	m_vPosition.AddZ(_fZ);
	SetWorldDirty(true);
}


void
CEntity::Translate(const CVector3& _krTranslation)
{
	m_vPosition += _krTranslation;
	SetWorldDirty(true);
}


void
CEntity::SetRotationX(float _fX)
{
	m_vRotation.SetX(_fX);
	SetWorldDirty(true);
}


void
CEntity::SetRotationY(float _fY)
{
	m_vRotation.SetY(_fY);
	SetWorldDirty(true);
}


void
CEntity::SetRotationZ(float _fZ)
{
	m_vRotation.SetZ(_fZ);
	SetWorldDirty(true);
}


void
CEntity::SetRotation(const CVector3& _krRotation)
{
	m_vRotation = _krRotation;
	SetWorldDirty(true);
}


void
CEntity::AddRotationX(float _fX)
{
	m_vRotation.AddX(_fX);
	SetWorldDirty(true);
}


void
CEntity::AddRotationY(float _fY)
{
	m_vRotation.AddY(_fY);
	SetWorldDirty(true);
}


void
CEntity::AddRotationZ(float _fZ)
{
	m_vRotation.AddZ(_fZ);
	SetWorldDirty(true);
}


void
CEntity::AddRotation(const CVector3& _krRotation)
{
	m_vRotation += _krRotation;
	SetWorldDirty(true);
}


void
CEntity::SetScaleX(float _fX)
{
	m_vScale.SetX(_fX);
	SetWorldDirty(true);
}


void
CEntity::SetScaleY(float _fY)
{
	m_vScale.SetY(_fY);
	SetWorldDirty(true);
}


void
CEntity::SetScaleZ(float _fZ)
{
	m_vScale.SetZ(_fZ);
	SetWorldDirty(true);
}


void
CEntity::SetScale(float _fX, float _fY, float _fZ)
{
	m_vScale.Set(_fX, _fY, _fZ);
	SetWorldDirty(true);
}


const CVector3&
CEntity::GetPosition() const
{
	return (m_vPosition);
}


const CVector3&
CEntity::GetRotation() const
{
	return (m_vRotation);
}


const CVector3&
CEntity::GetScale() const
{
	return (m_vScale);
}


void
CEntity::GetPosition(CVector3& _rPosition) const
{
	_rPosition = m_vPosition;
}


void
CEntity::GetRotation(CVector3& _rRotation) const
{
	_rRotation = m_vRotation;
}


void
CEntity::GetScale(CVector3& _rScale) const
{
	_rScale = m_vScale;
}


void
CEntity::GetWorld(CWorldMatrix& _xrWorld)
{
	if (m_bWorldDirty)
	{
		RegenerateWorld();
	}


	_xrWorld = m_xWorld;
}


const CWorldMatrix& 
CEntity::GetWorld()
{
	if (m_bWorldDirty)
	{
		RegenerateWorld();
	}


	return (m_xWorld);
}


void
CEntity::SetWorldDirty(bool _bDirty)
{
	m_bWorldDirty = _bDirty;
}