#include "common.h"
#include "export.h"

DLLAPI BOOL WINAPI QueryProxyInfo(PROXY_SETTING* result)
{
	INTERNET_PER_CONN_OPTION_LIST option_list;
	INTERNET_PER_CONN_OPTION options[3];

	option_list.dwSize = sizeof(option_list);
	option_list.pszConnection = NULL;
	option_list.dwOptionCount = 3;
	option_list.pOptions = options;

	options[0].dwOption = INTERNET_PER_CONN_FLAGS;
	options[1].dwOption = INTERNET_PER_CONN_PROXY_SERVER;
	options[2].dwOption = INTERNET_PER_CONN_PROXY_BYPASS;

	if (InternetQueryOption(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION, &option_list, &option_list.dwSize) == FALSE) { return FALSE; }

	result->bEnabled = (options[0].Value.dwValue & PROXY_TYPE_PROXY) == PROXY_TYPE_PROXY ? TRUE : FALSE;

	if (options[1].Value.pszValue != NULL)
	{ strncpy_s(result->pszServer, result->uiServerLength, options[1].Value.pszValue, result->uiServerLength - 1); }

	if (options[2].Value.pszValue != NULL)
	{ strncpy_s(result->pszBypass, result->uiBypassLength, options[2].Value.pszValue, result->uiBypassLength - 1); }

	return TRUE;
}

DLLAPI BOOL WINAPI EnableProxy(LPCSTR addr, UINT port)
{
	INTERNET_PER_CONN_OPTION_LIST option_list;
	INTERNET_PER_CONN_OPTION options[3];

	option_list.dwSize = sizeof(option_list);
	option_list.pszConnection = NULL;
	option_list.dwOptionCount = 3;
	option_list.pOptions = options;

	options[0].dwOption = INTERNET_PER_CONN_FLAGS;
	options[0].Value.dwValue = PROXY_TYPE_DIRECT | PROXY_TYPE_PROXY;

	char proxy_server[128];
	_snprintf_s(proxy_server, sizeof(proxy_server) - 1, "%s:%d", addr, port);

	options[1].dwOption = INTERNET_PER_CONN_PROXY_SERVER;
	options[1].Value.pszValue = proxy_server;

	options[2].dwOption = INTERNET_PER_CONN_PROXY_BYPASS;
	options[2].Value.pszValue = (LPSTR)"localhost;127.*;10.*;172.16.*;172.17.*;172.18.*;172.19.*;172.20.*;172.21.*;172.22.*;172.23.*;172.24.*;172.25.*;172.26.*;172.27.*;172.28.*;172.29.*;172.30.*;172.31.*;172.32.*;192.168.*";

	if (InternetSetOption(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION, &option_list, option_list.dwSize) == TRUE)
	{
		InternetSetOption(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0);
		InternetSetOption(NULL, INTERNET_OPTION_REFRESH, NULL, 0);
		return TRUE;
	}
	else { return FALSE; }
}

DLLAPI BOOL WINAPI DisableProxy()
{
	INTERNET_PER_CONN_OPTION_LIST option_list;
	INTERNET_PER_CONN_OPTION options[1];

	option_list.dwSize = sizeof(option_list);
	option_list.pszConnection = NULL;
	option_list.dwOptionCount = 1;
	option_list.pOptions = options;

	options[0].dwOption = INTERNET_PER_CONN_FLAGS;
	options[0].Value.dwValue = PROXY_TYPE_DIRECT;

	if (InternetSetOption(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION, &option_list, option_list.dwSize) == TRUE)
	{
		InternetSetOption(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0);
		InternetSetOption(NULL, INTERNET_OPTION_REFRESH, NULL, 0);
		return TRUE;
	}
	else { return FALSE; }
}

