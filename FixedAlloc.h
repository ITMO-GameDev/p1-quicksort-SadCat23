#pragma once
#include <cstddef>
#include <list>
#include "stackLinkedList.cpp"
#include <vector>
#include  <set>
#include <string>
#include <iostream>


class FixedAlloc
{
protected:
	std::size_t m_chunkSize;
	std::vector<void*> pages;
	std::set<void*> dumpSet;
	const static size_t pageSize = 4096;
	bool isInit;

	struct  FreeHeader {
	};
	using Node = StackLinkedList<FreeHeader>::Node;
	StackLinkedList<FreeHeader> m_freeList;

	void* m_start_ptr = nullptr;


	virtual void* request_page();
	virtual  void chunk_page(void* page);

public:
	FixedAlloc(std::size_t chunkSize);

	virtual ~FixedAlloc();
	virtual void init();
	virtual void* alloc();
	virtual bool free(void* ptr);
	virtual void destroy();
	virtual void dumpBlocks();






};