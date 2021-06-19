#include "HM3Module.h"

#include "HM3Hooks.h"
#include "HM3Pointers.h"
#include "HM3Functions.h"

#include <Pipeman.h>
#include <functional>

HM3Module::HM3Module() :
	m_Pipeman(nullptr),
	m_Hooks(nullptr),
	m_Pointers(nullptr),
	m_Functions(nullptr),
	m_CheatsEnabled(false),
	m_UnlimitedSaves(false),
	m_Hitman2016Mode(false)
{
	if (!CheckInstance())
		return;

#ifdef _DEBUG
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
#endif

	Log("Initializing Statman HM3 stat module...\n");

	SetEnvironmentVariable("Statman_HM3", "\x01\x00");

	Log("Waiting for the game to be ready...\n");

	// Make sure the game is fully loaded.
	while (GetModuleHandleA("d3d9") == NULL && GetModuleHandleA("d3d3.dll") == NULL)
		Sleep(5);

	Log("Initialized!\n");

	// Patch required data.
	PerformPatches();

	const HM3Version version = CheckVersion();

	// Setup pointers, functions, and hooks.
	m_Pointers = new HM3Pointers(version);
	// TODO: figure out addresses for these in GOG version
	m_Functions = new HM3Functions();
	m_Hooks = new HM3Hooks(version);

	// Setup Pipeman.
	m_Pipeman = new Pipeman("\\\\.\\pipe\\Statman_IPC", "H3");
	m_Pipeman->SetMessageCallback(std::bind(&HM3Module::OnMessage, this, std::placeholders::_1, std::placeholders::_2));
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
	if (p_Type == "EC")
	{
		// Enable cheats.
		m_CheatsEnabled = p_Content == "true";
		*(bool*) (0x008ABA89) = m_CheatsEnabled;
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
		// Unlimited saves.
		m_Hitman2016Mode = p_Content == "true";
		return;
	}
}