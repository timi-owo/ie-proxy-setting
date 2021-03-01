#ifndef _EXPORT_H_
#define _EXPORT_H_

#ifdef PROJECT_DLL_EXPORT
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif

#if !defined(_INC_WINDOWS) || !defined(_WINDOWS_)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

struct PROXY_SETTING
{
	BOOL	bEnabled;

	LPSTR	pszServer;
	size_t	uiServerLength;

	LPSTR	pszBypass;
	size_t	uiBypassLength;
};

#ifdef __cplusplus
extern "C" {
#endif

	DLLAPI BOOL WINAPI QueryProxyInfo(PROXY_SETTING* result);
	DLLAPI BOOL WINAPI EnableProxy(LPCSTR addr, UINT port);
	DLLAPI BOOL WINAPI DisableProxy();

#ifdef __cplusplus
}
#endif

#endif //_EXPORT_H_

