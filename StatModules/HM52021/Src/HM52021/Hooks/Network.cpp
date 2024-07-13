#include <HM52021/HM52021Hooks.h>

#include <HM52021/Structs/ZHttp.h>

DECLARE_FASTCALL_DETOUR(HM52021Hooks, void, ZHttpManager_PopulateRequestPtrFromParams, ZHttpManager* th, ZHttpRequestWindows** request, ZHttpRequestParams* params)
{
	Log("Populating HTTP request from params.\n");

	Log("%s %s HTTP/1.1\n", ZHttpUrl::EVerbToStr(params->m_url.m_eVerb).c_str(), params->m_url.fullUrl().c_str());

	for (auto it = params->m_headers.begin(); it != params->m_headers.end(); ++it)
	{
		Log("%s: %s\n", it->m_key.c_str(), it->m_value.c_str());
	}

	Log("\n");
	Log("%s\n", params->m_body.c_str());
	Log("\n\n");

	return o_ZHttpManager_PopulateRequestPtrFromParams(th, request, params);
}

DECLARE_FASTCALL_DETOUR(HM52021Hooks, bool, ZHttpUrl_IsSecureProtocol, ZHttpUrl* th)
{
	Log("Checking for secure protocol on URL: %s\n", th->fullUrl().c_str());
	return false;
}