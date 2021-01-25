#include <HM52021/HM52021Hooks.h>
#include <HM52021/HM52021Module.h>
#include <Pipeman.h>

#include <HM52021/Structs/ZScene.h>

DECLARE_FASTCALL_DETOUR(HM52021Hooks, void, ZEntitySceneContext_LoadScene, ZEntitySceneContext* th, const ZSceneData& data)
{
	Log("Loading scene!\n");

	Log("Scene: %s\n", data.m_sceneName.c_str());
	Log("Start Scene: %d\n", data.m_bStartScene);
	Log("Scene Unk01: %d\n", data.m_unk01);
	Log("Scene Type: %s\n", data.m_type.c_str());
	Log("Scene CodeName Hint: %s\n", data.m_codeNameHint.c_str());

	for (auto it = data.m_sceneBricks.begin(); it != data.m_sceneBricks.end(); ++it)
	{
		Log("Scene brick: %s\n", it->c_str());
	}

	o_ZEntitySceneContext_LoadScene(th, data);

	g_Module->Pipe()->SendPipeMessage("LS", data.m_sceneName.c_str());
}