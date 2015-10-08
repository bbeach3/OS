#include "mpx_supt.h"
#include "pcb.h"
#include "queue.h"

/*TO DO FOR MODULE 2:
	-Fine-tune/bugfix any and all methods located in pcb.c
		-Ensure we have covered any and all error cases when necessary, giving 			them appropriate error codes
	-Determine what exactly needs to be done concerning the queues, and if we want 		to even implement a two-queue system
	-Determine if the queues should remain doubly-linked, or shift to become 		singly-linked - They don't appear to do anything but complicate methods as of 		right now, but who knows
	-Implement selectability of said methods into menu.c
	-Update the manuals and documentation for any new files or new methods in 		existing files
*/
struct queue *readyqueue = sys_alloc_mem(sizeof(struct queue));
struct queue *blockedqueue = sys_alloc_mem(sizeof(struct queue)); 

struct pcb *allocatePCB()
{
	struct pcb *newPCB = sys_alloc_mem(sizeof(struct pcb));

	if(newPCB != NULL)
	{
		return newPCB;
	}
	else
	{
		return NULL;
	}
}

int freePCB(struct pcb *oldpcb)
{
	sys_free_mem(oldpcb->name);
	sys_free_mem(oldpcb->proctype);
	sys_free_mem(oldpcb->priority);
	return sys_free_mem(oldpcb);
}

struct pcb *setupPCB(char *pcbname, unsigned int pcbproc, int pcbprior)
{
	struct pcb *blankPCB = allocatePCB();

	if(blankPCB == NULL)
	{
		return NULL;
	}

	blankPCB->name = pcbname;
	blankPCB->proctype = pcbproc;
	blankPCB->priority = pcbprior;

	//There has to be more/other ways or errorchecking here, but here's a start
	if(blankPCB->name == NULL || blankPCB.prototype == NULL || blankPCB.priority == NULL)
	{
		return NULL;
	}
}

struct pcb *findPCB(char *pcbname)
{
	struct pcb *pcbpointer;

	pcbpointer = readyqueue->head;
	while(pcbpointer != NULL)
	{
		if(strcmp(pcbname, pcbpointer->pcbname) == 0)
		{
			return pcbpointer;
		}

		pcbpointer = pcbpointer->head;
			
	}

	pcbpointer = blockedqueue->head;

	while(pcbpointer != NULL)
	{
		if(strcmp(pcbname, pcbpointer->pcbname) == 0)
		{
			return pcbpointer;
		}

		pcbpointer = pcbpointer->head;
	}

	return NULL;
	//Cycles through both queues, and returns a pcb pointer if it finds a match - If not, it'll return null at the end of the queue
}

void insertPCB(struct pcb *newpcb)
{
	//Big issue here is determining whether we need to insert this into the readyqueue or the blockedqueue - From there, it's relatively simple to insert into the blockedqueue (Just plug it onto tail->next and have newpcb attach back to tail) and only marginally moreso into the readyqueue (Search queue via priority, locate where the first pcb that has a lower priority than newpcb, then place newpcb after the pcb we found)
}

int removePCB(struct pcb *oldpcb)
{
	struct pcb *foundpcb = findPCB(oldpcb->name);

	if(foundpcb == NULL)
	{
		//Return an error code stating that the PCB in question does not exist
	}

	(foundpcb->prev)->next = foundpcb->next;
	(foundpcb->next)->prev = foundpcb->prev;
}
