#pragma once
#include "pch.h"

namespace MorphTutorial
{
	inline HANDLE MyThread;
	inline uintptr_t OnUpdateTrampoline;
	inline uintptr_t EnterWorldTrampoline;

	int32_t __cdecl OnUpdate(float*);
	void __cdecl OnEnterWorld();
	DWORD WINAPI Init(LPVOID);
}