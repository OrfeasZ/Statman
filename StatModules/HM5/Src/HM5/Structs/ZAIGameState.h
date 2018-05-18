#pragma once

#include <stdafx.h>

class ZEntityType;
class ZActor;

struct ZEntityRef
{
	ZEntityType** m_pObj;
};

template <typename T>
class TEntityRef
{
public:
	ZEntityRef m_entityRef;
	T* m_pInterfaceRef;
};

struct SClosestActorInfo
{
	TEntityRef<ZActor> m_pMaxFacingAlertableActor; // 0
	TEntityRef<ZActor> m_pClosestAlertableActor;  // 16
	TEntityRef<ZActor> m_pClosestAlertableGuard; // 32
	TEntityRef<ZActor> m_p_ClosestEngagedActor; // 48
	float maxFacingAlertableActor; // 64
	float distanceToAltertableActor; // 68
	float distanceToAlertableGuard; // 72
	float distanceToEngagedActor; // 76
};

class ZGuid
{
public:
	union
	{
		struct
		{
			uint32_t _a;
			uint16_t _b;
			uint16_t _c;
			uint8_t _d;
			uint8_t _e;
			uint8_t _f;
			uint8_t _g;
			uint8_t _h;
			uint8_t _i;
			uint8_t _j;
			uint8_t _k;
		};

		struct
		{
			uint64_t m_nHigh;
			uint64_t m_nLow;
		};
	};

};

class ZRepositoryID :
	public ZGuid
{
};

enum class EGameTension : int32_t
{
	EGT_Undefined,
	EGT_Ambient,
	EGT_Agitated,
	EGT_Searching,
	EGT_AlertedLow,
	EGT_AlertedHigh,
	EGT_Hunting,
	EGT_Arrest,
	EGT_Combat
};

struct STokenID
{
	uint32_t m_iValue;
	bool m_bValid;
};

struct SActorCounts
{
	int enemiesIsAlerted; // 124
	int enemiesIsAlertedArmed; // 128
	int enemiesIsEngaged; // 132
	int lastEnemyKilled; // 136
	int enemiesInCombat; // 140
	int alertableActorOnScreen; // 144
	int alertableGuardOnScreen; // 148
};

struct ZGameTime
{
	int64_t m_nTicks;
};

class ZAIGameState
{
public:
	SClosestActorInfo m_ActorInfo; // 0
	float m_fDisguiseHealth; // 80
	STokenID m_outfitToken; // 88
	PAD(32); // 96
	SActorCounts m_ActorCounts; // 124
	EGameTension m_eGameTensionMax; // 152
	EGameTension m_eGameTensionGuard; // 156
	EGameTension m_eGameTensionCivilian; // 160
	EGameTension m_eGameTensionToHitmanGuard; // 164
	EGameTension m_eGameTensionToHitmanCivilian; // 168
	int m_nAliveEnemyCount; // 172
	int m_nAliveGuardCount; // 176
	ZGameTime m_nLastBulletFlyByEventTime; // 184
	float m_fAttentionMax; // 192
	float m_fAttentionMaxPan; // 196
	float m_fAudibleAttentionMax; // 200
	float m_fAudibleAttentionMaxPan; // 204
	float m_fSecurityCameraAttentionMax; // 208
	float m_fSecurityCameraAttentionMaxPan; // 212
	float m_fTrespassingAttentionMax; // 216
	float m_fTrespassingAttentionMaxPan; // 220
	PAD(8); // 224
	float m_fDisguiseAttentionMax; // 232
	float m_fDisguiseAttentionMaxPan; // 236
	PAD(40); // 240

	// Closet, Broken, Trespassing, Deep Trespassing, Accident Body Found is Murdered
	// Non-target kills, no noticed kills, no accident bodies found, no suspicious disguise, no camera

	union
	{
		uint8_t unionInt00; // 280

		struct
		{
			bool m_bDisguiseBroken : 1; // & 1 (>> 0)
			bool m_bDisguiseSuspicious : 1; // & 2 (>> 1)
			bool m_bInDisguise : 1; // & 4 (>> 2)
			bool m_bUnk03 : 1; // & 8 (>> 3)
			bool m_bBulletFlyByHitman: 1; // & 0x10 (>> 4)
			bool m_bStealthKill : 1; // & 0x20 (>> 5)
			bool m_bUnk06 : 1; // & 0x40 (>> 6)
			bool m_bTrespassing : 1; // & 0x80 (>> 7)
		};
	};

	union
	{
		uint8_t unionInt01; // 281

		struct
		{
			bool m_bDeepTrespassing : 1; // & 1 (>> 0)
			bool m_bHitmanTrespassingSpotted : 1; // & 2 (>> 1)
			bool m_bUnk10 : 1; // & 4 (>> 2)
			bool m_bUnk11 : 1; // & 8 (>> 3)
			bool m_bUnk12 : 1; // & 0x10 (>> 4)
			bool m_bUnk13 : 1; // & 0x20 (>> 5)
			bool m_bUnk14 : 1; // & 0x40 (>> 6)
			bool m_bUnk15 : 1; // & 0x80 (>> 7)
		};
	};

	union
	{
		uint8_t unionInt02; // 282

		struct
		{
			bool m_bBodyFoundMurder : 1; // & 1 (>> 0)
			bool m_bBodyFoundPacify : 1; // & 2 (>> 1)
			bool m_bBodyFoundAccident : 1; // & 4 (>> 2)
			bool m_bBloodPoolFound : 1; // & 8 (>> 3)
			bool m_bCanOpenCPDoor : 1; // & 0x10 (>> 4)
			bool m_bUnk21 : 1; // & 0x20 (>> 5)
			bool m_bSpottedEnteringCloset: 1; // & 0x40 (>> 6)
			bool m_bUnk23 : 1; // & 0x80 (>> 7)
		};
	};

	union
	{
		uint8_t unionInt03; // 283

		struct
		{
			bool m_bBeingFrisked : 1; // & 1 (>> 0)
			bool m_bFriskSuccess: 1; // & 2 (>> 1)
			bool m_bFriskFailed: 1; // & 4 (>> 2)
			bool m_bUnk27 : 1; // & 8 (>> 3)
			bool m_bHitmanInVision : 1; // & 0x10 (>> 4)
			bool m_bNPCHasWhiteDot : 1; // & 0x20 (>> 5)
			bool m_bNPCHasExclamationMark : 1; // & 0x40 (>> 6)
			bool m_bNPCHasQuestionMark : 1; // & 0x80 (>> 7)
		};
	};

	union
	{
		uint8_t unionInt04; // 284

		struct
		{
			bool m_bDisguiseBeingInvestigated : 1; // & 1 (>> 0)
			bool m_bDeadBodySeenAccident : 1; // & 2 (>> 1)
			bool m_bDeadBodySeenMurder : 1; // & 4 (>> 2)
			bool m_bUnk35 : 1; // & 8 (>> 3)
			bool m_bUnk36 : 1; // & 0x10 (>> 4)
			bool m_bUnk37 : 1; // & 0x20 (>> 5)
			bool m_bUnk38 : 1; // & 0x40 (>> 6)
			bool m_bUnk39 : 1; // & 0x80 (>> 7)
		};
	};
};

class ZGameStatsManager
{
public:
	PAD(128);
	ZAIGameState m_GameState; // 128
	ZAIGameState m_OldGameState; // 416
};