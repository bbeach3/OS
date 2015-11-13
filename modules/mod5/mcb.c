#include "mcb.h"
#include <stdlib.h>
#include <stdio.h>

void *mcbheap;
mcblist *freelist;
mcblist *alloclist;


int main(int argc, char* argv[])
{
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
}

int initializeHeap()//Returns # of bytes allocated/Error code
{
	//Size of heap during testing: 200 bytes
	//Move up to 50000 byte max for the final
	int bytesalloc = 200;
	
	mcbheap = malloc(bytesalloc);	//allocate heap
	if(mcbheap == NULL){
		return -1;
	}
	freelist = malloc(sizeof(mcblist)); //initialize free list
	alloclist = malloc(sizeof(mcblist)); // initialize allocated list
	freelist->head = NULL;
	alloclist->head = NULL;
	
	//make first block (the whole thing)
	compmcb *firstmcb = mcbheap;
	freelist->head = firstmcb;
	firstmcb->alloc = 0;
	//address holds firstmcb's location
	firstmcb->address = firstmcb;
	firstmcb->size = bytesalloc;
	firstmcb->next = NULL;
	firstmcb->prev = NULL;

	return bytesalloc;
}

//note to self - change 'bytesalloc' to 'size' when we move to mpx
void *allocateMem(int bytesalloc)
{
	compmcb *found = NULL;
	//making sure there's a free block existing
	if(freelist->head == NULL){
		printf("There is nothing in free list, or free list does not exist. Remove this later.");
		return NULL;
	}
	//if we get here, there's a freelist head, so set search to it
	compmcb *search = freelist->head;
	//seeing if the head works, since first fit
	if(search->size >= bytesalloc + sizeof(compmcb) + sizeof(limitmcb)){
		found = search;
	}
	//if the head wasn't good enough, go through the list
	while(search->next != NULL){ //checking first, so we don't fall in a trap
		if(found == NULL){ //if we haven't found found
			if(search->size >= bytesalloc + sizeof(compmcb) + sizeof(limitmcb)){
				found = search; //we found one big enough!
			}
		}
		search = search->next; //and advance
	}
	if(found == NULL){
		printf("searched the whole list and found nothing. Remove this later.");
		return NULL; //request failed
	}
	
	
	//now, we have to remove it from the free list
	//we already know where it is (found) so no need to search
	
	if(found->prev == NULL){
		freelist->head = found->next;
	} else {
		found->prev->next = found->next;
	}
	if(found->next != NULL){
		found->next->prev = found->prev;
	}
	found->next = NULL;
	found->prev = NULL;
	
	
	//we only make a remainder block if enough is left over.
	//the size of compmcb + limitmcb is 56, so 58 is a tight minimum
	limitmcb *templimit = found->address + found->size - sizeof(limitmcb);
	int leftovers = found->size - (bytesalloc + sizeof(compmcb) + sizeof(limitmcb));
	if(leftovers < 58){
		//too small. No remainder
		found->alloc = 1;
		templimit->alloc = 1;
		templimit->size = found->size;
		//insert procedure
		insertMCB(found);
		return found->address;
	}
	
	//otherwise, make a remainder
	found->alloc = 1;
	found->size = bytesalloc + sizeof(compmcb) + sizeof(limitmcb);
	//insert procedure
	insertMCB(found);
	//go to where limitmcb goes for new block
	templimit = found->address + found->size - sizeof(limitmcb);
	templimit->alloc = 1;
	templimit->size=found->size;
	
	//make the new free mcb
	compmcb *remaindermcb = found->address + found->size;
	remaindermcb->alloc = 0;
	remaindermcb->address = remaindermcb;
	
	remaindermcb->size = leftovers;
	//insert procedure
	insertMCB(remaindermcb);
	
	
	//make limitmcb for the new free block
	limitmcb* templimitF = remaindermcb->address + remaindermcb->size;
	
	templimitF->alloc = 0;
	templimitF->size = leftovers;
	return found->address;

	//To replace sys_alloc_mem, found in mpx_supt
	//Returns a pointer to the memory that was allocated, or NULL if an error occured
	//Will handle locating and breaking up blocks as necessary
}

