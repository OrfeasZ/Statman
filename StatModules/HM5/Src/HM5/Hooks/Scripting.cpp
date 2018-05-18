#include <HM5/HM5Hooks.h>
#include <HM5/HM5Module.h>
#include <HM5/HM5PinHandler.h>

DECLARE_FASTCALL_DETOUR(HM5Hooks, void, ZEntityImpl_SignalOutputPin, ZEntityImpl* th, int32_t nPinID, ZVariantRef* data)
{
	if (!g_Module->PinHandler())
		return o_ZEntityImpl_SignalOutputPin(th, nPinID, data);

	if (!g_Module->PinHandler()->OnOutputPinSignal(nPinID, data))
		return;

	o_ZEntityImpl_SignalOutputPin(th, nPinID, data);
}