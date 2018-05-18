#pragma once

#include <stdafx.h>
#include <Hooks.h>

class ZEntityImpl;
class ZVariantRef;

class HM5Hooks
{
public:
	HM5Hooks();
	~HM5Hooks();

protected:
	void Install();
	void Uninstall();

public:
	DECLARE_FASTCALL_HOOK(void, ZEntityImpl_SignalOutputPin, ZEntityImpl* th, int32_t nPinID, ZVariantRef* data);

private:
	bool m_Installed;
};