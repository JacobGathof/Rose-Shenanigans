#pragma once
//#include "boxer.h"
#include <Windows.h>

// Documentation of valid options can be found below
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms645505(v=vs.85).aspx

enum Response {
	None,
	Ok,
	Cancel,
	Abort,
	Retry,
	Ignore,
	Yes,
	No,
	TryAgain,
	Continue
};

class PopUpManager
{
public:
	PopUpManager();
	~PopUpManager();

	static Response showError(LPCWSTR message, LPCWSTR title, int options = 0);
	static Response showWarning(LPCWSTR message, LPCWSTR title, int options = 0);
	static Response showMessage(LPCWSTR message, LPCWSTR title, int options = 0);
	static Response showOptions(LPCWSTR message, LPCWSTR title, int options);

	//static void showError(const char *message, const char *title);
	//static void showWarning(const char *message, const char *title);
	//static void showMessage(const char *message, const char *title);

private:
	static Response PopUpManager::showBox(LPCWSTR message, LPCWSTR title, int options);

};

