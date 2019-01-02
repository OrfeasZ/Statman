#include <HM5/HM5Hooks.h>

#include <HM5/Structs/ZHttp.h>

DECLARE_FASTCALL_DETOUR(HM5Hooks, void, ZHttpManager_PopulateRequestPtrFromParams, ZHttpManager* th, ZHttpRequestWindows** request, ZHttpRequestParams* params)
{
	/*Log("Populating HTTP request from params.\n");

	Log("%s %s HTTP/1.1\n", ZHttpUrl::EVerbToStr(params->m_url.m_eVerb).c_str(), params->m_url.fullUrl().c_str());

	for (auto it = params->m_headers.begin(); it != params->m_headers.end(); ++it)
	{
		Log("%s: %s\n", it->m_key.c_str(), it->m_value.c_str());
	}

	Log("\n");
	Log("%s\n", params->m_body.c_str());
	Log("\n\n");*/

	return o_ZHttpManager_PopulateRequestPtrFromParams(th, request, params);
}