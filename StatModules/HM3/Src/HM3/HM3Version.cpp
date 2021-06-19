#include "HM3Version.h"

#include <iterator>

struct PossibleVersion
{
	const char* version_string;
	const char* version_addr;
	HM3Version  version;
};

static const PossibleVersion POSSIBLE_VERSIONS[]
{
	{ "blood-build3-20060616-26123", (const char*)0x007562C0, HM3_GOG },
	{ "blood-build3-20060601-26089", (const char*)0x00000000, HM3_STEAM }, // Unknown
};

HM3Version CheckVersion()
{
	for (const PossibleVersion& version : POSSIBLE_VERSIONS)
	{
		if (strcmp(version.version_addr, version.version_string) == 0)
		{
			return version.version;
		}
	}

	return HM3_UNKNOWN;
}
