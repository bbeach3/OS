#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct queue queue;

struct queue{
	int count;
	pcb *head;
	pcb *tail;
};

#endif
