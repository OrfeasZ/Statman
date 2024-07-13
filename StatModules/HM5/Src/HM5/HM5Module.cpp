#include "HM5Module.h"

#include "HM5Pointers.h"
#include "HM5Hooks.h"
#include "HM5PinHandler.h"

#include <Pipeman.h>
#include <functional>
#include <Utils.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

#include <HM5/Structs/ZAIGameState.h>
#include <HM5/Structs/ZGameStats.h>
#include <HM5/Structs/ZTypeRegistry.h>
#include <HM5/Structs/ZScene.h>
#include <HM5/Structs/ZModule.h>
#include <HM5/Structs/ZGameContext.h>

#ifdef _DEBUG
#include "HM5Generator.h"
#endif

HM5Module::HM5Module() :
	m_Pipeman(nullptr),
	m_Pointers(nullptr),
	m_PinHandler(nullptr),
	m_Hooks(nullptr),
	m_ModuleBase(0),
	m_SizeOfCode(0)
{
}

HM5Module::~HM5Module()
{
	if (m_Pipeman)
		delete m_Pipeman;

	if (m_Pointers)
		delete m_Pointers;

	if (m_Hooks)
		delete m_Hooks;

	if (m_PinHandler)
		delete m_PinHandler;

	m_Pipeman = nullptr;
	m_Pointers = nullptr;
	m_Hooks = nullptr;
	m_PinHandler = nullptr;

	Log("Resetting stat module environment variable.\n");

	SetEnvironmentVariable("Statman_HM5", "\x02\x00");
}

bool HM5Module::Init()
{
	if (!CheckInstance())
	{
		Log("The current stat module is already loaded. Exiting.\n");
		return false;
	}

#ifdef _DEBUG
	char s_Buffer[2];
	if (!GetEnvironmentVariableA("Statman_HM5", s_Buffer, 2) || s_Buffer[0] != 0x02)
	{
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		SetConsoleTitleA("Statman - Debug Console");
		freopen("CON", "w", stdout);
	}
#endif

	Log("Initializing Statman HM5 stat module...\n");

	SetEnvironmentVariable("Statman_HM5", "\x01\x00");

	Log("Waiting for the game to be ready...\n");

	// Make sure the game is fully loaded.
	while (GetModuleHandleA("dxgi") == NULL && GetModuleHandleA("dxgi.dll") == NULL)
		Sleep(5);

	Log("Game is ready. Setting up basic configuration.\n");

	// Get the module base address and size.
	HMODULE s_Module = GetModuleHandleA(nullptr);
	m_ModuleBase = reinterpret_cast<uintptr_t>(s_Module) + Utils::GetBaseOfCode(s_Module);
	m_SizeOfCode = Utils::GetSizeOfCode(s_Module);

	// Patch required data.
	PerformPatches();

	// Setup pointers, functions, and hooks.
	m_Pointers = new HM5Pointers();
	m_Hooks = new HM5Hooks();
	m_PinHandler = new HM5PinHandler();

	if (!m_Pointers->Setup())
	{
		Log("Failed to setup HM5 pointers. Statman may require an update to support the latest game.");
		return false;
	}

	if (!m_Hooks->Install())
	{
		Log("Failed to install HM5 hooks. Statman may require an update to support the latest game.");
		return false;
	}

	// Wait for late initialization.
	Log("Waiting for game late initialization...\n");

	while (!(*m_Pointers->g_pTypeRegistry) || (*m_Pointers->g_pTypeRegistry)->m_types.m_nSize < 4300)
		Sleep(1000);

	Log("Game late initialization finished!\n");

	// Setup Pipeman.
	m_Pipeman = new Pipeman("\\\\.\\pipe\\Statman_IPC", "H5");
	m_Pipeman->SetMessageCallback(std::bind(&HM5Module::OnMessage, this, std::placeholders::_1, std::placeholders::_2));

	m_Pipeman->SetConnectedCallback([]()
	{
		Log("Connected to Statman via Pipeman!\n");

		Log("Sending ZGameTimeManager address.\n");
		std::string s_PointerStr = std::to_string(reinterpret_cast<uintptr_t>(g_Module->Pointers()->g_pGameTimeManagerSingleton));
		g_Module->Pipe()->SendPipeMessage("GT", s_PointerStr);

		Log("Sending ZEntitySceneContext address.\n");
		s_PointerStr = std::to_string(reinterpret_cast<uintptr_t>((*g_Module->Pointers()->g_pHitman5Module)->m_pEntitySceneContext));
		g_Module->Pipe()->SendPipeMessage("SC", s_PointerStr);
	});

#ifdef _DEBUG
	// If we're running in debug mode dump all reflection data.
	HM5Generator s_Generator;
	s_Generator.Generate();
#endif

	return true;
}

bool HM5Module::CheckInstance()
{
	char s_Buffer[2];
	if (GetEnvironmentVariableA("Statman_HM5", s_Buffer, 2) && s_Buffer[0] == 0x01)
		return false;

	return true;
}

void HM5Module::PerformPatches()
{
	// Nothing here.
	// Interesting function: ZCompiledBehaviorTree::InitializeBehavior
}

void HM5Module::OnMessage(const std::string& p_Type, const std::string& p_Content)
{
	if (p_Type == "GS")
	{
		Log("Got GameStats message!\n");
		Log("Has %zd stats.\n", m_Pointers->g_pGameStatsSingleton->size());

		for (auto it = m_Pointers->g_pGameStatsSingleton->begin(); it != m_Pointers->g_pGameStatsSingleton->end(); ++it)
		{
			Log("Got stat pair: %p\n", (*it));
			Log("Pair key: %s\n", it->m_key.c_str());
		}

		auto s_Module = *m_Pointers->g_pHitman5Module;

		Log("Scene: %s\n", s_Module->m_pEntitySceneContext->m_sceneData.m_sceneName.c_str());
		Log("Start Scene: %d\n", s_Module->m_pEntitySceneContext->m_sceneData.m_bStartScene);
		Log("Scene Unk01: %d\n", s_Module->m_pEntitySceneContext->m_sceneData.m_unk01);
		Log("Scene Type: %s\n", s_Module->m_pEntitySceneContext->m_sceneData.m_type.c_str());
		Log("Scene CodeName Hint: %s\n", s_Module->m_pEntitySceneContext->m_sceneData.m_codeNameHint.c_str());

		for (auto it = s_Module->m_pEntitySceneContext->m_sceneData.m_sceneBricks.begin(); it != s_Module->m_pEntitySceneContext->m_sceneData.m_sceneBricks.end(); ++it)
		{
			Log("Scene brick: %s\n", it->c_str());
		}

		return;
	}

	if (p_Type == "LS")
	{
		auto s_Parts = Utils::SplitString(p_Content, ',');

		ZSceneData* s_Data = new ZSceneData();
		s_Data->m_sceneName = ZString(s_Parts[0]);
		s_Data->m_bStartScene = true;
		s_Data->m_unk01 = true;
		s_Data->m_type = ZString(s_Parts[1]);
		s_Data->m_codeNameHint = ZString(s_Parts[2]);

		for (size_t i = 3; i < s_Parts.size(); ++i)
		{
			s_Data->m_sceneBricks.push_back(ZString(s_Parts[i]));
		}

		Log("Loading scene '%s'.\n", s_Parts[0].c_str());

		// This works as long as there's at least two bricks specified. Needs fixing.
		m_Pointers->g_pGameContextSingleton->SetPendingTransition(*s_Data);

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