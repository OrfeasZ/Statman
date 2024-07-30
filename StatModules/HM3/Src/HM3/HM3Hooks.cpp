#include "HM3Hooks.h"
#include "HM3Module.h"

#include "Utils.h"

HM3Hooks::HM3Hooks() :
	m_Installed(false)
{
	Install();
}

HM3Hooks::~HM3Hooks()
{
	Uninstall();
}

bool HM3Hooks::Install()
{
	if (m_Installed)
		return true;

	if (MH_Initialize() != MH_OK)
	{
		Log("Failed to initialize MinHook.\n");
		return false;
	}
	
	DECLARE_PATTERN_HOOK(
		ZScene_Load,
		"\x56\x8B\x74\x24\x08\x8B\xC6\x57\xC6\x01",
		"xxxxxxxxxx"
	)

	DECLARE_PATTERN_HOOK(
		ZHM3LevelControl_FrameUpdate,
		"\x64\xA1\x00\x00\x00\x00\x6A\x00\x68\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x81\xEC\x00\x00\x00\x00\x56\x57\x8B\xF1\xE8\x00\x00\x00\x00\xD9\x46\x30",
		"xx????x?x????xxxx????xx????xxxxx????xxx"
	)

	DECLARE_PATTERN_HOOK(
		ZHM3LevelControl_MissionCompleted2,
		"\x55\x8B\xEC\x83\xE4\x00\x6A\x00\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x81\xEC\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x53\x55\x56\x8B\xF1",
		"xxxxx?x?x????xx????xxxx????xx????x????xxxxx"
	)

	DECLARE_PATTERN_HOOK(
		ZLimitSaves_Click,
		"\x53\x8B\x5C\x24\x08\x56\x8B\xF1\x3B\x5E\x6C",
		"xxxxxxxxxxx"
	)

	if (!HookD3D9())
		return false;
	
	m_Installed = true;
	return true;
}

bool HM3Hooks::HookD3D9()
{
	// Create the D3D9 interface.
	auto* s_D3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!s_D3D) {
		Log("Could not create D3D9 interface. Stats overlay won't work.\n");
		return false;
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
		return false;
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
		return false;
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

	return true;
}

void HM3Hooks::Uninstall()
{
	if (!m_Installed)
		return;
	
	m_Installed = false;

	REMOVE_HOOK(ZScene_Load)
	REMOVE_HOOK(ZHM3LevelControl_FrameUpdate)
	REMOVE_HOOK(ZHM3LevelControl_MissionCompleted2)
	REMOVE_HOOK(ZLimitSaves_Click)
	REMOVE_HOOK(IDirect3DDevice9__EndScene)
	
	if (MH_Uninitialize() != MH_OK)
		Log("Failed to uninitialize MinHook.\n");
}