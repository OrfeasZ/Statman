#pragma once

#include <stdafx.h>
#include <Hooks.h>

class ZEntityType;
class ZVariantRef;
class ZHttpManager;
class ZHttpRequestWindows;
class ZHttpRequestParams;
class ZSceneData;
class ZEntitySceneContext;

class HM5Hooks
{
public:
	HM5Hooks();
	~HM5Hooks();

protected:
	bool Install();
	void Uninstall();

public:
	DECLARE_FASTCALL_HOOK(void, SignalOutputPin, ZEntityType** entity, int32_t pin, ZVariantRef* data);
	DECLARE_FASTCALL_HOOK(void, ZHttpManager_PopulateRequestPtrFromParams, ZHttpManager* th, ZHttpRequestWindows** request, ZHttpRequestParams* params);
	DECLARE_FASTCALL_HOOK(void, ZEntitySceneContext_LoadScene, ZEntitySceneContext* th, const ZSceneData& data);

private:
	bool m_Installed;
};