#include <HM3/HM3Hooks.h>
#include <HM3/HM3Module.h>
#include <HM3/HM3Pointers.h>
#include <HM3/HM3Functions.h>
#include <HM3/Structs/HM3Stats.h>
#include <HM3/Structs/ZHM3GameData.h>
#include <HM3/Structs/ZRender.h>

#include <tuple>
#include <format>
#include <optional>

#include <D3dx9core.h>
#include <DirectXMath.h>

#include "Structs/ZHM3Actor.h"
#pragma comment(lib, "d3dx9")

using namespace DirectX;

static const double c_Multipliers[] = {
	0.0, 1.0, 1.5, 2.0, 2.5, 3.0, 3.25, 3.5, 3.75, 4.0, 4.1300001, 4.25, 4.3800001, 4.5, 4.6300001, 4.75,
	4.8800001, 5.0, 5.0599999, 5.1300001, 5.1900001, 5.25, 5.3099999, 5.3800001, 5.4400001, 5.5, 5.5599999,
	5.6300001, 5.6900001, 5.75, 5.8099999, 5.8800001, 5.9400001, 6.0
};

uint32_t CalculateRating0() {
	const auto* s_Stats = g_Module->Pointers()->ZHM3LevelControl__m_stats;

	double s_Rating0 = 0.0;

	// Innocents Killed
	int s_InnocentsKilled = s_Stats->m_InnocentsKilled >= 34 ? 33 : s_Stats->m_InnocentsKilled;
	s_Rating0 += c_Multipliers[s_InnocentsKilled] * 12.0;

	// Innocents Wounded
	int s_InnocentsWounded = s_Stats->m_InnocentsWounded >= 34 ? 33 : s_Stats->m_InnocentsWounded;
	s_Rating0 += c_Multipliers[s_InnocentsWounded] * 6.0;

	// Enemies Killed
	int s_EnemiesKilled = s_Stats->m_EnemiesKilled >= 34 ? 33 : s_Stats->m_EnemiesKilled;
	s_Rating0 += c_Multipliers[s_EnemiesKilled] * 6.0;

	// Enemies Wounded
	int s_EnemiesWounded = s_Stats->m_EnemiesWounded >= 34 ? 33 : s_Stats->m_EnemiesWounded;
	s_Rating0 += c_Multipliers[s_EnemiesWounded] * 3.0;

	// Policemen Killed
	int s_PoliceMenKilled = s_Stats->m_PoliceMenKilled >= 34 ? 33 : s_Stats->m_PoliceMenKilled;
	s_Rating0 += c_Multipliers[s_PoliceMenKilled] * 9.0;

	// Policemen Wounded
	int s_PoliceMenWounded = s_Stats->m_PoliceMenWounded >= 34 ? 33 : s_Stats->m_PoliceMenWounded;
	s_Rating0 += c_Multipliers[s_PoliceMenWounded] * 5.0;

	// Max Rating is 100
	s_Rating0 = s_Rating0 > 100.0 ? 100.0 : s_Rating0;

	return static_cast<uint32_t>(ceil((round(s_Rating0) / 100.0) * 6.0));
}