void insertMCB(compmcb *toInsert){
	if(toInsert->alloc == 0){
		if(freelist->head == NULL){
			freelist->head = toInsert;
			return;
		}
		struct compmcb *temp = freelist->head;
		if(temp->next == NULL){ //only the head exists
			if(toInsert->address > temp->address){ //head has lower address
				temp->next = toInsert;
				toInsert->prev = temp;
				return;
			} else { //head has higher address
				freelist->head = toInsert;
				toInsert->next = temp;
				temp->prev = toInsert;
				return;
			}
		}	
		//there's more than just the head to go through
		while(temp->next != NULL){
			temp = temp->next;
			if(toInsert->address < temp->address){
				temp->prev->next = toInsert;
				toInsert->prev = temp->prev;
				temp->prev = toInsert;
				toInsert->next = temp;
				return;
			}
		}
		//if we get here, toInsert had the highest address
		//and temp is the last current compmcb
		temp->next = toInsert;
		toInsert->prev = temp;
		return;
			
		
		
		//stop
	} else {
		//if list is empty, put mcb at head
		if(alloclist->head == NULL){
			alloclist->head = toInsert;
			return;
		}
		struct compmcb *temp = alloclist->head;
		if(temp->next == NULL){ //only the head exists
			if(toInsert->address > temp->address){ //head has lower address
				temp->next = toInsert;
				toInsert->prev = temp;
				return;
			} else { //head has higher address
				alloclist->head = toInsert;
				toInsert->next = temp;
				temp->prev = toInsert;
				return;
			}
		}
		//there's more than just the head to go through
		while(temp->next != NULL){
			temp = temp->next;
			if(toInsert->address < temp->address){
				temp->prev->next = toInsert;
				toInsert->prev = temp->prev;
				temp->prev = toInsert;
				toInsert->next = temp;
				return;
			}
		}
		//if we get here, toInsert had the highest address
		//and temp is the last current compmcb
		temp->next = toInsert;
		toInsert->prev = temp;
		return;
	}
}

int freeMem(void *ptr)
{
	//1. Go to the amcb we're told. 
	//2. remove amcb from alloclist (special case - it's the head)
	//3. change compmcb and limitmcb to free
	//4. link into FMCB
	//5. do merges. 
		//check the limitmcb by free compmcb, compmcb by free limitmcb
	//6. return
	if(alloclist->head == NULL){
		return 0;
	}	
	compmcb *toFree = NULL;
	compmcb *search = alloclist->head;
	while(toFree==NULL){
		if(search == NULL){
			break;
		}
		if(search->address == ptr){
			toFree=search;
			break;
		}
		search= search->next;
	}
	if(toFree==NULL){
		return 0; //MCB not found, return error code
	}
	
	if(toFree->alloc==0){ 
		return 0; //mcb is not allocated, return error code
	
	}
	if(alloclist->head==toFree){
		if(toFree->next==NULL)
			alloclist->head =NULL;
		else{
			toFree->next->prev = NULL;
			alloclist->head = toFree->next;
			toFree->next = NULL;
		}
	}
	else{
		if(toFree->next!=NULL)
			toFree->next->prev = toFree->prev;
		toFree->prev->next = toFree->next;
		toFree->next=NULL;
		toFree->prev=NULL;
	}
	toFree->alloc = 0;
		
	insertMCB(toFree);
	compmcb *previous = toFree->prev;
	if(previous!= NULL && previous->address+previous->size==toFree->address){
		if(previous ==freelist->head)
			freelist->head = toFree;
		toFree->prev = previous->prev;
		toFree->size+= previous->size;
		toFree->address = previous->address;
		previous->next = NULL;
		previous->prev = NULL;
	}
	compmcb *nextOne = toFree->next;
	if(nextOne!= NULL && nextOne->address==toFree->address+toFree->size){
		toFree->next = nextOne->next;
		toFree->size+= nextOne->size;
		nextOne->next = NULL;
		nextOne->prev = NULL;
	}
	limitmcb *limit =toFree->address + toFree->size - sizeof(limitmcb);
	limit->alloc = 0;
	limit->size = toFree->size;
	
	return 1; //this is garbage so it compiles
}

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
