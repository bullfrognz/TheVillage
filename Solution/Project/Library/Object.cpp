//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name :   Object.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Framework\Renderer.h"
#include "Framework\Effect.h"
#include "Library\Model.h"
#include "Defines\Macros.h"


// This Include
#include "Object.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* Object constructors
*
*---------------------------------------------------------------------------------------------------------------------------*/

CObject::CObject()
: m_pModel(0)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Object deconstructor
*
*---------------------------------------------------------------------------------------------------------------------------*/

CObject::~CObject()
{
	Deinitialise();
}





bool
CObject::Initialise(IRenderer& _rRenderer, const char* _kcpModelFile, const std::vector<CModel::EInputType>& _karInputLayout)
{
	m_pModel = new CModel();
	FW_VALIDATE(m_pModel->Initialise(_rRenderer, _kcpModelFile, _karInputLayout));


	return (true);
}





bool
CObject::Draw(IRenderer& _rRenderer, IEffect& _rEffect)
{
	FW_VALIDATE(m_pModel->Draw(_rRenderer, _rEffect));


	return (true);
}





/********************************
            Protected
*********************************/






/********************************
            Private
*********************************/





void
CObject::Deinitialise()
{
	FW_DELETE(m_pModel);
}