uint32_t CalculateRating1() {
	const auto* s_Stats = g_Module->Pointers()->ZHM3LevelControl__m_stats;
	const auto* s_GameData = *g_Module->Pointers()->g_pGameData;

	double s_Rating1 = 0.0;

	// Frisk Failed
	int s_FriskFailed = s_Stats->m_FriskFailed >= 34 ? 33 : s_Stats->m_FriskFailed;
	s_Rating1 += c_Multipliers[s_FriskFailed] * 6.0;

	// Covers Blown
	int s_CoverBlown = s_Stats->m_CoverBlown >= 34 ? 33 : s_Stats->m_CoverBlown;
	s_Rating1 += c_Multipliers[s_CoverBlown] * 6.0;

	// Bodies Found
	int s_BodiesFound;
	if (s_GameData->m_nDifficulty <= 1)
		s_BodiesFound = s_Stats->m_BodiesFound >= 34 ? 33 : s_Stats->m_BodiesFound;
	else
		s_BodiesFound = (s_Stats->m_BodiesFound + s_Stats->m_TargetBodiesFound) >= 34 ? 33 : (s_Stats->m_BodiesFound + s_Stats->m_TargetBodiesFound);

	s_Rating1 += c_Multipliers[s_BodiesFound] * 6.0;

	// Unconscious Bodies Found
	int s_UnconsciousBodiesFound = s_Stats->m_UnconsciousBodiesFound >= 34 ? 33 : s_Stats->m_UnconsciousBodiesFound;
	s_Rating1 += c_Multipliers[s_UnconsciousBodiesFound] * 6.0;

	// Witnesses
	int s_Witnesses = s_Stats->m_Witnesses >= 34 ? 33 : s_Stats->m_Witnesses;
	s_Rating1 += c_Multipliers[s_Witnesses] * 8.0;

	// Caught on Camera
	int s_CameraCaught = s_Stats->m_CameraCaught >= 34 ? 33 : s_Stats->m_CameraCaught;
	s_Rating1 += c_Multipliers[s_CameraCaught] * 10.0;

	// Items Left
	if (s_GameData->m_nDifficulty == 3)
	{
		if (s_Stats->m_CustomWeaponsLeftOnLevel > 0)
			s_Rating1 += 5.0;

		if (s_Stats->m_SuitLeftOnLevel)
			s_Rating1 += 5.0;
	}

	// Max Rating is 100
	s_Rating1 = s_Rating1 > 100.0 ? 100.0 : s_Rating1;

	return static_cast<uint32_t>(ceil((round(s_Rating1) / 100.0) * 6.0));
}

