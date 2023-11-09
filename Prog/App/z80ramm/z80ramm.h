// Header: z80 ram manager
// File Name: z80ramm.h
// Author: Mikhail Kaa
// Date: 03.11.2023

#ifndef Z80RAMM
#define Z80RAMM

#include "main.h"

void z80ramm_init(void);
void z80ramm_deinit(void);
void z80ramm_write(uint16_t adr, uint8_t data);
uint8_t z80ramm_read(uint16_t adr);

void control(uint8_t cmd);

#endif /* Z80RAMM */
