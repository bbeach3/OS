#ifndef _PCB_H
#define _PCB_H

struct pcb
{
	char *name;
	unsigned int proctype;
	int priority;
	int state;
	unsigned char *stacktop;
	unsigned char *stackbase;
	//Pointers to other PCBs
	pcb *next;
	pcb *prev;
};

pcb *allocatePCB();

//Returns success or error code - 0 success, #>0 error code(s)?
int freePCB(pcb *oldpcb);

pcb *setupPCB(char *pcbname, unsigned int pcbproc, int pcbprior);

pcb *findPCB(char *pcbname);

void insertPCB(pcb *newpcb);

//Returns success or error code - See aboce
int removePCB(pcb *oldpcb);

#endif