std::tuple<bool, const char*> GetRating() {
	const auto s_Rating0 = CalculateRating0();
	const auto s_Rating1 = CalculateRating1();
	const auto s_PerfectRating = (s_Rating0 + s_Rating1) == 0;

	if (s_Rating0 == 0 && s_Rating1 == 0) {
		return std::make_tuple(s_PerfectRating, "Silent Assassin");
	}
	else if (s_Rating0 == 0 && s_Rating1 == 1) {
		return std::make_tuple(s_PerfectRating, "Professional");
	}
	else if (s_Rating0 == 0 && s_Rating1 == 2) {
		return std::make_tuple(s_PerfectRating, "Hired Killer");
	}
	else if (s_Rating0 == 0 && s_Rating1 == 3) {
		return std::make_tuple(s_PerfectRating, "Murderer");
	}
	else if (s_Rating0 == 0 && s_Rating1 == 4) {
		return std::make_tuple(s_PerfectRating, "Mugger");
	}
	else if (s_Rating0 == 0 && s_Rating1 == 5) {
		return std::make_tuple(s_PerfectRating, "Messy Murderer");
	}
	else if (s_Rating0 == 0 && s_Rating1 == 6) {
		return std::make_tuple(s_PerfectRating, "Exhibitionist");
	}
	else if (s_Rating0 == 1 && s_Rating1 == 0) {
		return std::make_tuple(s_PerfectRating, "Hitman");
	}
	else if (s_Rating0 == 1 && s_Rating1 == 1) {
		return std::make_tuple(s_PerfectRating, "Specialist");
	}
	else if (s_Rating0 == 1 && s_Rating1 == 2) {
		return std::make_tuple(s_PerfectRating, "Contract Killer");
	}
	else if (s_Rating0 == 1 && s_Rating1 == 3) {
		return std::make_tuple(s_PerfectRating, "Gangster");
	}
	else if (s_Rating0 == 1 && s_Rating1 == 4) {
		return std::make_tuple(s_PerfectRating, "Perpetrator");
	}
	else if (s_Rating0 == 1 && s_Rating1 == 5) {
		return std::make_tuple(s_PerfectRating, "Fierce Offender");
	}
	else if (s_Rating0 == 1 && s_Rating1 == 6) {
		return std::make_tuple(s_PerfectRating, "Clumsy Killer");
	}
	else if (s_Rating0 == 2 && s_Rating1 == 0) {
		return std::make_tuple(s_PerfectRating, "Stalker");
	}
	else if (s_Rating0 == 2 && s_Rating1 == 1) {
		return std::make_tuple(s_PerfectRating, "The Ghost");
	}
	else if (s_Rating0 == 2 && s_Rating1 == 2) {
		return std::make_tuple(s_PerfectRating, "Hoodlum");
	}
	else if (s_Rating0 == 2 && s_Rating1 == 3) {
		return std::make_tuple(s_PerfectRating, "The Cleaner");
	}
	else if (s_Rating0 == 2 && s_Rating1 == 4) {
		return std::make_tuple(s_PerfectRating, "Thug");
	}
	else if (s_Rating0 == 2 && s_Rating1 == 5) {
		return std::make_tuple(s_PerfectRating, "Violent Thug");
	}
	else if (s_Rating0 == 2 && s_Rating1 == 6) {
		return std::make_tuple(s_PerfectRating, "Assailant");
	}
	else if (s_Rating0 == 3 && s_Rating1 == 0) {
		return std::make_tuple(s_PerfectRating, "Shadow Killer");
	}
	else if (s_Rating0 == 3 && s_Rating1 == 1) {
		return std::make_tuple(s_PerfectRating, "Phantom Killer");
	}
	else if (s_Rating0 == 3 && s_Rating1 == 2) {
		return std::make_tuple(s_PerfectRating, "The Eraser");
	}
	else if (s_Rating0 == 3 && s_Rating1 == 3) {
		return std::make_tuple(s_PerfectRating, "Killer");
	}
	else if (s_Rating0 == 3 && s_Rating1 == 4) {
		return std::make_tuple(s_PerfectRating, "Lunatic");
	}
	else if (s_Rating0 == 3 && s_Rating1 == 5) {
		return std::make_tuple(s_PerfectRating, "Madman");
	}
	else if (s_Rating0 == 3 && s_Rating1 == 6) {
		return std::make_tuple(s_PerfectRating, "Maniac");
	}
	else if (s_Rating0 == 4 && s_Rating1 == 0) {
		return std::make_tuple(s_PerfectRating, "Invisible killer");
	}
	else if (s_Rating0 == 4 && s_Rating1 == 1) {
		return std::make_tuple(s_PerfectRating, "The Undertaker");
	}
	else if (s_Rating0 == 4 && s_Rating1 == 2) {
		return std::make_tuple(s_PerfectRating, "Lean Killer");
	}
	else if (s_Rating0 == 4 && s_Rating1 == 3) {
		return std::make_tuple(s_PerfectRating, "Killer");
	}
	else if (s_Rating0 == 4 && s_Rating1 == 4) {
		return std::make_tuple(s_PerfectRating, "Loose Cannon");
	}
	else if (s_Rating0 == 4 && s_Rating1 == 5) {
		return std::make_tuple(s_PerfectRating, "Mad Butcher");
	}
	else if (s_Rating0 == 4 && s_Rating1 == 6) {
		return std::make_tuple(s_PerfectRating, "Berserker");
	}
	else if (s_Rating0 == 5 && s_Rating1 == 0) {
		return std::make_tuple(s_PerfectRating, "Serial Killer");
	}
	else if (s_Rating0 == 5 && s_Rating1 == 1) {
		return std::make_tuple(s_PerfectRating, "Serial Killer");
	}
	else if (s_Rating0 == 5 && s_Rating1 == 2) {
		return std::make_tuple(s_PerfectRating, "Deranged Slayer");
	}
	else if (s_Rating0 == 5 && s_Rating1 == 3) {
		return std::make_tuple(s_PerfectRating, "Terrorist");
	}
	else if (s_Rating0 == 5 && s_Rating1 == 4) {
		return std::make_tuple(s_PerfectRating, "Armed Madman");
	}
	else if (s_Rating0 == 5 && s_Rating1 == 5) {
		return std::make_tuple(s_PerfectRating, "Psychopath");
	}
	else if (s_Rating0 == 5 && s_Rating1 == 6) {
		return std::make_tuple(s_PerfectRating, "Psychopath");
	}
	else if (s_Rating0 == 6 && s_Rating1 == 0) {
		return std::make_tuple(s_PerfectRating, "Sociopath");
	}
	else if (s_Rating0 == 6 && s_Rating1 == 1) {
		return std::make_tuple(s_PerfectRating, "Serial Killer");
	}
	else if (s_Rating0 == 6 && s_Rating1 == 2) {
		return std::make_tuple(s_PerfectRating, "Deranged Slayer");
	}
	else if (s_Rating0 == 6 && s_Rating1 == 3) {
		return std::make_tuple(s_PerfectRating, "Terrorist");
	}
	else if (s_Rating0 == 6 && s_Rating1 == 4) {
		return std::make_tuple(s_PerfectRating, "Psychopath");
	}
	else if (s_Rating0 == 6 && s_Rating1 == 5) {
		return std::make_tuple(s_PerfectRating, "Psychopath");
	}
	else if (s_Rating0 == 6 && s_Rating1 == 6) {
		return std::make_tuple(s_PerfectRating, "Mass Murderer");
	}
	else {
		return std::make_tuple(s_PerfectRating, "No Rating");
	}
}

