#pragma once

#include <stdafx.h>
#include <Hooks.h>

class ZEntityType;
class ZVariantRef;

class HM5Hooks
{
public:
	HM5Hooks();
	~HM5Hooks();

protected:
	bool Install();
	void Uninstall();

public:
	DECLARE_FASTCALL_HOOK(void, SignalOutputPin, ZEntityType** entity, int32_t pin, ZVariantRef* data);

private:
	bool m_Installed;
};