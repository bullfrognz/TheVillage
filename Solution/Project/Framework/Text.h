//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   Text.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Text_H__
#define __Text_H__


// Library Includes


// Local Includes
#include "Defines\DataTypes.h"


// Types


// Constants


// Prototypes
class IRenderer;


class IText
{
	
	// Member Types
public:


	enum EQuality
	{
		INVALID_QUALITY = -1,

		QUALITY_LOW,
		QUALITY_HIGH,

		MAX_QUALITY
	};


	enum EFamilty
	{
		INVALID_FAMILY = -1,

		FAMILY_NEWTIMESROMAN,
		FAMILY_ARIAL,

		MAX_FAMILY
	};


	struct TDesc
	{
		TDesc()
		{
			memset(this, 0, sizeof(TDesc));
		}


		uint uiSize;
		uint uiWeight;
		EQuality eQuality;
		EFamilty eFamily;
		bool bItalic;
	};


	// Member Functions
public:


			 IText() {};
	virtual ~IText() {};


	virtual bool Draw() = 0;


	virtual void SetText(const char* _kcpText) = 0;


	// Inline Function
	virtual inline void SetSize(uint _uiSize) = 0;
	virtual inline void SetColour(float _fRed, float _fGreen, float _fBlue) = 0;
	virtual inline void SetTransparency(float _fLevel) = 0;
	virtual inline void SetPosition(int _iX, int _iY) = 0;
	virtual inline void SetPositionX(int _iX) = 0;
	virtual inline void SetPositionY(int _iY) = 0;


protected:


private:


	// Member Variables
protected:


private:


};


#endif //__Text_H__