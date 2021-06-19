#ifndef HM3VERSION_H
#define HM3VERSION_H

enum HM3Version
{
	HM3_UNKNOWN = 0,
	HM3_STEAM = 1,
	HM3_GOG   = 2
};

HM3Version CheckVersion();

#endif
