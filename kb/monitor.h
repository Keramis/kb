#include "includes.h"

//this is the monitoring module.
//we will monitor the active window and determine if it's worth listening to.

bool doMonitor(int &err, std::wstring &exename);