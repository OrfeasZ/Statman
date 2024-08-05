#include "HM3Module.h"

#include "HM3Hooks.h"
#include "HM3Pointers.h"
#include "HM3Functions.h"

#include <Pipeman.h>
#include <functional>
#include <json.hpp>
#include <fstream>
#include <filesystem>

#include "Utils.h"

HM3Module::HM3Module()
{
}

HM3Module::~HM3Module()
{
	if (m_Pipeman)
		delete m_Pipeman;

	if (m_Hooks)
		delete m_Hooks;

	if (m_Pointers)
		delete m_Pointers;

	if (m_Functions)
		delete m_Functions;

	m_Pipeman = nullptr;
	m_Hooks = nullptr;
	m_Pointers = nullptr;
	m_Functions = nullptr;

	SetEnvironmentVariable("Statman_HM3", "\x02\x00");
}

bool HM3Module::Init()
{
	if (!CheckInstance())
	{
		Log("The current stat module is already loaded. Exiting.\n");
		return false;
	}

#ifdef _DEBUG
	char s_Buffer[2];
	if (!GetEnvironmentVariableA("Statman_HM3", s_Buffer, 2) || s_Buffer[0] != 0x02)
	{
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		SetConsoleTitleA("Statman - Debug Console");
		freopen("CON", "w", stdout);
	}
#endif

	Log("Initializing Statman HM3 stat module...\n");

	SetEnvironmentVariable("Statman_HM3", "\x01\x00");

	Log("Waiting for the game to be ready...\n");

	// Make sure the game is fully loaded.
	while (GetModuleHandleA("d3d9") == NULL && GetModuleHandleA("d3d3.dll") == NULL)
		Sleep(5);

	Log("Initialized!\n");

	// Get the module base address and size.
	HMODULE s_Module = GetModuleHandleA(nullptr);
	m_ModuleBase = reinterpret_cast<uintptr_t>(s_Module) + Utils::GetBaseOfCode(s_Module);
	m_SizeOfCode = Utils::GetSizeOfCode(s_Module);

	Log("Module base address: %x\n", m_ModuleBase);
	Log("Module size: %x\n", m_SizeOfCode);

	/*
	// Print item names
	struct ItemTypeName {
		int32_t id;
		const char* name;
	};

	auto* s_ItemTypeNames = reinterpret_cast<ItemTypeName*>(0x008031E0);

	for (int i = 0; i < 321; ++i) {
		Log("Item [%d] = %s\n", s_ItemTypeNames[i].id, s_ItemTypeNames[i].name);
	}

	Sleep(5000);*/
	
	// Patch required data.
	PerformPatches();

	// Setup pointers, functions, and hooks.
	m_Pointers = new HM3Pointers();
	m_Functions = new HM3Functions();
	m_Hooks = new HM3Hooks();

	// Setup Pipeman.
	m_Pipeman = new Pipeman(R"(\\.\pipe\Statman_IPC)", "H3");
	m_Pipeman->SetMessageCallback(std::bind(&HM3Module::OnMessage, this, std::placeholders::_1, std::placeholders::_2));
	m_Pipeman->SetConnectedCallback([this]()
	{
		m_Pipeman->SendPipeMessage("HI", "");
	});

	return true;
}

bool HM3Module::CheckInstance()
{
	char s_Buffer[2];
	if (GetEnvironmentVariableA("Statman_HM3", s_Buffer, 2) && s_Buffer[0] == 0x01)
		return false;

	return true;
}

void HM3Module::PerformPatches()
{
	// Nothing here.
}

void HM3Module::OnMessage(const std::string& p_Type, const std::string& p_Content)
{
	Log("Got message '%s' from IPC: %s\n", p_Type.c_str(), p_Content.c_str());

	if (p_Type == "EC")
	{
		// Enable cheats.
		m_CheatsEnabled = p_Content == "true";
		*Pointers()->CConfiguration__m_bCheatsEnabled = m_CheatsEnabled;
		return;
	}

	if (p_Type == "US")
	{
		// Unlimited saves.
		m_UnlimitedSaves = p_Content == "true";
		return;
	}

	if (p_Type == "H2")
	{
		// Hitman 2016 mode.
		m_Hitman2016Mode = p_Content == "true";
		return;
	}

	if (p_Type == "OV")
	{
		// Overlay toggle
		m_OverlayEnabled = p_Content == "true";
		return;
	}

	if (p_Type == "2D")
	{
		// Draw debug overlay for 2016 mode
		m_Debug2016 = p_Content == "true";
		return;
	}

	if (p_Type == "2J")
	{
		// Parse Hitman 2016 data.
		ParseHitman2016Data(p_Content);
		return;
	}

	if (p_Type == "XX")
	{
		Log("Statman requested exit.\n");

		std::thread s_ExitThread([]()
		{
			delete g_Module;
			g_Module = nullptr;
		});

		s_ExitThread.detach();

		return;
	}
}
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

void HM3Module::ParseHitman2016Data(const std::string& p_Json) {
	try {
		m_LevelStartingLocations.clear();
		
		nlohmann::json s_Json = nlohmann::json::parse(p_Json);

		if (s_Json.is_null())
			return;

		// Parse level starting locations.
		for (auto& [s_Level, s_Locations] : s_Json.items()) {
			std::vector<LevelStartingLocation> s_LevelLocations;

			for (auto& [s_Name, s_Location] : s_Locations.items()) {
				LevelStartingLocation s_LocationData;
				s_LocationData.Name = s_Name;

				const auto s_Positions = s_Location["position"];

				s_LocationData.Rotation = {
					.xAxis = { s_Positions[0][0], s_Positions[0][1], s_Positions[0][2] },
					.yAxis = { s_Positions[1][0], s_Positions[1][1], s_Positions[1][2] },
					.zAxis = { s_Positions[2][0], s_Positions[2][1], s_Positions[2][2] }
				};

				s_LocationData.Position = {
					s_Positions[3][0],
					s_Positions[3][1],
					s_Positions[3][2]
				};

				s_LocationData.Outfit = s_Location["outfit"];

				s_LevelLocations.push_back(s_LocationData);
			}

			m_LevelStartingLocations[s_Level] = s_LevelLocations;
		}
	}
	catch (std::exception& e) {
		Log("Could not parse Hitman 2016 data: %s\n", e.what());
	}
}