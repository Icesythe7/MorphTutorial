#pragma once
#include "pch.h"

namespace  WowAddresses
{
	inline uintptr_t TextSectionEnd = 0xD415BC;
	inline uintptr_t OnIdle = 0x4A8460;
	inline uintptr_t FrameScriptExecute = 0x819210;
	inline uintptr_t FrameScriptRegister = 0x817F90;
	inline uintptr_t ClntObjMgrGetActivePlayer = 0x4D3790;
	inline uintptr_t ClntObjMgrObjectPtr = 0x4D4DB0;
	inline uintptr_t UpdateDisplayInfo = 0x73E410;
	inline uintptr_t LuaGetState = 0x84DBD0;
	inline uintptr_t LuaIsString = 0x84DF60;
	inline uintptr_t LuaToString = 0x84E0E0;
	inline uintptr_t LuaIsNumber = 0x84DF20;
	inline uintptr_t LuaToNumber = 0x84E030;
	inline uintptr_t LuaError = 0x84F280;

	class Unit final
	{
	public:
		char pad_0000[7620]; //0x0000
		int32_t head; //0x1DC4
		char pad_1DC8[4]; //0x1DC8
		int32_t neck; //0x1DCC
		char pad_1DD0[4]; //0x1DD0
		int32_t shoulders; //0x1DD4
		char pad_1DD8[4]; //0x1DD8
		int32_t shirt; //0x1DDC
		char pad_1DE0[4]; //0x1DE0
		int32_t chest; //0x1DE4
		char pad_1DE8[4]; //0x1DE8
		int32_t belt; //0x1DEC
		char pad_1DF0[4]; //0x1DF0
		int32_t legs; //0x1DF4
		char pad_1DF8[4]; //0x1DF8
		int32_t feet; //0x1DFC
		char pad_1E00[4]; //0x1E00
		int32_t wrist; //0x1E04
		char pad_1E08[4]; //0x1E08
		int32_t hands; //0x1E0C
		char pad_1E10[4]; //0x1E10
		int32_t finger_1; //0x1E14
		char pad_1E18[4]; //0x1E18
		int32_t finger_2; //0x1E1C
		char pad_1E20[4]; //0x1E20
		int32_t trinket_1; //0x1E24
		char pad_1E28[4]; //0x1E28
		int32_t trinket_2; //0x1E2C
		char pad_1E30[4]; //0x1E30
		int32_t back; //0x1E34
		char pad_1E38[4]; //0x1E38
		int32_t main_hand; //0x1E3C
		char pad_1E40[4]; //0x1E40
		int32_t off_hand; //0x1E44
		char pad_1E48[4]; //0x1E48
		int32_t ranged; //0x1E4C
		char pad_1E50[4]; //0x1E50
		int32_t tabard; //0x1E54
		char pad_1E58[488]; //0x1E58
	}; //Size: 0x2040
}