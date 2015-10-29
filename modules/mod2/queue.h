#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct queue queue;

struct queue{
	int count; //!<number of PCBs in the queue
	pcb *head; //!<pointer to first PCB of queue
	pcb *tail; //!<pointer to last PCB of queue
};

#endif
