#include "pch.h"
#include  <malloc.h>
#include <iostream>
#include "FixedAlloc.h"
#include "windows.h"

FixedAlloc::FixedAlloc(const std::size_t chunkSize) : m_chunkSize(chunkSize), m_freeList()
{
	isInit = false;
}

FixedAlloc::~FixedAlloc()
{
	this->FixedAlloc::destroy();
}

void FixedAlloc::init()
{
	request_page();
	isInit = true;
}

void* FixedAlloc::alloc()
{

	if (m_freeList.head == nullptr)
	{
		request_page();
	}
	Node* freePosition = m_freeList.pop();
	dumpSet.insert(freePosition);
	return static_cast<void*>(freePosition);
}

bool FixedAlloc::free(void* ptr)
{
	auto contains = dumpSet.erase(ptr);
	if (contains) {
		m_freeList.push(static_cast<Node*>(ptr));
	}
	return contains;
}

void FixedAlloc::destroy()
{
	for (auto page : pages)
	{
		VirtualFree(page, 0, MEM_RELEASE);
	}
	isInit = false;
	dumpSet.clear();

}
void FixedAlloc::dumpBlocks()
{
	for (auto val : dumpSet) {
		std::cout << val << " " << m_chunkSize << std::endl;
	}

}

void FixedAlloc::chunk_page(void* page)
{
	const int nChunks = pageSize / m_chunkSize;
	for (int i = 0; i < nChunks; ++i) {
		const std::size_t address = reinterpret_cast<std::size_t>(page) + i * m_chunkSize;
		m_freeList.push(reinterpret_cast<Node*>(address));
	}
}

void* FixedAlloc::request_page()
{
	const auto page = VirtualAlloc(nullptr, pageSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	pages.push_back(page);
	chunk_page(page);
	return page;
}