#ifndef _PCB_H
#define _PCB_H

//extern queue readyQueue;
//extern queue blockedQueue;

typedef struct pcb pcb;

struct pcb{
	char name[9]; //!< name of PCB
	unsigned int proctype; //!< marks type: App (1) or System(0)
	int priority; //!< priority level assigned
	int state; //0 for blocked, 1 for ready, and I guess 2 for running
	int suspension; //0 for suspended, 1 for not
	unsigned char *stacktop;//!< top of stack
	unsigned char *stackbase; //!<base of stack
	//Pointers to other PCBs
	pcb *next; //!<pointer to next PCB in queue
	pcb *prev; //!<pointer to previous PCB in queue
};



pcb *allocatePCB();

//Returns success or error code - 0 success, #>0 error code(s)?
int freePCB(pcb *oldpcb);

pcb* setupPCB(char *pcbname, unsigned int pcbproc, int pcbprior);

pcb* findPCB(char *pcbname);

void insertPCB(pcb *newpcb);

void insertReady(pcb *newpcb);

void insertBlocked(pcb *newpcb);

//Returns success or error code - See above
int removePCB(pcb *oldpcb);

void displayPCB(pcb *apcb);
void displayReady();
void displayBlocked();

#endif
