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
	//freelist = 
	//alloclist = 

	//Finally, we create our free block and place it in the free list
	struct compmcb heapmcb;

	heapmcb.alloc = 0;
	heapmcb->address = mcbheap->base;
	heapmcb.size = bytesalloc;

	//Add heapmcb onto our free list 

	return bytesalloc;
}

u32int *allocateMem(int bytesalloc)
{
	//To replace sys_alloc_mem, found in mpx_supt
	//Returns a pointer to the memory that was allocated, or NULL if an error occured
	//Will handle locating and breaking up blocks as necessary
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
