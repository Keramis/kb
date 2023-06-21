#include "handleChars.h"

std::string nums[] {")", "!", "@", "#", "$", "%", "^", "&", "*", "("};

std::string handleNumbers(int vkcode, bool shift);

std::string handleChars(int vkCode, bool shift)
{
	switch (vkCode)
	{
		//handling numbers here:
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
		return handleNumbers(vkCode, shift);
		break;
	case 8:
		return "BACKSPACE";
		break;
	case 9:
		return "TAB";
		break;
	case 13:
		return "ENTER";
		break;
	case 27:
		return "ESC";
		break;
	case 32:
		return "SPACE";
		break;
	case 186:
		return (!shift ? ";" : ":");
		break;
	case 187:
		return (!shift ? "=" : "+");
		break;
	case 188:
		return (!shift ? "," : "<");
		break;
	case 189:
		return (!shift ? "-" : "_");
		break;
	case 190:
		return (!shift ? "." : ">");
		break;
	case 191:
		return (!shift ? "/" : "?");
		break;
	case 192:
		return (!shift ? "`" : "~");
		break;
	case 219:
		return (!shift ? "[" : "{");
		break;
	case 220:
		return (!shift ? "\\" : "|");
		break;
	case 221:
		return (!shift ? "]" : "}");
		break;
	case 222:
		return (!shift ? "\'" : "\"");
		break;
	default:
		char ch = (char)vkCode;
		if (!shift) {
			return std::string(1, tolower(ch)); //convert char to 1-length string :)
		}
		else {
			return std::string(1, ch);
		}
		break;
	}
}

std::string handleNumbers(int vkcode, bool shift)
{
	if (!shift)
		return std::string(1, (char)vkcode);
	else
		return nums[vkcode - 48]; //only works because numbers are sequential, and so is my array.
}

bool handleShift()
{
	if ((GetKeyState(160) & 0x8000) || (GetKeyState(161) & 0x8000))
		return true;
	else
		return false;
}

bool handleCTRL()
{
	if ((GetKeyState(162) & 0x8000) || (GetKeyState(163) & 0x8000))
		return true;
	else
		return false;
}