std::string GetRatingIssues() {
	const auto* s_Stats = g_Module->Pointers()->ZHM3LevelControl__m_stats;
	const auto* s_GameData = *g_Module->Pointers()->g_pGameData;

	std::string s_Issues = "";

	if (s_Stats->m_InnocentsKilled > 0 || s_Stats->m_EnemiesKilled > 0 || s_Stats->m_PoliceMenKilled > 0) {
		s_Issues += " | NPCs Killed";
	}

	if (s_Stats->m_InnocentsWounded > 0 || s_Stats->m_EnemiesWounded > 0 || s_Stats->m_PoliceMenWounded > 0) {
		s_Issues += " | NPCs Wounded";
	}

	if (s_Stats->m_FriskFailed > 0) {
		s_Issues += " | Frisk Failed";
	}

	if (s_Stats->m_CoverBlown > 0) {
		s_Issues += " | Cover Blown";
	}

	if (s_GameData->m_nDifficulty <= 1) {
		if (s_Stats->m_BodiesFound > 0 || s_Stats->m_UnconsciousBodiesFound > 0) {
			s_Issues += " | Bodies Found";
		}
	}
	else {
		if (s_Stats->m_BodiesFound > 0 || s_Stats->m_TargetBodiesFound > 0 || s_Stats->m_UnconsciousBodiesFound > 0) {
			s_Issues += " | Bodies Found";
		}
	}

	if (s_Stats->m_Witnesses > 0) {
		s_Issues += " | Witnesses";
	}

	if (s_GameData->m_nDifficulty == 3) {
		if (s_Stats->m_CustomWeaponsLeftOnLevel > 0 || s_Stats->m_SuitLeftOnLevel > 0) {
			s_Issues += " | Items Left";
		}
	}

	if (s_Issues.size() <= 3) {
		return s_Issues;
	}

	return s_Issues.substr(3);
}

struct SVector2 {
	float x;
	float y;
};

struct SCameraData {
	float FovDegrees;
	float Near;
	float Far;
	float ViewWidth;
	float ViewHeight;
	SMatrix33 RotationMatrix;
	SVector3 Position;
};

