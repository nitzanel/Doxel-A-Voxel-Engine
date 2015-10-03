/*
This file contains a basic IOManager class.
*/
#pragma once

#include <vector>

class IOManager
{
public:
	/*
	read a file to a vector of unsigned chars
	*/
	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	/*
	read a file to a string.
	*/
	static bool readFileToBuffer(std::string filePath, std::string& buffer);
};

