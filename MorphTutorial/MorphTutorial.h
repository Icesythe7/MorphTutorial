#pragma once
#include "pch.h"

namespace MorphTutorial
{
	inline HANDLE MyThread;
	inline uintptr_t OnUpdateTrampoline;

	int32_t __cdecl OnUpdate(float*);
	DWORD WINAPI Init(LPVOID);
}