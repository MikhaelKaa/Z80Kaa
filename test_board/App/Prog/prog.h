// Header: serial programmator
// File Name: prog.h
// Author: Mikhail Kaa
// Date: 13.11.2023

#ifndef PROG
#define PROG

#include "main.h"
#include "z80_ram.h"

extern uint8_t (*prog_out)(uint8_t* Buf, uint16_t Len);

void prog_in(uint8_t* Buf, uint16_t Len);

#endif /* PROG */
