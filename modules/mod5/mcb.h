#ifndef _MCB_H
#define _MCB_H

typedef struct compmcb compmcb;

struct compmcb{
	int alloc; //0 is free, 1 is allocated
	void *address; //own (the compmcb's) address
	int size;
	char pcbname[9];
	compmcb *next;
	compmcb *prev;
};

typedef struct limitmcb limitmcb;

struct limitmcb{
	int alloc;
	int size;	//of blocks + memory
};

typedef struct mcblist mcblist;

struct mcblist{
	compmcb *head;
};

extern mcblist* freelist;
extern mcblist* alloclist;
extern void* mcbheap;

int initializeHeap();

//prototype must match sys_alloc_mem when we replace mpx's with our own
void *allocateMem(int bytesalloc);
//for now, it doesn't, because I had some compiling issues.
//when we make the switch, change the name, type of size...
//if all else fails, just leave the name as is and have sys_alloc_mem call it		

void insertMCB(compmcb *toInsert);

//see notes above on allocateMem
int freeMem(void *ptr);

void showAllocMap();

void showFreeMap();

int isEmpty();

#endif