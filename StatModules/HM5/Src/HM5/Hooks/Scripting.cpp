#include <HM5/HM5Hooks.h>
#include <HM5/HM5Module.h>
#include <HM5/HM5PinHandler.h>

DECLARE_FASTCALL_DETOUR(HM5Hooks, void, SignalOutputPin, ZEntityType** entity, int32_t pin, ZVariantRef* data)
{
	if (!g_Module->PinHandler())
		return o_SignalOutputPin(entity, pin, data);

	if (!g_Module->PinHandler()->OnOutputPinSignal(entity, pin, data))
		return;

	o_SignalOutputPin(entity, pin, data);
}