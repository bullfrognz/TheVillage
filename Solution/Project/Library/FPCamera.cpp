//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   FPCamera.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Defines Includes
#include "Defines\Macros.h"


// Local Includes
#include "Utilities\Messenger.h"
#include "Math\WorldMatrix.h"
#include "Math\ViewMatrix.h"
#include "Framework\Mouse.h"
#include "Framework\Keyboard.h"


#include "Framework\Windows\WinMouse.h"


// This Include
#include "FPCamera.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CFPCamera constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CFPCamera::CFPCamera()
: m_fMovementVelocity(100.0f)
, m_fMouseTranslationX(0)
, m_fMouseTranslationY(0)
, m_fSensitivity(0.004f)
, m_bMoveForward(false)
, m_bMoveBack(false)
, m_bMoveLeft(false)
, m_bMoveRight(false)
, m_bMoveUp(false)
, m_bMoveDown(false)
{
	//Empty
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CFPCamera deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CFPCamera::~CFPCamera()
{
	Deinitialise();
}





bool
CFPCamera::Initialise(uint _uiWidth, uint _uiHeight)
{
	FW_VALIDATE(InitialiseObserver());


	CCamera::Initialise(_uiWidth, _uiHeight);


	Messenger::Send(CURSOR_HIDE, 0);


	return (true);
}





bool
CFPCamera::Process(float _fDeltaTick)
{
	// Update rotation
	ProcessMouse(_fDeltaTick);


	// Update position
	ProcessMovement(_fDeltaTick);


	// Send center message
	Messenger::Send(CURSOR_CENTER, 0);


	return (true);
}





/********************************
            Protected
*********************************/





bool
CFPCamera::ProcessMouse(float _fDeltaTick)
{
	//Check position has changed
	if (m_fMouseTranslationX || m_fMouseTranslationY)
	{
		CEntity::AddRotationY(m_fMouseTranslationX * m_fSensitivity);
		CEntity::AddRotationX(m_fMouseTranslationY * m_fSensitivity);
	}

	
	m_fMouseTranslationX = 0;
	m_fMouseTranslationY = 0;


	LimitRotation();


	return (true);
}





bool
CFPCamera::ProcessMovement(float _fDeltaTick)
{
	const CWorldMatrix& kxrWorld = CEntity::GetWorld();


	CVector3 vOrientationX = kxrWorld.GetOrientationX();
	CVector3 vOrientationY = kxrWorld.GetOrientationY();
	CVector3 vOrientationZ = kxrWorld.GetOrientationZ();


	CVector3 vTranslationX;
	CVector3 vTranslationY;
	CVector3 vTranslationZ;


	// Forward - Back
	if (m_bMoveForward && !m_bMoveBack)
	{
		vTranslationZ = vOrientationZ * m_fMovementVelocity;
	}
	else if (!m_bMoveForward && m_bMoveBack)
	{
		vTranslationZ = vOrientationZ * -m_fMovementVelocity;
	}


	// Left - Right
	if (m_bMoveLeft && !m_bMoveRight)
	{
		vTranslationX = vOrientationX * -m_fMovementVelocity;
	}
	else if (!m_bMoveLeft && m_bMoveRight)
	{
		vTranslationX = vOrientationX * m_fMovementVelocity;
	}


	// Up - Down
	if (m_bMoveUp && !m_bMoveDown)
	{
		vTranslationY = CVector3(0.0f, 1.0f, 0.0f) * m_fMovementVelocity;
	}
	else if (!m_bMoveUp && m_bMoveDown)
	{
		vTranslationY = CVector3(0.0f, 1.0f, 0.0f) * -m_fMovementVelocity;
	}


	if (!vTranslationX.IsZero() ||
		!vTranslationY.IsZero() ||
		!vTranslationZ.IsZero())
	{
		CEntity::Translate( vTranslationX * _fDeltaTick );
		CEntity::Translate( vTranslationY * _fDeltaTick );
		CEntity::Translate( vTranslationZ * _fDeltaTick );
	}


	return (true);
}





void
CFPCamera::LimitRotation()
{
	if (CEntity::GetRotation().GetX() > 1.221f)
	{
		CEntity::SetRotationX(1.221f);
	}
	else if (CEntity::GetRotation().GetX() < -1.221)
	{
		CEntity::SetRotationX(-1.221f);
	}
}





/********************************
            Private
*********************************/




bool
CFPCamera::InitialiseObserver()
{
	FW_VALIDATE(Messenger::RegisterObserver(KEY_UP_W, this));
	FW_VALIDATE(Messenger::RegisterObserver(KEY_UP_S, this));
	FW_VALIDATE(Messenger::RegisterObserver(KEY_UP_A, this));
	FW_VALIDATE(Messenger::RegisterObserver(KEY_UP_D, this));
	FW_VALIDATE(Messenger::RegisterObserver(KEY_UP_SPACE, this));
	FW_VALIDATE(Messenger::RegisterObserver(KEY_UP_CONTROL, this));
	FW_VALIDATE(Messenger::RegisterObserver(KEY_DWN_W, this));
	FW_VALIDATE(Messenger::RegisterObserver(KEY_DWN_S, this));
	FW_VALIDATE(Messenger::RegisterObserver(KEY_DWN_A, this));
	FW_VALIDATE(Messenger::RegisterObserver(KEY_DWN_D, this));
	FW_VALIDATE(Messenger::RegisterObserver(KEY_DWN_SPACE, this));
	FW_VALIDATE(Messenger::RegisterObserver(KEY_DWN_CONTROL, this));


	FW_VALIDATE(Messenger::RegisterObserver(MOUSE_RAWINPUT, this));


	return (true);
}




void
CFPCamera::NotifyMessage(uint _uiSubject, void* _pDispatcher)
{
	switch (_uiSubject)
	{
	case MOUSE_RAWINPUT:
		{
			CWinMouse* pMouse = static_cast<CWinMouse*>(_pDispatcher);
			m_fMouseTranslationX = static_cast<float>(pMouse->GetTranslationX());
			m_fMouseTranslationY = static_cast<float>(pMouse->GetTranslationY());
		}
		break;

	case KEY_UP_W:
		m_bMoveForward = false;
		break;

	case KEY_UP_S:
		m_bMoveBack = false;
		break;

	case KEY_UP_A:
		m_bMoveLeft = false;
		break;

	case KEY_UP_D:
		m_bMoveRight = false;
		break;

	case KEY_UP_SPACE:
		m_bMoveUp = false;
		break;

	case KEY_UP_CONTROL:
		m_bMoveDown = false;
		break;

	case KEY_DWN_W:
		m_bMoveForward = true;
		break;

	case KEY_DWN_S:
		m_bMoveBack = true;
		break;

	case KEY_DWN_A:
		m_bMoveLeft = true;
		break;

	case KEY_DWN_D:
		m_bMoveRight = true;
		break;

	case KEY_DWN_SPACE:
		m_bMoveUp = true;
		break;

	case KEY_DWN_CONTROL:
		m_bMoveDown = true;
		break;
	}
}





void
CFPCamera::Deinitialise()
{
	DeinitialiseObserver();
}





bool
CFPCamera::DeinitialiseObserver()
{
	FW_VALIDATE(Messenger::UnregisterObserver(KEY_UP_W, this));
	FW_VALIDATE(Messenger::UnregisterObserver(KEY_UP_S, this));
	FW_VALIDATE(Messenger::UnregisterObserver(KEY_UP_A, this));
	FW_VALIDATE(Messenger::UnregisterObserver(KEY_UP_D, this));
	FW_VALIDATE(Messenger::UnregisterObserver(KEY_UP_SPACE, this));
	FW_VALIDATE(Messenger::UnregisterObserver(KEY_UP_CONTROL, this));
	FW_VALIDATE(Messenger::UnregisterObserver(KEY_DWN_W, this));
	FW_VALIDATE(Messenger::UnregisterObserver(KEY_DWN_S, this));
	FW_VALIDATE(Messenger::UnregisterObserver(KEY_DWN_A, this));
	FW_VALIDATE(Messenger::UnregisterObserver(KEY_DWN_D, this));
	FW_VALIDATE(Messenger::UnregisterObserver(KEY_DWN_SPACE, this));
	FW_VALIDATE(Messenger::UnregisterObserver(KEY_DWN_CONTROL, this));


	return (true);
}