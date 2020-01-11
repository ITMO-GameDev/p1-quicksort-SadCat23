#include "pch.h"
#include "MemoryAlloc.h"
#include <windows.h>
#include <cmath>
#include <cassert> 

int MemoryAlloc::align(int size)
{
	auto value = pow(2, ceil(log2(size)));
	return value >= 16 ? value : 16;
}

MemoryAlloc::MemoryAlloc()
{
	isInit = false;

}

MemoryAlloc::~MemoryAlloc()
{
	this->MemoryAlloc::destroy();
}

void MemoryAlloc::init()
{
	int start = 16;

	for (; start <= 512; start *= 2)
	{
		auto allocator = new FixedAlloc(start);
		allocator->init();

		FSA_alloc.insert_or_assign(start, allocator);
	}
	auto freelist = new FreeAlloc(52428800, FreeAlloc::PlacementPolicy::FIND_FIRST);
	freelist->init();
	FL_alloc.insert_or_assign(0, freelist);

	isInit = true;
}

void* MemoryAlloc::alloc(int size)
{
#ifndef NDEBUG
	assert(isInit);
#endif
	if (!isInit) return nullptr;
	if (size > 10485760)
	{
		return VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	}
	if (size > 512)
	{
		for (auto it = FL_alloc.begin(); it != FL_alloc.end(); ++it)
		{
			if (it->second->getFreeSize() > size)
			{
				auto mem = it->second->allocate(size);
				std::cout << mem << std::endl;
				dumpFLMap.insert_or_assign(mem, it->second);
				return mem;

			}
		}
		auto freelist = new FreeAlloc(52428800, FreeAlloc::PlacementPolicy::FIND_FIRST);
		freelist->init();
		FL_alloc.insert_or_assign(FL_alloc.size() + 1, freelist);
		auto mem = freelist->allocate(size);
		dumpFLMap.insert_or_assign(mem, freelist);
		return mem;

	}
	auto alignedSize = align(size);
	auto allocator = FSA_alloc[alignedSize];
	return  allocator->alloc();
}

void MemoryAlloc::free(void* ptr)
{
#ifndef NDEBUG
	assert(isInit);
#endif
	if (!isInit) return;

	for (auto it = FSA_alloc.begin(); it != FSA_alloc.end(); ++it)
	{
		if (it->second->free(ptr))
			return;
	}

	if (dumpFLMap.count(ptr))
	{

		dumpFLMap[ptr]->free(ptr);
		dumpFLMap.erase(ptr);
		return;
	}


	VirtualFree(ptr, 0, MEM_RELEASE);
}

void MemoryAlloc::destroy()
{
#ifndef NDEBUG
	assert(isInit);
#endif
	if (!isInit) return;
	for (auto it = FSA_alloc.begin(); it != FSA_alloc.end(); ++it)
	{
		it->second->destroy();
	}
	for (auto it = FL_alloc.begin(); it != FL_alloc.end(); ++it)
	{
		it->second->destroy();
	}
	FSA_alloc.clear();
	FL_alloc.clear();
	dumpFLMap.clear();
	isInit = false;
}

void MemoryAlloc::dumpBlocks()
{
#ifndef NDEBUG
	assert(isInit);
#endif
	if (!isInit) return;
	for (auto it = FSA_alloc.begin(); it != FSA_alloc.end(); ++it)
	{
		it->second->dumpBlocks();
	}
}
