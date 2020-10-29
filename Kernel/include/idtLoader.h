#ifndef __IDT_LOADER_H_
#define __IDT_LOADER_H_
#include <stdint.h>
void load_idt();
extern uint64_t _syscallHandler();
#endif