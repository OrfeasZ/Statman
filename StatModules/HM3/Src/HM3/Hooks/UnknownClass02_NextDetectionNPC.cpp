#include <HM3/HM3Hooks.h>

#include <HM3/Structs/UnknownClass02.h>

DECLARE_THISCALL_DETOUR(HM3Hooks, int, UnknownClass02_NextDetectionNPC, UnknownClass02* th, DetectionIterator* a2)
{
	Log("Test %p %p\n", th, a2);

	int s_RetVal = o_UnknownClass02_NextDetectionNPC(th, a2);

	Log("Retval: %d\n", s_RetVal);

	return s_RetVal;
}
