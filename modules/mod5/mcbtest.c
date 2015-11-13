#include "mcb.c"
#include <stdlib.h>
#include <stdio.h>

/**
\Function initializeMemory
\Description: attemps to initialize memory and reports on it
\Parameters: none
\Returns: none
*/
void initializeMemory()
{
	int initResults = initializeHeap();
	if(initResults == -1){
		printf("Initialization failed. \n");
	} else {
		printf("Initialization successful. \n");
	}
}

/**
\Function allocateMemory
\Description: attempts to allocate a block
\Parameters: size - amount of memory to allocate
\Returns: pointer to the allocated space
*/
void *allocateMemory(int size)
{
	void *allocatedspace = allocateMem(size);
	if (allocatedspace == NULL){
		printf("Allocation failed. \n");
		return NULL;
	}
	void *theblock = allocatedspace - sizeof(compmcb);
	int offset =(int) (theblock - mcbheap);
	printf("Allocation worked - Block address as offset: %d \n", offset);
	return allocatedspace;
}

/**
\Function freeMemory
\Description: attempts to free a block
\Parameters: address - pointer to block to free
\Returns: none
*/
void freeMemory(void *address){
	int result = freeMem(address);
	if(result == 0){
		printf("Free Memory failed. \n");
	} else {
		printf("Free Memory worked. \n");
		int offset = (int) (address - mcbheap);
		//address points to the memory, so we retreat to the compmcb
		offset = offset - sizeof(compmcb);
		printf("Block address as offset: %d \n", offset);
	}
}

/**
\Function showAllocMap
\Description: prints data on all allocated blocks
\Parameters: none
\Returns: none
*/
void showAllocMap()
{
	if(alloclist->head == NULL){
		printf("No alloc.\n");
		return;
	}
	compmcb *temp = alloclist->head;	
	while(temp != NULL){
		printf("Printing a block\n");
		int offset;
		offset = (int ) ((void *)temp - mcbheap);
		printf("Location %d \n",offset);
		printf("size %d \n", temp->size);
		printf("alloc code %d \n", temp->alloc);
		printf("Block done. \n");
		temp = temp->next;
	}
}

/**
\Function showFreeMap
\Description: prints data on all free blocks
\Parameters: none
\Returns: none
*/
void showFreeMap()
{
	compmcb *tempFree = freelist->head;
	while(tempFree !=NULL)
	{
	printf("Printing free block\n");
	int offset;
	offset = (int ) ((void *)tempFree - mcbheap);
	printf("Location %d \n",offset);
	printf("Size %d \n",tempFree->size);
	printf("Alloc code %d \n",tempFree->alloc);
	printf("Block done. \n");
	tempFree = tempFree->next;
	}
}

/**
\Function isEmpty
\Description: checks if the entire heap is a single free block
\Parameters: oldpcb - pointer to PCB to remove
\Returns: Boolean result
*/
int isEmpty()
{
	if(alloclist->head == NULL){
		if(freelist->head != NULL){
			if(freelist->head->next == NULL){
				printf("isEmpty = yes\n");
				return 1; //just the one free mcb
			}
		}
	}
	printf("isEmpty = no\n");
	return 0; //not empty
}

int main(int argc, char* argv[])
{
	initializeMemory();
	void *addr1 = allocateMemory(50);
	void *addr2 = allocateMemory(30);
	showAllocMap();
	showFreeMap();
	freeMemory(addr2);
	showAllocMap();
	showFreeMap();
	freeMemory(addr1);
	showAllocMap();
	showFreeMap();
	isEmpty();
}



/*

prior tests - for posterity
	printf("initializing \n");
	int initcheck;
	initcheck = initializeHeap();
	if(initcheck == -1){
		printf("init failed. \n");
	} else {
		printf("init worked. \n");
	}
	isEmpty();
	printf("printing free first time\n");
	showFreeMap();
	printf("Allocating 30.\n");
	void *ambc = allocateMem(30);
	printf("Allocating 10.\n");
	void *ambc2 = allocateMem(10);
	isEmpty();
	showAllocMap();
	printf("printing free second time\n");
	showFreeMap();
	printf("freeing block \n");
	freeMem(ambc);
	printf("block as been freed \n");
	printf("printing free third time\n");
	showFreeMap();
	showAllocMap();
	freeMem(ambc2);
	printf("printing free final time\n");
	showFreeMap();
	showAllocMap();
*/
