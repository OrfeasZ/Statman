#include <HM3/HM3Hooks.h>

#include <HM3/Structs/UnknownClass02.h>

HM3Hooks::UnknownClass02_NextDetectionNPC_t HM3Hooks::UnknownClass02_NextDetectionNPC = nullptr;

int __fastcall HM3Hooks::c_UnknownClass02_NextDetectionNPC(UnknownClass02* th, int, DetectionIterator* a2)
{
	Log("Test %p %p\n", th, a2);

	int s_RetVal = UnknownClass02_NextDetectionNPC(th, a2);

	Log("Retval: %d\n", s_RetVal);

	return s_RetVal;
}
