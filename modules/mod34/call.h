#ifndef _CALL_H
#define _CALL_H

typedef struct context context;

struct context {
	u32int gs, fs, es, ds;
	u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	u32int eip, cs, eflags;
};

u32int* sys_call(context *registers);

#endif
