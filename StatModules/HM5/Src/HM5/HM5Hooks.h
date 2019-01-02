#pragma once

#include <stdafx.h>
#include <Hooks.h>

class ZEntityType;
class ZVariantRef;
class ZHttpManager;
class ZHttpRequestWindows;
class ZHttpRequestParams;

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

private:
	bool m_Installed;
};