#pragma once

#include <stdafx.h>
#include "ZResourceID.h"
#include "Reflection.h"

class IEntitySceneContext :
	public IComponentInterface
{
};

class ZEntitySceneContext :
	public IEntitySceneContext
{
public:
	PAD(0x08);
	ZString m_sceneName; // 0x10
};