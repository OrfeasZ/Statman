#include "HM5PinHandler.h"

#include <HM5/Structs/ZObject.h>
#include <HM5/Structs/Reflection.h>

HM5PinHandler::HM5PinHandler()
{

}

bool HM5PinHandler::OnOutputPinSignal(int32_t p_Pin, ZVariantRef* p_Ref)
{
	auto it = m_PinRegistry.find(p_Pin);

	if (it == m_PinRegistry.end())
	{
		Log("Unknown Pin [%x]: %s %x %x\n",
			p_Pin,
			p_Ref->m_TypeID->m_pType->m_pTypeName,
			p_Ref->m_TypeID->m_nTypeNum,
			p_Ref->m_TypeID->m_pType->m_nTypeInfoFlags
		);

		return true;
	}

	Log("Pin [%s]: %s %x %x\n",
		it->second.c_str(),
		p_Ref->m_TypeID->m_pType->m_pTypeName,
		p_Ref->m_TypeID->m_nTypeNum,
		p_Ref->m_TypeID->m_pType->m_nTypeInfoFlags
	);

	return true;
}