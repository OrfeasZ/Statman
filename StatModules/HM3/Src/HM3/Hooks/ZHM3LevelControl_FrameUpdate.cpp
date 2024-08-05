#include <algorithm>
#include <HM3/HM3Hooks.h>

#include <HM3/HM3Module.h>
#include <HM3/HM3Functions.h>
#include <HM3/HM3Pointers.h>

#include <HM3/Structs/ZHM3Actor.h>
#include <HM3/Structs/HM3Stats.h>
#include <HM3/Structs/ZHM3LevelControl.h>
#include <HM3/Structs/UnknownClass02.h>
#include <HM3/Structs/ZHM3GameData.h>
#include <HM3/Structs/ZHM3Actor.h>
#include <HM3/Structs/ZRender.h>

#include <directxmath.h>

DECLARE_THISCALL_DETOUR(HM3Hooks, void, ZHM3LevelControl_FrameUpdate, ZHM3LevelControl* th)
{
	if (!g_Module || !g_Module->Pointers() || !g_Module->Functions())
		return o_ZHM3LevelControl_FrameUpdate(th);

	// VTable: 0x00755ADC
	auto s_Class02 = reinterpret_cast<UnknownClass02*>(reinterpret_cast<char*>(th) + sizeof(ZHM3LevelControl));

	// Calculate Stats
	int s_Witnesses = 0;

	DetectionIterator s_DetectionIt;
	s_Class02->InitDetectionIterator(&s_DetectionIt);

	//Log("Class2: %p\n", s_Class02);

	auto s_Hitman = (*g_Module->Pointers()->g_pGameData)->m_pHitman;

	for (ZREF s_NPCID = s_Class02->NextDetectionNPC(&s_DetectionIt); s_DetectionIt.m_Unk01 > 0; s_NPCID = s_Class02->NextDetectionNPC(&s_DetectionIt))
	{
		auto s_NPC = reinterpret_cast<ZHM3Actor*>(g_Module->Functions()->ZGEOM_RefToPtr(s_NPCID));

		if (!s_NPC)
			continue;

		if (!s_NPC->IsDead())
			++s_Witnesses;
	}

	int s_WeaponsInHand = 0;

	auto s_GameData = *g_Module->Pointers()->g_pGameData;

	if (s_GameData && th->m_pWeaponStorage && s_GameData->m_pLevelLinking)
	{
		g_Module->Functions()->ZHitmanWeaponStorage_EmptyStorage(th->m_pWeaponStorage, s_GameData->m_pLevelLinking);
		s_WeaponsInHand += g_Module->Functions()->ZHitmanWeaponStorage_NrOfCustomWeaponsInStorage(th->m_pWeaponStorage);
	}

	if (s_GameData && th->m_pWeaponStorage2 && s_GameData->m_pLevelLinking)
	{
		g_Module->Functions()->ZHitmanWeaponStorage_EmptyStorage(th->m_pWeaponStorage2, s_GameData->m_pLevelLinking);
		s_WeaponsInHand += g_Module->Functions()->ZHitmanWeaponStorage_NrOfCustomWeaponsInStorage(th->m_pWeaponStorage2);
	}

	// Update stats.
	if (g_Module->Pointers()->ZHM3LevelControl__m_stats)
	{
		g_Module->Pointers()->ZHM3LevelControl__m_stats->m_Witnesses = s_Witnesses;
		g_Module->Pointers()->ZHM3LevelControl__m_stats->m_CustomWeaponsLeftOnLevel = th->m_WeaponsLeftOnLevel - s_WeaponsInHand - g_Module->Functions()->ZHM3LevelControl_GetCustomWeaponsInventoryCount();

		if (s_GameData && s_GameData->m_pHitman)
			g_Module->Pointers()->ZHM3LevelControl__m_stats->m_SuitLeftOnLevel = s_GameData->m_pHitman->m_Unknown01 != s_GameData->m_pHitman->m_Unknown02;

		if (g_Module && g_Module->Hitman2016Mode())
			g_Module->Pointers()->ZHM3LevelControl__m_stats->m_SuitLeftOnLevel = false;
	}

	/*static int s_DidShit = 0;

	if (GetAsyncKeyState(VK_F5) && s_Hitman)
	{
		if (s_DidShit >= (*g_Module->Pointers()->g_pGameData)->m_nActorCount)
			s_DidShit = 0;

		Log("Hitman: %p\n", s_Hitman);

		auto s_TargetNpc = (*g_Module->Pointers()->g_pGameData)->m_aActors[s_DidShit++];
		Log("Target NPC: %p\n", s_TargetNpc);

		auto s_HitmanAs = s_TargetNpc->GetHitmanAs();
		Log("Hitman as: %x\n", s_HitmanAs);

		if (s_HitmanAs)
		{
			auto s_HitmanAsPtr = reinterpret_cast<ZHM3HmAs*>(g_Module->Functions()->ZGEOM_RefToPtr(s_HitmanAs));
			Log("Hitman as ptr: %p\n", s_HitmanAsPtr);

			if (s_HitmanAsPtr)
			{
				g_Module->Functions()->ZHitman3_ChangeIntoNewClothes(s_Hitman, s_HitmanAsPtr, s_TargetNpc, false, nullptr, 0);
				//Log("Dog: %f\n", s_Hitman->GetHealth());
			}
		}

		/*if ((*g_Module->Pointers()->g_pSysInterface)->m_pRenderer)
		{
			auto s_Renderer = (*g_Module->Pointers()->g_pSysInterface)->m_pRenderer;
			auto s_MainCamera = s_Renderer->GetCamera(0);

			if (s_MainCamera)
			{
				auto s_CameraPtr = reinterpret_cast<ZCAMERA*>(g_Module->Functions()->ZGEOM_RefToPtr(s_MainCamera));
				Log("Camera ptr: %p\n", s_CameraPtr);

				Log("Near: %f\n", s_CameraPtr->m_fNear);
				Log("Far: %f\n", s_CameraPtr->m_fFar);
				Log("FOV: %f\n", s_CameraPtr->GetFOV());
				Log("View Aspect: %f\n", s_CameraPtr->GetViewAspect());

				s_CameraPtr->SetFOV(120.0f);

				//auto s_ProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(s_CameraPtr->GetFOV(), s_CameraPtr->GetViewAspect(), s_CameraPtr->m_fNear, s_CameraPtr->m_fFar);
				
			}
		}#1#

		//Sleep(500);
	}*/
	
	// If we're in Hitman 2016 mode, and the level just loaded, check if the loaded scene partially matches any of the levels.
	if (g_Module->Hitman2016Mode() && g_Module->m_SceneLoaded)
	{
		g_Module->m_SceneLoaded = false;

		Log("First frame after scene load. Trying to find a starting location.\n");

		for (const auto& [s_Level, s_Locations] : g_Module->GetLevelStartingLocations())
		{
			auto s_LevelLower = s_Level;
			std::transform(s_LevelLower.begin(), s_LevelLower.end(), s_LevelLower.begin(), ::tolower);

			Log("Checking level %s with %d locations.\n", s_LevelLower.c_str(), s_Locations.size());
			Log("Scene: %s\n", g_Module->m_SceneName.c_str());

			// Check if s_Level is a substring of the loaded scene and if we have any locations for that level.
			if (s_Locations.size() > 0 && g_Module->m_SceneName.find(s_LevelLower) != std::string::npos)
			{
				// Pick a random location.
				const auto s_Location = s_Locations[rand() % s_Locations.size()];

				Log("Selected starting location for level %s: %s\n", s_Level.c_str(), s_Location.Name.c_str());

				// Try to get the actor with the given ID, and change hitman's outfit to theirs.
				const auto s_Actor = (*g_Module->Pointers()->g_pGameData)->m_aActors[s_Location.Outfit];

				if (s_Actor)
				{
					s_Actor->EnablePickupClothes();

					if (auto s_HitmanAs = s_Actor->GetHitmanAs())
					{
						if (auto s_HitmanAsPtr = reinterpret_cast<ZHM3HmAs*>(g_Module->Functions()->ZGEOM_RefToPtr(s_HitmanAs)))
						{
							g_Module->Functions()->ZHitman3_ChangeIntoNewClothes(s_Hitman, s_HitmanAsPtr, nullptr, false, nullptr, 0);
							auto s_Msg = (*g_Module->Pointers()->g_pSysInterface)->m_pEngineDb->RegisterZMsg("Hitman_ChangedClothes", 0, nullptr, 0);
							(*g_Module->Pointers()->ZLIST__m_TrackLinkObjectsInstance)->SendCommandRecursive(s_Msg, nullptr, nullptr);
						}
					}
				}

				// Update Hitman's position.
				s_Hitman->m_pBaseGeom->m_pParent->m_mMat = s_Location.Rotation;
				s_Hitman->m_pBaseGeom->m_pParent->m_vPos = s_Location.Position;
			}
		}
	}

	/*for (int i = 0; i < (*g_Module->Pointers()->g_pGameData)->m_nActorCount; ++i)
	{
		auto s_Actor = (*g_Module->Pointers()->g_pGameData)->m_aActors[i];

		if (s_Actor)
		{
			s_Actor->EnablePickupClothes();
		}
	}*/

	return o_ZHM3LevelControl_FrameUpdate(th);
}