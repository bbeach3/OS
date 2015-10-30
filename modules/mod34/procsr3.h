#ifndef _PROCSR3_H
#define _PROCSR3_H

#include <system.h>
#include <core/serial.h>

#include "../mpx_supt.h"
#include "../mod2/pcb.h"
#include <../kernel/core/menu.h>
#include "call.h"

#define RC_1 1
#define RC_2 2
#define RC_3 3
#define RC_4 4
#define RC_5 5

pcb* loadr3(char* name);

void proc1();

void proc2();

void proc3();

void proc4();

void proc5();

#endif
