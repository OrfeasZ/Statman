#include "HM3Hooks.h"

struct DetourAddresses
{
	uint32_t LoadSceneDetour;
	uint32_t UnknownUpdateDetour;
	uint32_t EndLevelDetour;
	uint32_t LimitedLivesDetour;
};

// The order corresponds to HM3Version enum values and should not be changed
static const DetourAddresses DetourVersions[]
{
	{ 0x00000000, 0x00000000, 0x00000000, 0x00000000 }, // Unknown version
	{ 0x0045A440, 0x006AF230, 0x006AEC80, 0x00677660 }, // Steam
	{ 0x0045A510, 0x006AFAF0, 0x006AF540, 0x00677F70 }  // GOG
};

HM3Hooks::HM3Hooks(HM3Version p_Version) :
	m_Installed(false)
{
	Install(p_Version);
}

HM3Hooks::~HM3Hooks()
{
	Uninstall();
}

void HM3Hooks::Install(HM3Version p_Version)
{
	if (m_Installed)
		return;

	if (MH_Initialize() != MH_OK)
	{
		Log("Failed to initialize MinHook.\n");
		return;
	}

	const DetourAddresses& s_Addresses(DetourVersions[p_Version]);

	if (s_Addresses.LoadSceneDetour == 0)
	{
		Log("Unsupported game version.\n");
		return;
	}

	m_Installed = true;

	DECLARE_OFFSET_HOOK(LoadScene, s_Addresses.LoadSceneDetour);
	DECLARE_OFFSET_HOOK(UnknownUpdateFunc01, s_Addresses.UnknownUpdateDetour);
	DECLARE_OFFSET_HOOK(EndLevel, s_Addresses.EndLevelDetour);
	DECLARE_OFFSET_HOOK(LimitedLives_SelectedGUIElement, s_Addresses.LimitedLivesDetour);
	//DECLARE_OFFSET_HOOK(UnknownClass02_NextDetectionNPC, 0x0042E810); // 0x0042E850?

	HookD3D9();
}

void HM3Hooks::HookD3D9()
{
	// Create the D3D9 interface.
	auto* s_D3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!s_D3D) {
		Log("Could not create D3D9 interface. Stats overlay won't work.\n");
		return;
	}

	// Create a window for our dummy device.
	WNDCLASSEX s_WindowClass{};
	s_WindowClass.cbSize = sizeof(WNDCLASSEX);
	s_WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	s_WindowClass.lpfnWndProc = DefWindowProc;
	s_WindowClass.lpszClassName = "Statman";
	RegisterClassEx(&s_WindowClass);

	HWND s_Window = CreateWindowEx(NULL, s_WindowClass.lpszClassName, "Statman", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, nullptr, nullptr);

	if (!s_Window) {
		Log("Could not create window for D3D9 device. Stats overlay won't work.\n");
		s_D3D->Release();
		return;
	}

	// Create our dummy device.
	D3DPRESENT_PARAMETERS s_Params{};
	ZeroMemory(&s_Params, sizeof(s_Params));
	s_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	s_Params.hDeviceWindow = s_Window;
	s_Params.Windowed = true;

	IDirect3DDevice9* s_Device = nullptr;
	const auto s_Result = s_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, s_Window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &s_Params, &s_Device);

	if (!SUCCEEDED(s_Result)) {
		Log("Could not create D3D device with error %x. Stats overlay won't work.\n", s_Result);
		DestroyWindow(s_Window);
		s_D3D->Release();
		return;
	}

	// Get the address to EndScene method.
	const auto* s_VTable = *reinterpret_cast<uintptr_t**>(s_Device);
	const intptr_t s_EndSceneOffset = 168;
	const auto s_EndSceneAddress = s_VTable[s_EndSceneOffset / sizeof(uintptr_t)];

	// Install the hook.
	DECLARE_OFFSET_HOOK(IDirect3DDevice9__EndScene, s_EndSceneAddress);

	// Clean things up.
	DestroyWindow(s_Window);
	s_Device->Release();
	s_D3D->Release();
}

void HM3Hooks::Uninstall()
{
	if (!m_Installed)
		return;
	
	m_Installed = false;

	REMOVE_HOOK(LoadScene);
	REMOVE_HOOK(UnknownUpdateFunc01);
	REMOVE_HOOK(EndLevel);
	REMOVE_HOOK(LimitedLives_SelectedGUIElement);
	//REMOVE_HOOK(UnknownClass02_NextDetectionNPC);
	REMOVE_HOOK(IDirect3DDevice9__EndScene);

	if (MH_Uninitialize() != MH_OK)
		Log("Failed to uninitialize MinHook.\n");
}