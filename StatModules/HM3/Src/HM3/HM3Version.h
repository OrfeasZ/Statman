#ifndef HM3VERSION_H
#define HM3VERSION_H

enum HM3Version
{
	HM3_UNKNOWN = 0,
	HM3_STEAM,
	HM3_GOG
};

HM3Version CheckVersion();

#endif
