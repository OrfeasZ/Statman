#include <HM3/HM3Hooks.h>
#include <HM3/HM3Module.h>
#include <HM3/HM3Pointers.h>
#include <HM3/Structs/HM3Stats.h>

#include <tuple>

#include <D3dx9core.h>
#pragma comment(lib, "d3dx9")

static const double m_Multipliers[] = {
	0.0, 1.0, 1.5, 2.0, 2.5, 3.0, 3.25, 3.5, 3.75, 4.0, 4.1300001, 4.25, 4.3800001, 4.5, 4.6300001, 4.75,
	4.8800001, 5.0, 5.0599999, 5.1300001, 5.1900001, 5.25, 5.3099999, 5.3800001, 5.4400001, 5.5, 5.5599999,
	5.6300001, 5.6900001, 5.75, 5.8099999, 5.8800001, 5.9400001, 6.0
};

uint32_t CalculateRating0() {
	const auto* s_Stats = g_Module->Pointers()->m_Stats;

	double s_Rating0 = 0.0;

	// Innocents Killed
	int s_InnocentsKilled = s_Stats->m_InnocentsKilled >= 34 ? 33 : s_Stats->m_InnocentsKilled;
	s_Rating0 += m_Multipliers[s_InnocentsKilled] * 12.0;

	// Innocents Wounded
	int s_InnocentsWounded = s_Stats->m_InnocentsWounded >= 34 ? 33 : s_Stats->m_InnocentsWounded;
	s_Rating0 += m_Multipliers[s_InnocentsWounded] * 6.0;

	// Enemies Killed
	int s_EnemiesKilled = s_Stats->m_EnemiesKilled >= 34 ? 33 : s_Stats->m_EnemiesKilled;
	s_Rating0 += m_Multipliers[s_EnemiesKilled] * 6.0;

	// Enemies Wounded
	int s_EnemiesWounded = s_Stats->m_EnemiesWounded >= 34 ? 33 : s_Stats->m_EnemiesWounded;
	s_Rating0 += m_Multipliers[s_EnemiesWounded] * 3.0;

	// Policemen Killed
	int s_PoliceMenKilled = s_Stats->m_PoliceMenKilled >= 34 ? 33 : s_Stats->m_PoliceMenKilled;
	s_Rating0 += m_Multipliers[s_PoliceMenKilled] * 9.0;

	// Policemen Wounded
	int s_PoliceMenWounded = s_Stats->m_PoliceMenWounded >= 34 ? 33 : s_Stats->m_PoliceMenWounded;
	s_Rating0 += m_Multipliers[s_PoliceMenWounded] * 5.0;

	// Max Rating is 100
	s_Rating0 = s_Rating0 > 100.0 ? 100.0 : s_Rating0;

	return static_cast<uint32_t>(ceil((round(s_Rating0) / 100.0) * 6.0));
}

