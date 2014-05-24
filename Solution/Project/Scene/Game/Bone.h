//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  (c) 2011 Bryce Booth
//
//  File Name   :   Bone.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __Bone_H__
#define __Bone_H__


// Library Includes


// Local Includes


// Types


// Prototypes


class CBone
{

	// Member Functions
public:


	 CBone();
	~CBone();


	bool Initialise();


	// Inline Functions


protected:


private:


	void Deinitialise();


	CBone(const CBone& _krBone);
	CBone& operator = (const CBone& _krBone);


	// Member Variables
protected:


private:


};


#endif //__Bone_H__