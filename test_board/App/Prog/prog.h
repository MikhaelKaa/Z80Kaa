// Header: serial programmator
// File Name: prog.h
// Author: Mikhail Kaa
// Date: 13.11.2023

#ifndef PROG
#define PROG

#include "main.h"

extern uint8_t (*prog_out)(uint8_t*, uint16_t);

void prog_in(uint8_t* Buf, uint16_t Len);

#endif /* PROG */
