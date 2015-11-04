#include "procsr3.h"

/**
\Function loadr3
\Description: creates pcbs for one of the five provided processes
\Parameters: char * name - a pointer to the name of the process
\Returns: pointer to created pcb
*/
pcb *loadr3(char *name)//stack size?
{
	pcb *newpcb = setupPCB(name, 1, 1);
	newpcb->suspension = 0; //Must be suspended ready
	context *con = (context*)(newpcb->stacktop);
	memset(con, 0, sizeof(context));
	con->fs = 0x10;
	con->gs = 0x10;
	con->ds = 0x10;
	con->es = 0x10;
	con->cs = 0x8;
	con->ebp = (u32int)(newpcb->stack);
	con->esp = (u32int)(newpcb->stacktop);
	if(strcmp(name, "Process1") == 0)
	{
		con->eip = (u32int)proc1;
	}
	else if(strcmp(name, "Process2") == 0)
	{
		con->eip = (u32int)proc2;
	}
	else if(strcmp(name, "Process3") == 0)
	{
		con->eip = (u32int)proc3;
	}
	else if(strcmp(name, "Process4") == 0)
	{
		con->eip = (u32int)proc4;
	}
	else if(strcmp(name, "Process5") == 0)
	{
		con->eip = (u32int)proc5;
	}
	else if(strcmp(name, "Menu") == 0)
	{
		con->eip = (u32int)menu;
	}
	else
	{
		con->eip = (u32int)idle;
	}
	//These are all hard-coded, so there's no need to check for any other cases
	return newpcb;
}

void proc1()
{
  int i;

  // repeat forever if termination fails
  while(1){
    for(i=0; i<RC_1; i++){
      serial_println("proc1 dispatched");
      sys_req(IDLE);
    }
    sys_req(EXIT);
    serial_println("proc1 ran after it was terminated");
  }
}

void proc2()
{
  int i;

  // repeat forever if termination fails
  while(1){
    for(i=0; i<RC_2; i++){
      serial_println("proc2 dispatched");
      sys_req(IDLE);
    }
    sys_req(EXIT);
    serial_println("proc2 ran after it was terminated");
  }
}

void proc3()
{
  int i;

  // repeat forever if termination fails
  while(1){
    for(i=0; i<RC_3; i++){
      serial_println("proc3 dispatched");
      sys_req(IDLE);
    }
    sys_req(EXIT);
    serial_println("proc3 ran after it was terminated");
  }
}

void proc4()
{
  int i;

  // repeat forever if termination fails
  while(1){
    for(i=0; i<RC_4; i++){
      serial_println("proc4 dispatched");
      sys_req(IDLE);
    }
    sys_req(EXIT);
    serial_println("proc4 ran after it was terminated");
  }
}

void proc5()
{
  int i;

  // repeat forever if termination fails
  while(1){
    for(i=0; i<RC_5; i++){
      serial_println("proc5 dispatched");
      sys_req(IDLE);
    }
    sys_req(EXIT);
    serial_println("proc5 ran after it was terminated");
  }
}
