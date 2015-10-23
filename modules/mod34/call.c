#include "call.h"
#include "../irq.s"
#include "../mpx_supt.c"

context *cop;

//cop needs to be set up somewhere, as a 'global variable'
u32int* sys_call(context *registers){
	if(cop == NULL)
	{
		//save the above context as a global variable
		oldcon == registers;
	}
	else
	{
		if(params.op_code == IDLE)
		{
			//save context (reassign cop's stack top)
			cop->stacktop = registers;
		}
		else
		{
			if(params.op_code == EXIT)
			{
				//free cop
				freePCB(cop);
			}
		}
	}
	//check for ready process
	//if there is a ready process
		//remove from queue
		//assign cop
		//return cop's stacktop
	//NOTE: this is probably wrong and we'll need to redo it to not always take the head
	if(readyQueue->head != NULL){
		pcb *temp;
		temp = readyQueue->head;
		removePCB(temp);
		insertPCB(cop);
		cop = temp;
		return cop->stacktop;
	}
	//if not
		//return thing we saved in step 1
		//this is possibly wrong
		return cop->stacktop;
}