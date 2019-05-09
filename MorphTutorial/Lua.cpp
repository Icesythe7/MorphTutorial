#include "pch.h"

namespace Lua
{
	/// <summary>
	/// Returns the number of params for the lua function that was called.
	/// </summary>
	/// <param name="luaState">The luaState.</param>
	/// <returns>The number of params.</returns>
	int32_t GetTop(const uintptr_t luaState)
	{
		return reinterpret_cast<int32_t(__cdecl*)(uintptr_t)>(WowAddresses::LuaGetState)(luaState);
	}

	/// <summary>
	/// Returns a boolean if the specified element can be converted to a string.
	/// </summary>
	/// <param name="luaState">The luaState.</param>
	/// <param name="stackPos">The position of the element to check on the stack.</param>
	/// <returns>True if the specified stack element can be converted to a string.</returns>
	bool IsString(const uintptr_t luaState, const int32_t stackPos)
	{
		return reinterpret_cast<bool(__cdecl*)(uintptr_t, int32_t)>(WowAddresses::LuaIsString)(luaState, stackPos);
	}

	/// <summary>
	/// Converts the specified element in lua to a const char*.
	/// </summary>
	/// <param name="luaState">The luaState.</param>
	/// <param name="stackPos">The position of the element to check on the stack.</param>
	/// <returns>A const char* of the lua string.</returns>
	const char* ToString(const uintptr_t luaState, const int32_t stackPos)
	{
		return reinterpret_cast<const char*(__cdecl*)(uintptr_t, int32_t, DWORD*)>(WowAddresses::LuaToString)(luaState, stackPos, nullptr);
	}

	/// <summary>
	/// Returns a boolean if the specified element can be converted to a number.
	/// </summary>
	/// <param name="luaState">The luaState.</param>
	/// <param name="stackPos">The position of the element to check on the stack.</param>
	/// <returns>True if the specified stack element can be converted to a number.</returns>
	bool IsNumber(const uintptr_t luaState, const int32_t stackPos)
	{
		return reinterpret_cast<bool(__cdecl*)(uintptr_t, int32_t)>(WowAddresses::LuaIsNumber)(luaState, stackPos);
	}

	/// <summary>
	/// Converts the specified element in lua to a double.
	/// </summary>
	/// <param name="luaState">The luaSate.</param>
	/// <param name="stackPos">The position of the element to check on the stack.</param>
	/// <returns>A double of the lua number.</returns>
	double ToNumber(const uintptr_t luaState, const int32_t stackPos)
	{
		return reinterpret_cast<double(__cdecl*)(uintptr_t, int32_t)>(WowAddresses::LuaToNumber)(luaState, stackPos);
	}

	/// <summary>
	/// Throws an error in lua.
	/// </summary>
	/// <param name="luaState">The luaState.</param>
	/// <param name="msg">The error message to display.</param>
	void Error(const uintptr_t luaState, const char* msg)
	{
		reinterpret_cast<void(__cdecl*)(uintptr_t, const char*, int32_t)>(WowAddresses::LuaError)(luaState, msg, 0);
	}

	/// <summary>
	/// Helper function to compare two strings.
	/// </summary>
	/// <param name="string1">The first string.</param>
	/// <param name="string2">The second string.</param>
	/// <returns>True if both strings are an exact match.</returns>
	bool CompareStrings(const char* string1, const char* string2)
	{
		return strcmp(string1, string2) == 0;
	}

	/// <summary>
	/// Updates the model of the unit specified in lua.
	/// </summary>
	/// <param name="l">The luaState passed by lua when called.</param>
	/// <returns>The number of return values passed to the lua function from C++.</returns>
	int64_t UpdateModel(const uintptr_t l)
	{
		const auto numArgs = GetTop(l);
		auto errorMsg = "Incorrect number of arguments for [UpdateModel(string unit)]";

		if (numArgs == 1
			&& (errorMsg = "Incorrect parameter(1) type [string expected for unit]", IsString(l, 1)))
		{
			const auto command = ToString(l, 1);
			if (CompareStrings(command, "player"))
			{
				const auto localPlayer = WowFunctions::GetLocalPlayerBase();
				if (localPlayer)
				{
					WowFunctions::UpdateModel(localPlayer);
					return 0;
				}
				errorMsg = "Invalid unit (nil) [UpdateModel(string unit)]";
			}
			else
				errorMsg = "Invalid command entered for [UpdateModel(string unit)]";
		}
		Error(l, errorMsg);
		return 0;
	}

	/// <summary>
	/// Sets the item ids for the specified unit and slot.
	/// </summary>
	/// <param name="l">The luaState passed by lua when called.</param>
	/// <returns>The number of return values passed to the lua function from C++.</returns>
	int64_t SetVisibleItem(const uintptr_t l)
	{
		const auto numArgs = GetTop(l);
		auto errorMsg = "Incorrect number of arguments for [SetVisibleItem(string unit, int slotId, int itemId)]";

		if (numArgs == 3
			&& (errorMsg = "Incorrect parameter(1) type [string expected for unit]", IsString(l, 1))
			&& (errorMsg = "Incorrect parameter(2) type [int expected for slotId]", IsNumber(l, 2))
			&& (errorMsg = "Incorrect parameter(3) type [int expected for itemId]", IsNumber(l, 3)))
		{
			const auto command = ToString(l, 1);
			if (CompareStrings(command, "player"))
			{
				const auto slotId = static_cast<int32_t>(ToNumber(l, 2));
				const auto itemId = static_cast<int32_t>(ToNumber(l, 3));
				const auto localPlayer = reinterpret_cast<WowAddresses::Unit*>(WowFunctions::GetLocalPlayerBase());
				if (localPlayer)
				{
					switch (slotId)
					{
					case 1: { localPlayer->head = itemId; return 0; }
					case 3: { localPlayer->shoulders = itemId; return 0; }
					case 4: { localPlayer->shirt = itemId; return 0; }
					case 5: { localPlayer->chest = itemId; return 0; }
					case 6: { localPlayer->belt = itemId; return 0; }
					case 7: { localPlayer->legs = itemId; return 0; }
					case 8: { localPlayer->feet = itemId; return 0; }
					case 9: { localPlayer->wrist = itemId; return 0; }
					case 10: { localPlayer->hands = itemId; return 0; }
					case 15: { localPlayer->back = itemId; return 0; }
					case 16: { localPlayer->main_hand = itemId; return 0; }
					case 17: { localPlayer->off_hand = itemId; return 0; }
					case 18: { localPlayer->ranged = itemId; return 0; }
					case 19: { localPlayer->tabard = itemId; return 0; }
					default: { errorMsg = "Invalid slotId entered for [SetVisibleItem(string unit, int slotId, int itemId)]"; }
					}
				}
				else
					errorMsg = "Invalid unit (nil) [SetVisibleItem(string unit, int slotId, int itemId)]";
			}
			else
				errorMsg = "Invalid command entered for [SetVisibleItem(string unit, int slotId, int itemId)]";
		}
		Error(l, errorMsg);
		return 0;
	}
}