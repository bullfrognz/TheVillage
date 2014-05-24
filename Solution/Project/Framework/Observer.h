//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Observer.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Observer_H__
#define __Observer_H__


// Library Includes


// Local Includes
#include "Defines\DataTypes.h"


// Types


// Constants


// Prototypes


class IObserver
{

	// Member Functions
public:


			 IObserver() {};
	virtual ~IObserver() {};


	virtual void NotifyMessage(uint _uiSubject, void* _pDispatcher) = 0;


	// Inline Functions


protected:


private:


	// Member Variables
protected:


private:


};


#endif //__Observer_H__