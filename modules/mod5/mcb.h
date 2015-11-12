#ifndef _MCB_H
#define _MCB_H

#include "mem/heap.h"

typedef struct {
	int alloc; //0 is free, 1 is allocated
	void *address;
	int size;
	void *next;
	void *prev;
} compmcb;

typedef struct {
	int alloc;
	int size;	
} limitmcb;

struct heap *mcbheap;
compmcb *freelist;
compmcb *alloclist;

int initializeHeap();

u32int *allocateMem(int bytesalloc);

void freeMem();

void showAllocMap();

void showFreeMap();

int isEmpty();

#endif
