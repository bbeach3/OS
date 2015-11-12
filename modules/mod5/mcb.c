#include "mcb.h"
int initializeHeap()//Returns # of bytes allocated/Error code
{
	//Size of heap during testing: 200 bytes
	//Move up to 50000 byte max for the final
	int bytesalloc = 200;

	mcbheap = (heap *)malloc(bytesalloc);//Allocating for our heap
	mcbheap->base = &mcbheap; //Top of our heap
	mcbheap->max_size = bytesalloc; 
	mcbheap->min_size = 0;
	//Use for index?

	//Then, our free and allocated list are initialized - but what exactly are these?
	//The answer: freelist is memory that is unassigned, allocated list is mcbs 		  assigned to a process
	//freelist = 
	//alloclist = 

	//Finally, we create our free block and place it in the free list
	compmcb heapmcb
	heapmcb.alloc = 0;
	heapmcb->address = mcbheap->base;
	heapmcb.size = bytesalloc;

	//Add heapmcb onto our free list 

	return bytesalloc;
}

//To replace sys_alloc_mem, found in mpx_supt
//Returns a pointer to the memory that was allocated, or NULL if an error occured
//Will handle locating and breaking up blocks as necessar
compmcb *allocateMem(int bytesalloc)
{
	compmcb *found = NULL;
	compmcb *search = *freelist;
	while(found==null){//this loop searches through the freelist and returns the first mcb with 				     enough space
		if(search->size >=bytesalloc+sizeof(compmcb)+sizeof(limitmcb)) 
			found = search;
		else
			search = search->next;
	}
	if(found ==null)
		return null;
	
	//if found is head of freelist, make the next free mcb head
	if(freelist == found){
		freelist == found->next;
		found->next->prev = null;
	}
	else{
	//remove found from freelist
	found->next->prev = found->prev; 
	found->prev->next = found->next; 
	}
	//initialize allocated mcb
	compmcb *ambc = { ->alloc = 1, ->address = found->address, ->size = bytesalloc + sizeof(compmcb)+ sizeof(limitmcb),next = null, prev = null}; 
	//create limited mcb, not sure how it links in yet
	compmcb *end = {->alloc = 1, ->size = bytesalloc + sizeof(compmcb)+ sizeof(limitmcb)};

	compmcb *asearch = alloclist;
	//if there is no head, make ambc head 
	if(asearch ==null)
		alloclist = ambc; 
	else{
		//search for correct position in alloclist
		while(asearch!= null){	
			//ambc is smaller than head, make it the new head
			if(asearch->address > ambc->address && asearch->prev ==null){ 
				alloclist =ambc;
				ambc->next = asearch;
				break;
			}
			//ambc is larger than search but smaller than next, insert inbetween
			else if(asearch->address < ambc->address && asearch->next->address> ambc->address){
				ambc->next = asearch->next;
				ambc->prev = asearch;
				asearch->next = ambc;
				ambc->next->prev = ambc;
				break;	
			}
			//ambc is larger than largest in list, insert at end
			else if(asearch->address > ambc->address && asearch->next == null){
				asearch ->next = ambc;
				ambc->prev = asearch;
				ambc->next = null;
				break;
			}
		}
	}
	//if ambc isn't alloclist and asearch is null, an error has occured. Shouldn't ever happen, though.
	if(asearch ==null && alloclist!=ambc)
		return null;
	//now, time to make the remainder block	
	compmcb *remaindercomp  = { ->alloc = 0, ->address = found->address - bytesalloc + sizeof(compmcb)+ sizeof(limitmcb), ->size = found->size - (bytesalloc + sizeof(compmcb)+ sizeof(limitmcb)),next = null, prev = null}; 
	compmcb *remainderlim   = { ->alloc = 0, size = remaindercomp->size);
	if(freelist==null)
		freelist = remaindercomp;
	else{
		compmcb fsearch = freelist;
		//search for correct position in freelist
		while(fsearch!= null){	
			//remaindercomp is smaller than head, make it the new head
			if(fsearch->address > remaindercomp->address && fsearch->prev ==null){ 
				freelist =remaindercomp;
				ambc->next = asearch;
				break;
			}
			//remaindercomp is larger than search but smaller than next, insert inbetween
			else if(fsearch->address < remaindercomp->address && fsearch->next->address> remaindercomp->address){
				remaindercomp->next = remaindercomp->next;
				remaindercomp>prev = fsearch;
				fsearch->next = remaindercomp;
				ambc->next->prev = remaindercomp;
				break;	
			}
			//remaindercomp is larger than largest in list, insert at end
			else if(fsearch->address > remaindercomp->address && fsearch->next == null){
				fsearch ->next = remaindercomp;
				remaindercomp->prev = fsearch;
				remaindercomp->next = null;
				break;
			}
		}
	return ambc;
}

void freeMem()
{
	//To replace sys_free_mem, found in mpx_supt
	//Only returns error codes
}

void showAllocMap()
{
	
}

void showFreeMap()
{
	
}

int isEmpty()
{
	
}
