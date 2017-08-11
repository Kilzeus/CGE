#include"MemoryPool.h"
#include"Logger.h"
#include<iostream>
#include<sstream>

MemoryBlock::MemoryBlock( size_t size, size_t numBlocks )
 : chunkSize(size),full(false)
{

	//data = malloc(sizeof(MemoryBlock) + size * numBlocks );
	data = this+1;
	blockUsage.resize( numBlocks, false );

}

MemoryBlock::~MemoryBlock()
{

	//free( data );

}

void* MemoryBlock::allocate()
{

	for( int i = 0; i < blockUsage.size(); i++ )
	{
		if( blockUsage[i] == false )
		{
			blockUsage[i] = true;
			char* address = (char*)data + chunkSize * i;
			return (void*)address;
		}
	}
	return 0;
}

void* MemoryBlock::allocateMany( size_t numBlocks, size_t& blocksAllocated )
{

	for( int i = 0; i < blockUsage.size(); i++ )
	{
		if( blockUsage[i] == false )
		{
			blockUsage[i] = true;
			char* address = (char*)data + chunkSize * i;
			return (void*)address;
		}
	}
	return 0;

}

void MemoryBlock::deallocate( void* p )
{

	size_t index;
	if((char*)p - (char*)data > 0 ) index = ((char*)p - (char*)data ) / chunkSize;
	else 
		index = 0;
	blockUsage[index] = false;
	full = false;

}

bool MemoryBlock::isFull()
{

	for( int i = 0; i < blockUsage.size(); i++ )
	{
		if(!blockUsage[i]) return false;
	}
	return true;
}

MemoryPool::MemoryPool( size_t objectSize, size_t numBlocks )
 : objectSize(objectSize),numBlocks(numBlocks)
{

	//size_t q = objectSize % 16;
	//this->objectSize += ( 16 - q );
	//blocks.push_back( new MemoryBlock( objectSize, numBlocks ));
	MemoryBlock* block = (MemoryBlock*)malloc(sizeof(MemoryBlock) + objectSize * numBlocks );
	//if(!block ) Logger::getSingleton().logEntry( "mem error!", "memoryblock allocation failed" );;
	new (block) MemoryBlock( objectSize, numBlocks );
	blocks.push_back( block );

}

void* MemoryPool::allocate( size_t numBlocks )
{

	for( int i = 0; i < blocks.size(); i++ )
	{
		if(!blocks[i]->isFull()) return blocks[i]->allocate();
	}
	//MemoryBlock* block = new MemoryBlock( objectSize, numBlocks );
	MemoryBlock* block = (MemoryBlock*)malloc(sizeof(MemoryBlock) + objectSize * numBlocks );
	//if(!block ) Logger::getSingleton().logEntry( "mem error!", "memoryblock allocation failed" );;
	new (block) MemoryBlock( objectSize, numBlocks );
	blocks.push_back( block );
	return block->allocate();
}

void MemoryPool::deallocate( void* p )
{

	for( int i = 0; i < blocks.size(); i++ )
	{
		if( blocks[i] <= p && p < (char*)blocks[i] + sizeof(MemoryBlock) + objectSize * numBlocks )
		{
			blocks[i]->deallocate( p );
		}
	}
}

MemoryPool::~MemoryPool()
{

	for( int i = 0; i < blocks.size(); i++ )
	{
		free( blocks[i]);
	}

}