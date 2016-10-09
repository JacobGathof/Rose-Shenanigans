#include "PopUpManager.h"

PopUpManager::PopUpManager()
{
}

PopUpManager::~PopUpManager()
{
}

Response PopUpManager::showError(LPCWSTR message, LPCWSTR title, int options) {
	return showBox(message, title, MB_ICONHAND | options);
}

Response PopUpManager::showWarning(LPCWSTR message, LPCWSTR title, int options) {
	return showBox(message, title, MB_ICONEXCLAMATION | options);
}

Response PopUpManager::showMessage(LPCWSTR message, LPCWSTR title, int options) {
	return showBox(message, title, MB_ICONASTERISK | options);
}

Response PopUpManager::showOptions(LPCWSTR message, LPCWSTR title, int options) {
	return showBox(message, title, options);
}

//void PopUpManager::showError(const char *message, const char *title) {
//	MessageBox(NULL, message, title, MB_ICONERROR);
//}
//
//void PopUpManager::showWarning(const char *message, const char *title) {
//	MessageBox(NULL, message, title, MB_ICONWARNING);
//}
//
//void PopUpManager::showMessage(const char *message, const char *title) {
//	MessageBox(NULL, message, title, MB_ICONINFORMATION);
//}

Response PopUpManager::showBox(LPCWSTR message, LPCWSTR title, int options) {
	int out = MessageBox(NULL, message, title, options);
	switch (out)
	{
	case IDOK:
		return Response::Ok;
	case IDCANCEL:
		return Response::Cancel;
	case IDABORT:
		return Response::Abort;
	case IDRETRY:
		return Response::Retry;
	case IDIGNORE:
		return Response::Ignore;
	case IDYES:
		return Response::Yes;
	case IDNO:
		return Response::No;
	case IDTRYAGAIN:
		return Response::TryAgain;
	case IDCONTINUE:
		return Response::Continue;
	default:
		return Response::None;
	}
}

void convert(const char *message, const char *title) {
	
}

