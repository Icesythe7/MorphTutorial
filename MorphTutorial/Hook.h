#pragma once
#include "pch.h"

namespace Hook
{
	struct ByteBuffer final
	{
		BYTE data[32];
	};

	inline std::list<std::shared_ptr<ByteBuffer>> ByteBuffers;

	bool Create(uintptr_t, const uintptr_t*, uintptr_t*, size_t);
	bool Restore(uintptr_t, uintptr_t, size_t);
	void SuspendThreads(DWORD);
	void ResumeThreads();
}
