#include "pch.h"

namespace WowFunctions
{
	uintptr_t GetLocalPlayerBase()
	{
		const auto guid = reinterpret_cast<int64_t(__cdecl*)()>(WowAddresses::ClntObjMgrGetActivePlayer)();
		return guid? reinterpret_cast<uintptr_t(__cdecl*)(int64_t, int32_t)>(WowAddresses::ClntObjMgrObjectPtr)(guid, 16) : 0;
	}

	int32_t RunLua(const char* luaString)
	{
		return reinterpret_cast<int32_t(__cdecl*)(const char*, const char*, int32_t a3)>(WowAddresses::FrameScriptExecute)(luaString, luaString, 0);
	}

	int32_t RegisterFunction(const char* luaName, const uintptr_t theFunction)
	{
		const auto textSectionEnd = *reinterpret_cast<uint32_t*>(WowAddresses::TextSectionEnd);

		if (theFunction >= textSectionEnd)
		{
			const auto dif = theFunction - textSectionEnd;
			*reinterpret_cast<uint32_t*>(WowAddresses::TextSectionEnd) = textSectionEnd + dif + 1;
		}

		return reinterpret_cast<int32_t(__cdecl*)(const char*, uintptr_t)>(WowAddresses::FrameScriptRegister)(luaName, theFunction);
	}

	int32_t UpdateModel(const uintptr_t unit)
	{
		return reinterpret_cast<int32_t(__thiscall*)(uintptr_t, int32_t)>(WowAddresses::UpdateDisplayInfo)(unit, 1);
	}
}