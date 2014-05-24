//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name   :   StrUtilities.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __StrUtilities_H__
#define __StrUtilities_H__


// Library Includes
#include <string>
#include <sstream>
#include <Windows.h>


// Local Includes
#include "Defines\DataTypes.h"


// Types


// Prototypes


namespace StrUtilities
{
	std::string DirectoryPath(const std::string& _krFile);


	std::string ConvertToString(int _iValue);
	std::string ConvertToString(uint _uiValue);


	std::string& ConvertToString(const std::wstring& _kwrInput, std::string& _rOutput);
	std::wstring& ConvertToWString(const std::string& _krInput, std::wstring& _rwOutput);


	char* ConvertToString(const wchar_t* _kwcpInput, char*& _cprOutput);
	wchar_t* ConvertToWString(const char* _kcpInput, wchar_t*& _wcprOutput);


	void ConvertToInt(const std::string& _krString, int& _irReturnValue);
	void ConvertToFloat(const std::string& _krString, float& _frReturnValue);


	std::string& Trim(std::string& _rString);
	std::string& ToLower(std::string& _rString);


	char* Copy(const char* _kcpInput, char*& _prTarget);
};


#endif //__StrUtilities_H__