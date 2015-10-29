#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include <modules/mod34/call.h>
#include <modules/mod2/pcb.h>

extern pcb* cop;
extern context* oldcon;

/*
  Procedure..: init_irq
  Description..: Installs the initial interrupt handlers for
      the first 32 irq lines. Most do a panic for now.
*/
void init_irq(void);

/*
  Procedure..: init_pic
  Description..: Initializes the programmable interrupt controllers
      and performs the necessary remapping of IRQs. Leaves interrupts
      turned off.
*/
void init_pic(void);

#endif
