#include "HM5PinHandler.h"

#include <HM5/Structs/TMap.h>

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
			p_Ref->m_TypeID->pTypeInfo->pszTypeName,
			p_Ref->m_TypeID->typeNum,
			p_Ref->m_TypeID->pTypeInfo->m_nTypeInfoFlags
		);

		return true;
	}

	Log("Pin [%s]: %s %x %x\n",
		it->second.c_str(),
		p_Ref->m_TypeID->pTypeInfo->pszTypeName,
		p_Ref->m_TypeID->typeNum,
		p_Ref->m_TypeID->pTypeInfo->m_nTypeInfoFlags
	);

	return true;
}