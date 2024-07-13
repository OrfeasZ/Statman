#pragma once

enum HM3Version
{
	HM3_UNKNOWN = 0,
	HM3_STEAM,
	HM3_GOG
};

HM3Version CheckVersion();

