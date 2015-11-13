#include "mcb.c"
#include <stdlib.h>
#include <stdio.h>

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
