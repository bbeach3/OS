#include "call.h"
#include "../irq.s"
#include "../mpx_supt.c"

//cop needs to be set up somewhere, as a 'global variable'
u32int* sys_call(context *registers){
	if(cop == NULL)
	{
		//save the above context as a global variable, probably cop
		cop == registers;
	}
	else
	{
		if(params.op_code == IDLE)
		{
			//save context
		}
		else
		{
			if(params.op_code == EXIT)
			{
				//free cop
			}
		}
	}
}
