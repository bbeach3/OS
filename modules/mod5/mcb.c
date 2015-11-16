#include "mcb.h"
#include "system.h"
#include "mem/heap.h"

void *mcbheap;
mcblist *freelist;
mcblist *alloclist;



/**
\Function initializeHeap
\Description: prepares memory and related structures
\Parameters: none
\Returns: Success or Error code
*/
int initializeHeap()//Returns # of bytes allocated/Error code
{
	//Size of heap during testing: 200 bytes
	//Move up to 50000 byte max for the final
	int bytesalloc = 50000;
	
	mcbheap =(void *) kmalloc(bytesalloc);	//allocate heap
	if(mcbheap == NULL){
		return -1;
	}
	freelist =(mcblist *) kmalloc(sizeof(mcblist)); //initialize free list
	alloclist =(mcblist *) kmalloc(sizeof(mcblist)); // initialize allocated list
	freelist->head = NULL;
	alloclist->head = NULL;
	
	//make first block (the whole thing)
		//note to self - use memset and make the mcb, THEN point to it
	//he also wants me to remove freelist and alloclist as a struct and make them just pointers to the heads. So I guess remove that kmalloc up there, drop the ->head from all list mentions, and we're good? 
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

/**
\Function allocateMem
\Description: attempts to make allocated block in the heap
\Parameters: bytesalloc - amount of memory to allocate
\Returns: Pointer to where to write
*/
void *allocateMem(int bytesalloc)
{
	compmcb *found = NULL;
	//making sure there's a free block existing
	if(freelist->head == NULL){
		return NULL;
	}
	//if we get here, there's a freelist head, so set search to it
	compmcb *search = freelist->head;
	//seeing if the head works, since first fit
	if((unsigned)search->size >= bytesalloc + sizeof(compmcb) + sizeof(limitmcb)){
		found = search;
	}
	//if the head wasn't good enough, go through the list
	while(search->next != NULL){ //checking first, so we don't fall in a trap
		if(found == NULL){ //if we haven't found found
			if((unsigned)search->size >= bytesalloc + sizeof(compmcb) + sizeof(limitmcb)){
				found = search; //we found one big enough!
			}
		}
		search = search->next; //and advance
	}
	if(found == NULL){
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
		//note to self - supposed to return the memory's address
		return found->address + sizeof(compmcb);
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
	//note to self - supposed to return the memory's address
	return found->address + sizeof(compmcb);

	//To replace sys_alloc_mem, found in mpx_supt
	//Returns a pointer to the memory that was allocated, or NULL if an error occured
	//Will handle locating and breaking up blocks as necessary
}


/**
\Function insertPCB
\Description: inserts compmcb into proper list
\Parameters: toInsert - pointer to compmcb to insert
\Returns: none
*/
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

/**
\Function freeMem
\Description: attempts to free a memory block
\Parameters: ptr - pointer to block to remove
\Returns: Success or Error code
*/
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
	//realized allocateMem was returning the wrong thing
	//updating ptr here to keep things working
	ptr = ptr - sizeof(compmcb);
	
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
		/* The logic that was here was preserving toFree, when we want to absorb it into previous since previous comes first. - Bradley
			*/
		previous->next = toFree->next;
		previous->size += toFree->size;
		toFree->next = NULL;
		toFree->prev = NULL;
	}
	compmcb *nextOne = toFree->next;
	if(nextOne!= NULL && nextOne->address==toFree->address+toFree->size){
		toFree->size = toFree->size + nextOne->size;
		toFree->next = nextOne->next;
		nextOne->next = NULL;
		nextOne->prev = NULL;
	}
	limitmcb *limit =toFree->address + toFree->size - sizeof(limitmcb);
	limit->alloc = 0;
	limit->size = toFree->size;
	
	return 1;
}
