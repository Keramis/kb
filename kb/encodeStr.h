#pragma once
#include "includes.h"

long encodeStr(std::string& str);
bool flushChars(std::vector<int>& vec, std::vector<int> filename, int& count, bool check = true, int vecsize = 1000);