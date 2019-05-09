#pragma once
#include "pch.h"

namespace WowFunctions
{
	uintptr_t GetLocalPlayerBase();
	int32_t RunLua(const char*);
	int32_t RegisterFunction(const char*, uintptr_t);
	int32_t UpdateModel(uintptr_t);
}