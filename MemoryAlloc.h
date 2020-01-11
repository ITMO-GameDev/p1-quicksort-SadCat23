#pragma once
#include <map>
#include "FixedAlloc.h"
#include  "FreeAlloc.h"
class MemoryAlloc
{
private:
	std::map<int, FixedAlloc*> FSA_alloc;
	std::map<int, FreeAlloc*> FL_alloc;
	std::map<void*, FreeAlloc*> dumpFLMap;
	bool isInit;

	static int align(int size);
public:
	MemoryAlloc();
	~MemoryAlloc();
	virtual void init();
	virtual void* alloc(int size);
	virtual void free(void* ptr);
	virtual void destroy(); 
	#ifndef NDEBUG
	virtual void dumpBlocks();
	#endif
	


};