//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   Math.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Defines\Math.h"


// This Include
#include "MathUtilities.h"


// Implementation


namespace MathUtilities
{
	float DegreesToRadians(float _fDegrees)
	{
		float fRadians = _fDegrees;
		fRadians *= (Math::kfPi / 180.0f);


		return (fRadians);
	}


	float RadiansToDegrees(float _fRadians)
	{
		float fDegrees = _fRadians;
		fDegrees *= (180.0f / Math::kfPi);


		return (fDegrees);
	}
}

