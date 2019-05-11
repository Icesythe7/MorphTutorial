#include "pch.h"

namespace MorphTutorial
{
	DWORD WINAPI Init(void* const(param))
	{
		AllocConsole();
		SetConsoleTitle(L"MorphTutorial Debug Console");
		FILE* stream;
		freopen_s(&stream, "CONOUT$", "w", stdout);

		Hook::SuspendThreads(GetThreadId(MyThread));
		if (Hook::Create(WowAddresses::OnIdle, reinterpret_cast<uintptr_t*>(&OnUpdate), &OnUpdateTrampoline, 6))
			printf("GameLoop successfully hooked\n");
		else
		{
			printf("GameLoop hook failed... unloading dll in 5 seconds\n");
			Hook::ResumeThreads();
			Sleep(5000);
			const auto conHandle = GetConsoleWindow();
			FreeConsole();
			PostMessage(conHandle, WM_CLOSE, 0, 0);
			FreeLibraryAndExitThread(static_cast<HMODULE>(param), NULL);
		}

		Hook::ResumeThreads();

		//F4 to unload dll 
		while(1 & !GetAsyncKeyState(VK_F4))
		{
			Sleep(1);
		}

		Hook::SuspendThreads(GetThreadId(MyThread));
		if (Hook::Restore(WowAddresses::OnIdle, OnUpdateTrampoline, 6))
		{
			const auto conHandle = GetConsoleWindow();
			FreeConsole();
			PostMessage(conHandle, WM_CLOSE, 0, 0);
			Hook::ResumeThreads();
			FreeLibraryAndExitThread(static_cast<HMODULE>(param), NULL);
		}
		Hook::ResumeThreads(); //failsafe

		return 0;
	}

	int32_t __cdecl OnUpdate(float* a1)
	{
		if (GetAsyncKeyState(VK_F7) & 1)
		{
			printf("My base address is 0x%X\n", WowFunctions::GetLocalPlayerBase());
			for (const auto function : Lua::FunctionsMap)
			{
				if (WowFunctions::RegisterFunction(function.first, function.second))
				{
					std::stringstream fName;
					fName << "print('Registered [" << function.first << "]')" << "\n";
					WowFunctions::RunLua(fName.str().c_str());
				}
			}
		}

		return reinterpret_cast<int32_t(__cdecl*)(float*)>(OnUpdateTrampoline)(a1);
	}
}