std::optional<SVector2> WorldToScreen(const SCameraData& p_Cam, const SVector3& p_Pos) {
	const auto s_Forward = XMVectorSet(p_Cam.RotationMatrix.xAxis.x, p_Cam.RotationMatrix.xAxis.y, p_Cam.RotationMatrix.xAxis.z, 0.0f);
	const auto s_Up = XMVectorSet(p_Cam.RotationMatrix.yAxis.x, p_Cam.RotationMatrix.yAxis.y, p_Cam.RotationMatrix.yAxis.z, 0.0f);
	const auto s_CameraPos = XMVectorSet(p_Cam.Position.x, p_Cam.Position.y, p_Cam.Position.z, 1.0f);

	// Compute the "look at" position by adding the forward direction to the camera position
	const auto s_Target = XMVectorAdd(s_CameraPos, s_Forward);

	// Compute view and projection matrices
	const auto s_View = XMMatrixLookAtLH(s_CameraPos, s_Target, s_Up);

	constexpr auto s_AspectRatio = 1.0f;

	const auto s_Projection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(p_Cam.FovDegrees),
		s_AspectRatio,
		p_Cam.Near,
		p_Cam.Far
	);

	// Transform the world position to view space
	const auto s_WorldPos = XMVectorSet(p_Pos.x, p_Pos.y, p_Pos.z, 1.0f);
	const auto s_ViewPos = XMVector3Transform(s_WorldPos, s_View);

	// Transform the coordinates from view space to clip space
	const auto s_ClipPos = XMVector3Transform(s_ViewPos, s_Projection);

	// Perform perspective division to get NDC
	XMFLOAT4 s_Ndc;
	XMStoreFloat4(&s_Ndc, s_ClipPos);
	if (s_Ndc.w != 0.0f) {
		s_Ndc.x /= s_Ndc.w;
		s_Ndc.y /= s_Ndc.w;
		s_Ndc.z /= s_Ndc.w;
	}

	// Check if the point is within the clip space volume
	if (s_Ndc.x < -1.0f || s_Ndc.x > 1.0f || s_Ndc.y < -1.0f || s_Ndc.y > 1.0f || s_Ndc.z < 0.0f || s_Ndc.z > 1.0f) {
		return std::nullopt;
	}

	// Map NDC to screen space
	SVector2 s_ScreenPos;
	s_ScreenPos.x = ((s_Ndc.x + 1.0f) / 2.0f) * p_Cam.ViewWidth;
	s_ScreenPos.y = ((1.0f - s_Ndc.y) / 2.0f) * p_Cam.ViewHeight;

	return s_ScreenPos;
}

