#include "handleChars.h"

std::string handleChars(int vkCode, bool shift)
{
	switch (vkCode)
	{
#if 0
		//handling numbers here:
		{
			if (shift)
			{
	case 49:
		return "!";
		break;
	case 50:
		return "@";
		break;
	case 51:
		return "#";
		break;
	case 52:
		return "$";
		break;
	case 53:
		return "%";
		break;
	case 54:
		return "^";
		break;
	case 55:
		return "&";
		break;
	case 56:
		return "*";
		break;
	case 57:
		return "(";
		break;
	case 58:
		return ")";
		break;
			}
		}
#endif
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
	case 188:
		return (!shift ? "," : "<");
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