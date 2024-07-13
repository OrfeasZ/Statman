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
class ZHttpUrl;
class ZRuntimeResourceID;
class ZResourceID;
class ZAchievementManagerSimple;
class ZDynamicObject;
class ZChallengesManager;
class ZContractsManager;

class HM5Hooks
{
public:
	HM5Hooks();
	~HM5Hooks();

public:
	bool Install();

protected:
	void Uninstall();

public:
	DECLARE_FASTCALL_HOOK(void, SignalOutputPin, ZEntityType** entity, int32_t pin, ZVariantRef* data);
	DECLARE_FASTCALL_HOOK(void, ZHttpManager_PopulateRequestPtrFromParams, ZHttpManager* th, ZHttpRequestWindows** request, ZHttpRequestParams* params);
	DECLARE_FASTCALL_HOOK(void, ZEntitySceneContext_LoadScene, ZEntitySceneContext* th, const ZSceneData& data);
	DECLARE_FASTCALL_HOOK(bool, ZHttpUrl_IsSecureProtocol, ZHttpUrl* th);
	DECLARE_FASTCALL_HOOK(ZRuntimeResourceID*, ZRuntimeResourceID_QueryRuntimeResourceID, ZRuntimeResourceID* th, ZResourceID* resourceId)
	DECLARE_FASTCALL_HOOK(void, ZAchievementManagerSimple_OnEventSent, ZAchievementManagerSimple* th, uint32_t eventIndex, ZDynamicObject* event);
	DECLARE_FASTCALL_HOOK(void, ZChallengesManager_OnEventSent, ZChallengesManager* th, uint32_t eventIndex, ZDynamicObject* event);
	DECLARE_FASTCALL_HOOK(void, ZContractsManager_OnEventSent, ZContractsManager* th, uint32_t eventIndex, ZDynamicObject* event);

private:
	bool m_Installed;
};