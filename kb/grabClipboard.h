#pragma once
#include "includes.h"

inline bool grabClipboard(std::string &str)
{

	if (!OpenClipboard(nullptr)) //error opening clipboard
		return false;
	if (!IsClipboardFormatAvailable(CF_TEXT)) //not text contents
		return false;

	HANDLE data = GetClipboardData(CF_TEXT);

	if (data == nullptr) //error with data
	{
		CloseClipboard();
		return false;
	}

	char* retrievedText = static_cast<char*>(GlobalLock(data));

	if (retrievedText == nullptr) //error with text
	{
		CloseClipboard();
		GlobalUnlock(data);
		return false;
	}

	GlobalUnlock(data);
	CloseClipboard();

	if (str == std::string(retrievedText)) //text we already have, no need to return true to print.
		return false;

	str = std::string(retrievedText);
	return true;
}