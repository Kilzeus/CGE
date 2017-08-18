#pragma once

#include<new>
#include<vector>

class MemoryBlock
{

	void* data;
	std::vector<bool> blockUsage;
	size_t chunkSize;
	bool full;
	
	public:
	
	
	MemoryBlock( size_t size, size_t numBlocks );
	~MemoryBlock();
	void* allocate();
	void* allocateMany( size_t numBlocks, size_t& blocksAllocated );
	void deallocate( void* p );
	bool isFull();

};

class MemoryPool
{

	size_t objectSize;
	size_t numBlocks;
	std::vector<MemoryBlock*> blocks;

	public:
	
	MemoryPool( size_t objectSize, size_t numBlocks );
	~MemoryPool();
	void* allocate( size_t numBlocks = 1 );
	void deallocate( void* p );

};