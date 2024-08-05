#pragma once

#include <cstddef>
#include <stdafx.h>

#include "Structs/ZHM3Actor.h"

class ZRender;
class HM3Stats;
class ZSysInterface;
class ZHM3GameData;
class ZSWScene;
enum ALLOCSEQUENCESTATUS : uint32_t;
struct SGeomTypeCount;


class ZEngineDataBase : public ZSerializable
{
public:
	virtual void InitAllocSequencePercent(ZSWScene *,bool) = 0;
	virtual void EndAllocSequencePercent(ZSWScene *) = 0;
	virtual void SetAllocSequencePercent(ALLOCSEQUENCESTATUS,char const*,float) = 0;
	virtual void SoundUpdate() = 0;
	virtual void MainLoop(bool) = 0;
	virtual void GetSceneName() = 0;
	virtual void AllocRootGroup() = 0;
	virtual void AllocSequence(ZSWScene *) = 0;
	virtual void ForceExtraGeom() = 0;
	virtual void CountNrGeoms(uint32_t &,uint32_t &,SGeomTypeCount *,uint32_t) = 0;
	virtual void DeleteAllGeoms() = 0;
	virtual void LoadBoundTrees() = 0;
	virtual void CreateBoundTrees() = 0;
	virtual void CreateRoomTrees() = 0;
	virtual void LoadRoomTrees() = 0;
	virtual void CreateSoundGraph() = 0;
	virtual void LoadSoundGraph() = 0;
	virtual void RegisterZDefine(char const*,char *,int) = 0;
	virtual uint16_t RegisterZMsg(char const* msg, uint32_t a2, char* file, int line) = 0;
	// TODO: More
};

class ZSysInterface
{
public:
	PAD(0x48)
	uint32_t m_Ticks; // 0x0048
	PAD(0x6c)
	ZEngineDataBase* m_pEngineDb; // 0x00B8
	PAD(0x8c0)
    ZRender* m_pRenderer; //0x097C
};

static_assert(offsetof(ZSysInterface, m_pEngineDb) == 0x00B8, "ZSysInterface->m_pEngineDb");
static_assert(offsetof(ZSysInterface, m_Ticks) == 0x0048, "ZSysInterface->m_Ticks");
static_assert(offsetof(ZSysInterface, m_pRenderer) == 0x097C, "ZSysInterface->m_pRenderer");

class HM3Pointers
{
public:
	HM3Pointers();
	~HM3Pointers();

protected:
	bool Setup();

public:
	HM3Stats* ZHM3LevelControl__m_stats = nullptr;
	ZHM3GameData** g_pGameData = nullptr;
	bool* CConfiguration__m_bCheatsEnabled = nullptr;
	ZSysInterface** g_pSysInterface = nullptr;
	ZGEOM** ZLIST__m_TrackLinkObjectsInstance = nullptr;
};