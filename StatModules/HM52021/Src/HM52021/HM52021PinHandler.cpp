#include "HM52021PinHandler.h"

#include <HM52021/Structs/ZObject.h>
#include <HM52021/Structs/Reflection.h>
#include <HM52021/Structs/ZEntity.h>

HM52021PinHandler::HM52021PinHandler()
{

}

bool HM52021PinHandler::OnOutputPinSignal(ZEntityType** p_Entity, int32_t p_Pin, ZVariantRef* p_Ref)
{
	return true;
	
	/*switch (p_Pin)
	{
	case 0x7AE10CED: // Spotted
	case 0x1B1FBAA8: // BodyFound
	case 0xCBF43926: // BodyFoundAccident
	case 0xAC6EDBD9: // BodyFoundMurder
	case 0xDAC4D23C: // BodyFoundPacify
	case 0x1C0FC600: // OnBodyFound
	case 0x74F2ABDC: // DetectedKill
	case 0xA71BF957: // Kill
	case 0x5F9DC29C: // OnCameraDestroyed
	case 0xF4EEAFA7: // OnHandleBreakRecorder
	case 0x633F93F5: // OnHandleDisableCamera
	case 0x9FA855B4: // OnRecorded
	case 0xE4A6AB59: // DeadBodySeenAccident
	case 0x84B97ADA: // DeadBodySeenMurder
	case 0xF79C1A3D: // OnBodyNoticed
	{
		std::string s_ValueStr = p_Ref->m_pTypeID->typeInfo()->m_pTypeName;

		if (s_ValueStr == "ZDynamicObject")
		{
			ZDynamicObject* s_Object = reinterpret_cast<ZDynamicObject*>(p_Ref->m_pData);

			ZString s_ObjectStr;
			s_Object->ToString(s_Object, &s_ObjectStr);

			s_ValueStr = s_ObjectStr.c_str();
		}

		auto it = m_PinRegistry.find(p_Pin);

		if (it == m_PinRegistry.end())
		{		
			Log("Unknown Pin [0x%08X] => %s\n",
				p_Pin,
				s_ValueStr.c_str()
			);
		}
		else
		{
			Log("Pin [%s] => %s\n",
				it->second.c_str(),
				s_ValueStr.c_str()
			);
		}

		break;
	}
	}*/

	std::string s_ValueStr = p_Ref->m_pTypeID->typeInfo()->m_pTypeName;

	if (s_ValueStr == "ZDynamicObject")
	{
		ZDynamicObject* s_Object = reinterpret_cast<ZDynamicObject*>(p_Ref->m_pData);

		ZString s_ObjectStr;
		s_Object->ToString(s_Object, &s_ObjectStr);

		s_ValueStr = s_ObjectStr.c_str();
	}

	auto it = m_PinRegistry.find(p_Pin);

	if (it == m_PinRegistry.end())
	{
		Log("Unknown Pin [0x%p::0x%08X] => %s\n",
			*p_Entity,
			p_Pin,
			s_ValueStr.c_str()
		);
	}
	else
	{
		Log("Pin [0x%p::%s] => %s\n",
			*p_Entity,
			it->second.c_str(),
			s_ValueStr.c_str()
		);
	}

	if ((*p_Entity)->m_pProperties01)
	{
		for (auto& s_Property : *(*p_Entity)->m_pProperties01)
		{
			Log("{p1} [%p] [%p] type: %s, id: %x\n", &s_Property, s_Property.m_pType, s_Property.m_pType->getPropertyInfo()->m_pType->typeInfo()->m_pTypeName, s_Property.m_nPropertyId);
		}
	}

	if ((*p_Entity)->m_pProperties02)
	{
		for (auto& s_Property : *(*p_Entity)->m_pProperties02)
		{
			//Log("{p2} [%p] [%p] type: %s, id: %x\n", &s_Property, s_Property.m_pType, s_Property.m_pType->m_pTypeId->typeInfo()->m_pTypeName, s_Property.m_nPropertyId);
		}
	}

	/*if ((*p_Entity)->m_pInterfaces)
	{
		for (auto& s_Interface : *(*p_Entity)->m_pInterfaces)
		{
			Log("{i1} type: %s\n", s_Interface.m_pTypeId->typeInfo()->m_pTypeName);
		}
	}*/

	return true;
}