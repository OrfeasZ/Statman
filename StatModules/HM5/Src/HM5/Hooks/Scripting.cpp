#include <HM5/HM5Hooks.h>
#include <HM5/HM5Module.h>
#include <HM5/HM5PinHandler.h>
#include <HM5/Structs/ZResourceID.h>
#include <HM5/Structs/ZObject.h>
#include <Pipeman.h>

#include <json.hpp>

using json = nlohmann::json;

DECLARE_FASTCALL_DETOUR(HM5Hooks, void, SignalOutputPin, ZEntityType** entity, int32_t pin, ZVariantRef* data)
{
	if (!g_Module->PinHandler())
		return o_SignalOutputPin(entity, pin, data);

	if (!g_Module->PinHandler()->OnOutputPinSignal(entity, pin, data))
		return;

	o_SignalOutputPin(entity, pin, data);
}

DECLARE_FASTCALL_DETOUR(HM5Hooks, ZRuntimeResourceID*, ZRuntimeResourceID_QueryRuntimeResourceID, ZRuntimeResourceID* th, ZResourceID* resourceId)
{
	Log("Querying runtime resource ID: %s\n", resourceId->m_uri.c_str());
	auto s_ResourceID = o_ZRuntimeResourceID_QueryRuntimeResourceID(th, resourceId);

	Log("ResourceID: %016llX (%llu)\n", s_ResourceID->m_ID, s_ResourceID->m_ID);

	return s_ResourceID;
}

DECLARE_FASTCALL_DETOUR(HM5Hooks, void, ZAchievementManagerSimple_OnEventSent, ZAchievementManagerSimple* th, uint32_t eventIndex, ZDynamicObject* event)
{
	ZString s_EventStr;
	event->ToString(event, &s_EventStr);
	
	// TODO: Properly do this by reverse engineering ZDynamicObject whenever I'm feeling brave.
	// This is a super lazy hack but it should work fine for now.
	auto s_JsonEvent = json::parse(s_EventStr.c_str());

	// Send game event to statman.
	Log("ZAchievementManagerSimple Event! %s\n", s_JsonEvent.dump(4).c_str());
	g_Module->Pipe()->SendPipeMessage("GE", s_EventStr.c_str());

	if (s_JsonEvent["Name"] == "BodyFound")
	{
		//Log("ZAchievementManagerSimple Event! %s\n", s_JsonEvent.dump(4).c_str());
		g_Module->Pipe()->SendPipeMessage("SU", "BodyFound");
	}
	else if (s_JsonEvent["Name"] == "NoticedKill")
	{
		//Log("ZAchievementManagerSimple Event! %s\n", s_JsonEvent.dump(4).c_str());
		g_Module->Pipe()->SendPipeMessage("SU", "NoticedKill");
	}
	else if (s_JsonEvent["Name"] == "ContractStart")
	{
		//Log("ZAchievementManagerSimple Event! %s\n", s_JsonEvent.dump(4).c_str());
		g_Module->Pipe()->SendPipeMessage("CS", "");
	}
	else if (s_JsonEvent["Name"] == "Kill")
	{
		//Log("ZAchievementManagerSimple Event! %s\n", s_JsonEvent.dump(4).c_str());
		bool s_Accident = s_JsonEvent["Value"]["Accident"];
		bool s_Target = s_JsonEvent["Value"]["IsTarget"];
		std::string s_ID = s_JsonEvent["Value"]["RepositoryId"];

		std::string s_Event = "Kill:";
		s_Event += s_ID;
		s_Event += ",";
		s_Event += (s_Accident ? "true" : "false");
		s_Event += ",";
		s_Event += (s_Target ? "true" : "false");

		g_Module->Pipe()->SendPipeMessage("SU", s_Event);
	}
	else if (s_JsonEvent["Name"] == "Spotted")
	{
		//Log("ZAchievementManagerSimple Event! %s\n", s_JsonEvent.dump(4).c_str());
		std::string s_Spotters;

		for (auto& s_Spotter : s_JsonEvent["Value"])
		{
			if (s_Spotters.size() > 0)
				s_Spotters += ",";

			s_Spotters += s_Spotter;
		}

		g_Module->Pipe()->SendPipeMessage("SU", "Spotted:" + s_Spotters);
	}
	else if (s_JsonEvent["Name"] == "Witnesses")
	{
		//Log("ZAchievementManagerSimple Event! %s\n", s_JsonEvent.dump(4).c_str());
		std::string s_Witnesses;

		for (auto& s_Witness : s_JsonEvent["Value"])
		{
			if (s_Witnesses.size() > 0)
				s_Witnesses += ",";

			s_Witnesses += s_Witness;
		}

		g_Module->Pipe()->SendPipeMessage("SU", "Witnesses:" + s_Witnesses);
	}
	else if (s_JsonEvent["Name"] == "SecuritySystemRecorder")
	{
		//Log("ZAchievementManagerSimple Event! %s\n", s_JsonEvent.dump(4).c_str());
		std::string s_Event = s_JsonEvent["Value"]["event"];
        
		if (s_Event == "spotted")
		{
			g_Module->Pipe()->SendPipeMessage("SU", "CaughtOnCamera");
		}
		else if (s_Event == "destroyed")
		{
			g_Module->Pipe()->SendPipeMessage("SU", "RecordingsDestroyed");
		}
	}

	return o_ZAchievementManagerSimple_OnEventSent(th, eventIndex, event);
}

DECLARE_FASTCALL_DETOUR(HM5Hooks, void, ZChallengesManager_OnEventSent, ZChallengesManager* th, uint32_t eventIndex, ZDynamicObject* event)
{
	ZString s_EventStr;
	event->ToString(event, &s_EventStr);

	// TODO: Properly do this by reverse engineering ZDynamicObject whenever I'm feeling brave.
	// This is a super lazy hack but it should work fine for now.
	auto s_JsonEvent = json::parse(s_EventStr.c_str());

	Log("ZChallengesManager Event! %s\n", s_JsonEvent.dump(4).c_str());

	return o_ZChallengesManager_OnEventSent(th, eventIndex, event);
}

DECLARE_FASTCALL_DETOUR(HM5Hooks, void, ZContractsManager_OnEventSent, ZContractsManager* th, uint32_t eventIndex, ZDynamicObject* event)
{
	ZString s_EventStr;
	event->ToString(event, &s_EventStr);

	// TODO: Properly do this by reverse engineering ZDynamicObject whenever I'm feeling brave.
	// This is a super lazy hack but it should work fine for now.
	auto s_JsonEvent = json::parse(s_EventStr.c_str());

	Log("ZContractsManager Event! %s\n", s_JsonEvent.dump(4).c_str());

	return o_ZContractsManager_OnEventSent(th, eventIndex, event);
}