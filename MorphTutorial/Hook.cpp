#include "pch.h"

namespace Hook
{
	bool Create(const uintptr_t target, const uintptr_t* handler, uintptr_t* trampoline, const size_t size)
	{
		auto result = false;
		DWORD dwProtect;
		DWORD tVar;

		//protect original read/write
		if (VirtualProtect(reinterpret_cast<LPVOID>(target), size, PAGE_EXECUTE_READWRITE, &dwProtect))
		{
			auto hook = std::make_shared<ByteBuffer>(); 			
			ByteBuffers.emplace_back(hook);

			for (auto i = 0; i < static_cast<int32_t>(size); ++i)
				hook->data[i] = *reinterpret_cast<BYTE*>(target + i);                                         // copy original bytes to trampoline																							        

			hook->data[size] = static_cast<BYTE>(0x68);								                        // push ...
			*reinterpret_cast<int32_t*>(&hook->data[size + 1]) = target + size;			                    // the address of the next valid instruction in the target
			hook->data[size + 5] = static_cast<BYTE>(0xC3);							                        // return
			*trampoline = reinterpret_cast<uintptr_t>(hook->data);
			VirtualProtect(reinterpret_cast<LPVOID>(hook->data), size + 6, PAGE_EXECUTE_READWRITE, &tVar);

			*reinterpret_cast<BYTE*>(target) = 0x68;							                        // push ...
			*reinterpret_cast<int32_t*>(target + 1) = reinterpret_cast<int32_t>(handler);	            // the address of the detour
			*reinterpret_cast<BYTE*>(target + 5) = 0xC3;							                    // return

			for (auto i = 6; i < static_cast<int32_t>(size); ++i)                                       // if size > 6
				*reinterpret_cast<BYTE*>(target + i) = 0x90;						                    // fill the gap with NOPs

			result = VirtualProtect(reinterpret_cast<LPVOID>(target), size, dwProtect, &tVar);          // restore original memory protection
		}
		return result;
	}

	bool Restore(const uintptr_t target, const uintptr_t trampoline, const size_t size)
	{
		auto result = false;

		if (trampoline)
		{
			DWORD dwProtect;
			DWORD tVar;
			if (VirtualProtect(reinterpret_cast<LPVOID>(target), size, PAGE_EXECUTE_READWRITE, &dwProtect))
			{
				for (auto i = 0; i < static_cast<int32_t>(size); ++i)
					*reinterpret_cast<BYTE*>(target + i) = *reinterpret_cast<BYTE*>(trampoline + i);
				result = VirtualProtect(reinterpret_cast<LPVOID>(target), size, dwProtect, &tVar);
			}
		}
		return result;
	}

	void SuspendThreads(const DWORD threadToKeepRunning)
	{
		const auto h = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		if (h != INVALID_HANDLE_VALUE)
		{
			THREADENTRY32 te;
			te.dwSize = sizeof te;
			if (Thread32First(h, &te))
			{
				do
				{
					if (te.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) + sizeof te.th32OwnerProcessID)
					{
						if (te.th32ThreadID != threadToKeepRunning && te.th32OwnerProcessID == GetCurrentProcessId())
						{
							const auto thread = OpenThread(THREAD_ALL_ACCESS, FALSE, te.th32ThreadID);
							if (thread != nullptr)
							{
								SuspendThread(thread);
								CloseHandle(thread);
							}
						}
					}
					te.dwSize = sizeof te;
				} while (Thread32Next(h, &te));
			}
			CloseHandle(h);
		}
	}

	void ResumeThreads()
	{
		const auto h = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		if (h != INVALID_HANDLE_VALUE)
		{
			THREADENTRY32 te;
			te.dwSize = sizeof te;
			if (Thread32First(h, &te))
			{
				do
				{
					if (te.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) + sizeof te.th32OwnerProcessID)
					{
						if (te.th32OwnerProcessID == GetCurrentProcessId())
						{
							const auto thread = OpenThread(THREAD_ALL_ACCESS, FALSE, te.th32ThreadID);
							if (thread != nullptr)
							{
								ResumeThread(thread);
								CloseHandle(thread);
							}
						}
					}
					te.dwSize = sizeof te;
				} while (Thread32Next(h, &te));
			}
			CloseHandle(h);
		}
	}
}