DECLARE_STDCALL_DETOUR(HM3Hooks, HRESULT, IDirect3DDevice9__EndScene, IDirect3DDevice9* th)
{
	static ID3DXFont* s_Font = nullptr;

	static RECT s_TimerRect{};
	static RECT s_TimerRectShadow{};

	static RECT s_RatingRect{};
	static RECT s_RatingRectShadow{};

	static RECT s_IssuesRect{};
	static RECT s_IssuesRectShadow{};

	static RECT s_DebugRect{};
	static RECT s_DebugRectShadow{};
	
	static D3DCOLOR s_White = D3DCOLOR_RGBA(255, 255, 255, 255);
	static D3DCOLOR s_Green = D3DCOLOR_RGBA(0, 255, 0, 255);
	static D3DCOLOR s_Red = D3DCOLOR_RGBA(255, 0, 0, 255);
	static D3DCOLOR s_Orange = D3DCOLOR_RGBA(255, 140, 0, 255);
	static D3DCOLOR s_Shadow = D3DCOLOR_RGBA(0, 0, 0, 200);
	
	static D3DVIEWPORT9 s_Viewport{};

	static char s_TimeBuffer[20]{};

	const auto c_LeftOffset = 132;
	const auto s_BottomOffset = 100;

	if (!g_Module->OverlayEnabled()) {
		return o_IDirect3DDevice9__EndScene(th);
	}

	if (!s_Font) {
		const auto s_Result = D3DXCreateFont(th, 20, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &s_Font);

		if (FAILED(s_Result)) {
			Log("Could not create font with error %x. Overlay won't work.\n", s_Result);
		}
		else {
			th->GetViewport(&s_Viewport);

			Log("Viewport is %d x %d.\n", s_Viewport.Width, s_Viewport.Height);

			SetRect(&s_TimerRect, c_LeftOffset, s_Viewport.Height - s_BottomOffset, 0, 0);
			SetRect(&s_TimerRectShadow, c_LeftOffset + 2, s_Viewport.Height - s_BottomOffset + 2, 0, 0);

			SetRect(&s_RatingRect, c_LeftOffset, s_Viewport.Height - s_BottomOffset + 20, 0, 0);
			SetRect(&s_RatingRectShadow, c_LeftOffset + 2, s_Viewport.Height - s_BottomOffset + 22, 0, 0);

			SetRect(&s_IssuesRect, c_LeftOffset, s_Viewport.Height - s_BottomOffset + 40, 0, 0);
			SetRect(&s_IssuesRectShadow, c_LeftOffset + 2, s_Viewport.Height - s_BottomOffset + 42, 0, 0);

			SetRect(&s_DebugRect, c_LeftOffset, 100, 0, 0);
			SetRect(&s_DebugRectShadow, c_LeftOffset + 2, 102, 0, 0);

			Log("Overlay is set up!\n");
		}
	}

	if (s_Font) {
		// Render the timer.
		const auto s_CurrentTimeSeconds = (g_Module->Pointers()->g_pSysInterface && *g_Module->Pointers()->g_pSysInterface)
			? static_cast<double>((*g_Module->Pointers()->g_pSysInterface)->m_Ticks) * 0.0009765625
			: 0.0f;

		int s_Hours = static_cast<int>(s_CurrentTimeSeconds / 3600);
		int s_Minutes = static_cast<int>((s_CurrentTimeSeconds - (s_Hours * 3600)) / 60);
		double s_Seconds = s_CurrentTimeSeconds - (s_Hours * 3600) - (s_Minutes * 60);
		int s_WholeSeconds = static_cast<int>(s_Seconds);
		int s_Milliseconds = static_cast<int>((s_Seconds - s_WholeSeconds) * 1000);

		sprintf(s_TimeBuffer, "%02d:%02d:%02d.%03d", s_Hours, s_Minutes, s_WholeSeconds, s_Milliseconds);

		s_Font->DrawTextA(nullptr, s_TimeBuffer, -1, &s_TimerRectShadow, DT_LEFT | DT_NOCLIP, s_Shadow);
		s_Font->DrawTextA(nullptr, s_TimeBuffer, -1, &s_TimerRect, DT_LEFT | DT_NOCLIP, s_White);

		// Render the rating.
		const auto s_Rating = GetRating();
		const auto s_PerfectRating = std::get<0>(s_Rating);
		const auto s_RatingText = std::get<1>(s_Rating);

		s_Font->DrawTextA(nullptr, s_RatingText, -1, &s_RatingRectShadow, DT_LEFT | DT_NOCLIP, s_Shadow);
		s_Font->DrawTextA(nullptr, s_RatingText, -1, &s_RatingRect, DT_LEFT | DT_NOCLIP, s_PerfectRating ? s_Green : s_Red);

		if (!s_PerfectRating) {
			const auto s_Issues = GetRatingIssues();

			s_Font->DrawTextA(nullptr, s_Issues.c_str(), -1, &s_IssuesRectShadow, DT_LEFT | DT_NOCLIP, s_Shadow);
			s_Font->DrawTextA(nullptr, s_Issues.c_str(), -1, &s_IssuesRect, DT_LEFT | DT_NOCLIP, s_Orange);
		}

		if (g_Module->Debug2016() && (*g_Module->Pointers()->g_pGameData)->m_pHitman) {
			auto s_Renderer = (*g_Module->Pointers()->g_pSysInterface)->m_pRenderer;
			const auto s_Hitman = (*g_Module->Pointers()->g_pGameData)->m_pHitman;
			auto s_MainCamera = s_Renderer->GetCamera(0);

			std::string s_DebugText;
			
			auto s_HitmanMat = s_Hitman->m_pBaseGeom->m_pParent->m_mMat;
			auto s_HitmanPos = s_Hitman->m_pBaseGeom->m_pParent->m_vPos;

			// Add hitman's position to the debug text.
			s_DebugText += std::format("({:.2f}, {:.2f}, {:.2f}) ", s_HitmanMat.xAxis.x, s_HitmanMat.xAxis.y, s_HitmanMat.xAxis.z);
			s_DebugText += std::format("({:.2f}, {:.2f}, {:.2f}) ", s_HitmanMat.yAxis.x, s_HitmanMat.yAxis.y, s_HitmanMat.yAxis.z);
			s_DebugText += std::format("({:.2f}, {:.2f}, {:.2f}) ", s_HitmanMat.zAxis.x, s_HitmanMat.zAxis.y, s_HitmanMat.zAxis.z);
			s_DebugText += std::format("({:.2f}, {:.2f}, {:.2f}) ", s_HitmanPos.x, s_HitmanPos.y, s_HitmanPos.z);

			// If we have a main camera, render its position and NPCs we can dress as.
			if (s_MainCamera) {
				auto s_CameraPtr = reinterpret_cast<ZCAMERA*>(g_Module->Functions()->ZGEOM_RefToPtr(s_MainCamera));

				const auto s_Mat = s_CameraPtr->m_pBaseGeom->m_mMat;
				const auto s_CameraPos = s_CameraPtr->m_pBaseGeom->m_vPos;

				// Add the camera's position to the debug text.
				s_DebugText += "\n";
				s_DebugText += std::format("({:.2f}, {:.2f}, {:.2f}) ", s_Mat.xAxis.x, s_Mat.xAxis.y, s_Mat.xAxis.z);
				s_DebugText += std::format("({:.2f}, {:.2f}, {:.2f}) ", s_Mat.yAxis.x, s_Mat.yAxis.y, s_Mat.yAxis.z);
				s_DebugText += std::format("({:.2f}, {:.2f}, {:.2f}) ", s_Mat.zAxis.x, s_Mat.zAxis.y, s_Mat.zAxis.z);
				s_DebugText += std::format("({:.2f}, {:.2f}, {:.2f}) ", s_CameraPos.x, s_CameraPos.y, s_CameraPos.z);

				const SCameraData s_CameraData = {
					.FovDegrees = s_CameraPtr->GetFOV(),
					.Near = s_CameraPtr->m_fNear,
					.Far = s_CameraPtr->m_fFar,
					.ViewWidth = static_cast<float>(s_Viewport.Width),
					.ViewHeight = static_cast<float>(s_Viewport.Height),
					.RotationMatrix = s_CameraPtr->m_pBaseGeom->m_mMat,
					.Position = s_CameraPtr->m_pBaseGeom->m_vPos,
				};

				for (uint32_t i = 0; i < (*g_Module->Pointers()->g_pGameData)->m_nActorCount; ++i) {
					const auto s_Actor = (*g_Module->Pointers()->g_pGameData)->m_aActors[i];

					// Only render NPCs we can dress as.
					if (!s_Actor || !s_Actor->GetHitmanAs() || !g_Module->Functions()->ZGEOM_RefToPtr(s_Actor->GetHitmanAs()))
						continue;
					
					const auto s_Pos = s_Actor->m_pBaseGeom->m_pParent->m_vPos;

					// Render the NPC's ID.
					if (const auto s_ScreenCoord = WorldToScreen(s_CameraData, s_Pos)) {
						RECT s_ActorRect{};
						SetRect(&s_ActorRect, s_ScreenCoord->x, s_ScreenCoord->y, 0, 0);
						s_Font->DrawTextA(nullptr, std::to_string(i).c_str(), -1, &s_ActorRect, DT_LEFT | DT_NOCLIP, s_Green);
					}
				}
			}

			// Render the debug text.
			s_Font->DrawTextA(nullptr, s_DebugText.c_str(), -1, &s_DebugRectShadow, DT_LEFT | DT_NOCLIP, s_Shadow);
			s_Font->DrawTextA(nullptr, s_DebugText.c_str(), -1, &s_DebugRect, DT_LEFT | DT_NOCLIP, s_Green);
		}
	}

	return o_IDirect3DDevice9__EndScene(th);
}