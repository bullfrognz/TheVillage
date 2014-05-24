//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   Camera.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation



void
CCamera::GetView(CViewMatrix& _xrView)
{
	if (m_bViewDirty)
	{
		RegenerateView();
	}


	_xrView = m_xView;
}


const CViewMatrix&
CCamera::GetView()
{
	if (m_bViewDirty)
	{
		RegenerateView();
	}


	return (m_xView);
}


const CProjMatrix&
CCamera::GetProjection() const
{
	return (m_xProjection);
}


void
CCamera::GetProjection(CProjMatrix& _rProjection) const
{
	_rProjection = m_xProjection;
}