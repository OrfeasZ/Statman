#pragma once

#include <stdafx.h>
#include <Hooks.h>
#include <d3d9.h>
#pragma comment(lib, "d3d9")

struct DetectionIterator;
class ZScene;
class ZHM3LevelControl;
class ZLimitSaves;
class ZXMLGUISystem;
enum eZWUserEvents : int32_t;

class HM3Hooks
{
public:
	HM3Hooks();
	~HM3Hooks();

protected:
	bool Install();
	void Uninstall();
	bool HookD3D9();

public:
	DECLARE_THISCALL_HOOK(void, ZScene_Load, ZScene* th, const char* scene);
	DECLARE_THISCALL_HOOK(void, ZHM3LevelControl_FrameUpdate, ZHM3LevelControl* th);
	DECLARE_THISCALL_HOOK(int, ZHM3LevelControl_MissionCompleted2, ZHM3LevelControl* th);
	DECLARE_THISCALL_HOOK(void, ZLimitSaves_Click, ZLimitSaves* th, eZWUserEvents a2, int a3, ZXMLGUISystem* a4);
	DECLARE_STDCALL_HOOK(HRESULT, IDirect3DDevice9__EndScene, IDirect3DDevice9* th);

private:
	bool m_Installed;
};