uint32_t CalculateRating1() {
	const auto* s_Stats = g_Module->Pointers()->m_Stats;
	const auto* s_Class03 = *g_Module->Pointers()->m_class03Ptr;

	double s_Rating1 = 0.0;

	// Frisk Failed
	int s_FriskFailed = s_Stats->m_FriskFailed >= 34 ? 33 : s_Stats->m_FriskFailed;
	s_Rating1 += m_Multipliers[s_FriskFailed] * 6.0;

	// Covers Blown
	int s_CoverBlown = s_Stats->m_CoverBlown >= 34 ? 33 : s_Stats->m_CoverBlown;
	s_Rating1 += m_Multipliers[s_CoverBlown] * 6.0;

	// Bodies Found
	int s_BodiesFound;
	if (s_Class03->m_Difficulty <= 1)
		s_BodiesFound = s_Stats->m_BodiesFound >= 34 ? 33 : s_Stats->m_BodiesFound;
	else
		s_BodiesFound = (s_Stats->m_BodiesFound + s_Stats->m_TargetBodiesFound) >= 34 ? 33 : (s_Stats->m_BodiesFound + s_Stats->m_TargetBodiesFound);

	s_Rating1 += m_Multipliers[s_BodiesFound] * 6.0;

	// Unconscious Bodies Found
	int s_UnconsciousBodiesFound = s_Stats->m_UnconsciousBodiesFound >= 34 ? 33 : s_Stats->m_UnconsciousBodiesFound;
	s_Rating1 += m_Multipliers[s_UnconsciousBodiesFound] * 6.0;

	// Witnesses
	int s_Witnesses = s_Stats->m_Witnesses >= 34 ? 33 : s_Stats->m_Witnesses;
	s_Rating1 += m_Multipliers[s_Witnesses] * 8.0;

	// Caught on Camera
	int s_CameraCaught = s_Stats->m_CameraCaught >= 34 ? 33 : s_Stats->m_CameraCaught;
	s_Rating1 += m_Multipliers[s_CameraCaught] * 10.0;

	// Items Left
	if (s_Class03->m_Difficulty == 3)
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
	const auto* s_Stats = g_Module->Pointers()->m_Stats;
	const auto* s_Class03 = *g_Module->Pointers()->m_class03Ptr;

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

	if (s_Class03->m_Difficulty <= 1) {
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

	if (s_Class03->m_Difficulty == 3) {
		if (s_Stats->m_CustomWeaponsLeftOnLevel > 0 || s_Stats->m_SuitLeftOnLevel > 0) {
			s_Issues += " | Items Left";
		}
	}

	return s_Issues.substr(3);
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

	static D3DCOLOR s_White = D3DCOLOR_RGBA(255, 255, 255, 255);
	static D3DCOLOR s_Green = D3DCOLOR_RGBA(0, 255, 0, 255);
	static D3DCOLOR s_Red = D3DCOLOR_RGBA(255, 0, 0, 255);
	static D3DCOLOR s_Orange = D3DCOLOR_RGBA(255, 140, 0, 255);
	static D3DCOLOR s_Shadow = D3DCOLOR_RGBA(0, 0, 0, 200);

	static char s_TimeBuffer[20]{};

	const auto c_LeftOffset = 132;
	const auto s_BottomOffset = 100;

	if (!s_Font) {
		const auto s_Result = D3DXCreateFont(th, 20, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &s_Font);

		if (FAILED(s_Result)) {
			Log("Could not create font with error %x. Overlay won't work.\n", s_Result);
		}
		else {
			D3DVIEWPORT9 s_Viewport{};
			th->GetViewport(&s_Viewport);

			Log("Viewport is %d x %d.\n", s_Viewport.Width, s_Viewport.Height);

			SetRect(&s_TimerRect, c_LeftOffset, s_Viewport.Height - s_BottomOffset, 0, 0);
			SetRect(&s_TimerRectShadow, c_LeftOffset + 2, s_Viewport.Height - s_BottomOffset + 2, 0, 0);

			SetRect(&s_RatingRect, c_LeftOffset, s_Viewport.Height - s_BottomOffset + 20, 0, 0);
			SetRect(&s_RatingRectShadow, c_LeftOffset + 2, s_Viewport.Height - s_BottomOffset + 22, 0, 0);

			SetRect(&s_IssuesRect, c_LeftOffset, s_Viewport.Height - s_BottomOffset + 40, 0, 0);
			SetRect(&s_IssuesRectShadow, c_LeftOffset + 2, s_Viewport.Height - s_BottomOffset + 42, 0, 0);

			Log("Overlay is set up!\n");
		}
	}

	if (s_Font) {
		// Render the timer.
		const auto s_CurrentTimeSeconds = (g_Module->Pointers()->m_Time && *g_Module->Pointers()->m_Time)
			? static_cast<double>((*g_Module->Pointers()->m_Time)->m_Ticks) * 0.0009765625
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
	}

	return o_IDirect3DDevice9__EndScene(th);
}