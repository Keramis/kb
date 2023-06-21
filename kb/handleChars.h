#pragma once
#include "includes.h"

std::string handleChars(int vkCode, bool shift);

bool handleShift();
bool handleCTRL();

inline bool isCapsEnabled()
{
	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
		return 1;
	else
		return 0;
}