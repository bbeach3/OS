#include "procsr3.h"

pcb *loadr3(char *name)
{
	pcb *newpcb = setupPCB(name, 1, 1);
	newpcb->suspended = 0; //Must be suspended ready
	context *con = (context*)(newpcb->stacktop);
	memset(con, 0, sizeof(context));
	con->fs = 0x10;
	con->gs = 0x10;
	con->ds = 0x10;
	con->es = 0x10;
	con->cs = 0x8;
	con->ebp = (u32int)(newpcb->stackbase);
	con->esp = (u32int)(newpcb->stacktop);
	if(name == "Process1")
	{
		con->eip = (u32int)proc1;
	}
	else if(name == "Process2")
	{
		con->eip = (u32int)proc2;
	}
	else if(name == "Process3")
	{
		con->eip = (u32int)proc3;
	}
	else if(name == "Process4")
	{
		con->eip = (u32int)proc4;
	}
	else
	{
		con->eip = (u32int)proc5;
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
