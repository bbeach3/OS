#ifndef _PCB_H
#define _PCB_H

//extern queue readyQueue;
//extern queue blockedQueue;

typedef struct pcb pcb;

struct pcb{
	char name[9];
	unsigned int proctype;
	int priority;
	int state; //0 for blocked, 1 for ready, and I guess 2 for running
	int suspension; //0 for suspended, 1 for not
	unsigned char *stacktop;
	unsigned char *stackbase;
	//Pointers to other PCBs
	pcb *next;
	pcb *prev;
};

pcb *allocatePCB();

//Returns success or error code - 0 success, #>0 error code(s)?
int freePCB(pcb *oldpcb);

pcb* setupPCB(char *pcbname, unsigned int pcbproc, int pcbprior);

pcb* findPCB(char *pcbname);

void insertPCB(pcb *newpcb);

void insertReady(pcb *newpcb);

void insertBlocked(pcb *newpcb);

//Returns success or error code - See aboce
int removePCB(pcb *oldpcb);

void displayPCB(pcb *apcb);

#endif
