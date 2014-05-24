//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name   :   MathUtilities.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __MathUtilities_H__
#define __MathUtilities_H__


// Library Includes


// Local Includes


// Implementation


namespace MathUtilities
{
	template <class TYPE>
	TYPE Max(TYPE _Value1, TYPE _Value2)
	{
		return (_Value1 > _Value2 ? _Value1 : _Value2);
	}


	template <class TYPE>
	TYPE Min(TYPE _Value1, TYPE _Value2)
	{
		return (_Value1 < _Value2 ? _Value1 : _Value2);
	}



	float DegreesToRadians(float _fDegrees);
	float RadiansToDegrees(float _fRadians);


	const float kfPi = 3.14159265359f;
}


#endif //__MathUtilities_H__