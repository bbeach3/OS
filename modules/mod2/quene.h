#ifndef _QUENE_H
#define _QUENE_H

typedef struct queue queue;

struct queue{
	int count;
	pcb *head;
	pcb *tail;
};

#endif
