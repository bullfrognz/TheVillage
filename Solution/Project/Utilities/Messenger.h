//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Messenger.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Messenger_H__
#define __Messenger_H__


// Library Includes


// Local Includes
#include "Defines\DataTypes.h"


// Types
class IObserver;


namespace Messenger
{
	bool RegisterObserver(uint _uiSubjectId, IObserver* _pObserver);


	bool UnregisterObserver(uint _uiSubjectId, IObserver* _pObserver);


	bool Send(uint _uiSubjectId, void* _pData);


	const uint kuiMinSubjectId = 0;
	const uint kuiMaxSubjectId = 50000;
};


#endif //__Messenger_H__