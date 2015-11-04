#ifndef _PCB_H
#define _PCB_H
#include "pcb.h"
#include "../mpx_supt.h"
#include <string.h>
#include <core/serial.h>
#include "../mod34/call.h"

typedef struct pcb pcb;

struct pcb{
	char name[9]; //!< name of PCB
	unsigned int proctype; //!< marks type: App (1) or System(0)
	int priority; //!< priority level assigned
	int state; //0 for blocked, 1 for ready, and I guess 2 for running
	int suspension; //0 for suspended, 1 for not
	unsigned char *stacktop;//!< top of stack
	unsigned char *stack[1024]; //!<base of stack
	//Pointers to other PCBs
	pcb *next; //!<pointer to next PCB in queue
	pcb *prev; //!<pointer to previous PCB in queue
};

typedef struct queue queue;

struct queue{
	int count; //!<number of PCBs in the queue
	pcb *head; //!<pointer to first PCB of queue
	pcb *tail; //!<pointer to last PCB of queue
};

extern queue *readyQueue;
extern queue *blockedQueue;

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
