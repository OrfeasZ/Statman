#include "HM5PinHandler.h"

#include <HM5/Structs/ZObject.h>
#include <HM5/Structs/Reflection.h>
#include <HM5/Structs/ZEntity.h>

HM5PinHandler::HM5PinHandler()
{

}

bool HM5PinHandler::OnOutputPinSignal(ZEntityType** p_Entity, int32_t p_Pin, ZVariantRef* p_Ref)
{
	return true;

	auto it = m_PinRegistry.find(p_Pin);

	std::string s_EntityName = "UnknownEnt";

	if (p_Entity && *p_Entity)
	{
		//s_EntityName = (*p_Entity.m_pEntity)->m_TypeName.c_str();
	}

	if (it == m_PinRegistry.end())
	{
		Log("Unknown Pin [%x] (%s) => %p\n",
			p_Pin,
			p_Ref->m_pTypeID->typeInfo()->m_pTypeName,
			*p_Entity
		);

		return true;
	}

	Log("Pin [%s] (%s) => %p\n",
		it->second.c_str(),
		p_Ref->m_pTypeID->typeInfo()->m_pTypeName,
		*p_Entity
	);

	return true;
}