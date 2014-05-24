//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//
//  File Name :   Model.inl
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


uint
CModel::GetNumSubsets() const
{
	return (m_aSubsets.size());
}


const CModel::TSubset&
CModel::GetSubset(uint _uiId) const
{
	return (m_aSubsets[_uiId]);
}


uint
CModel::GetNumMaterials() const
{
	return (m_aMaterials.size());
}


CModel::TMaterial&
CModel::GetMaterial(uint _uiId)
{
	return (m_aMaterials[_uiId]);
}