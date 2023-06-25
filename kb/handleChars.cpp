#include "handleChars.h"

std::string nums[] {")", "!", "@", "#", "$", "%", "^", "&", "*", "("};
char nums2[]{ ')', '!', '@', '#', '$', '%', '^', '&', '*', '('};

std::string handleNumbers(int vkcode, bool shift);
int handleNumbers2(int vkcode, bool shift);

//we're keeping this for legacy/debugging purposes
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

int handleCharsFinal(int vkCode, bool shift)
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
		return handleNumbers2(vkCode, shift);
		break;
	case 8:
		return 8;
		break;
	case 9:
		return 9;
		break;
	case 13:
		return 13;
		break;
	case 27:
		return 27;
		break;
	case 32:
		return 32;
		break;
	case 186:
		return (int)(!shift ? ';' : ':');
		break;
	case 187:
		return (int)(!shift ? '=' : '+');
		break;
	case 188:
		return (int)(!shift ? ',' : '<');
		break;
	case 189:
		return (int)(!shift ? '-' : '_');
		break;
	case 190:
		return (int)(!shift ? '.' : '>');
		break;
	case 191:
		return (int)(!shift ? '/' : '?');
		break;
	case 192:
		return (int)(!shift ? '`' : '~');
		break;
	case 219:
		return (int)(!shift ? '[' : '{');
		break;
	case 220:
		return (int)(!shift ? '\\' : '|');
		break;
	case 221:
		return (int)(!shift ? ']' : '}');
		break;
	case 222:
		return (int)(!shift ? '\'' : '\"');
		break;
	default:
		if (!shift) {
			char ch = (char)vkCode;
			return (int)(tolower(ch)); //convert char to 1-length string :)
		}
		else {
			return vkCode;
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

int handleNumbers2(int vkcode, bool shift)
{
	if (!shift)
		return vkcode;
	else
		return static_cast<int>(nums2[vkcode - 48]);
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