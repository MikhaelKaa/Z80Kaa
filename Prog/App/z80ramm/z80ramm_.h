// Header: z80 ram manager internal header
// File Name: z80ramm_.h
// Author: Mikhail Kaa
// Date: 11.11.2023

#ifndef _Z80RAMM_
#define _Z80RAMM_

#include "z80ramm.h"

// BUSRQ на пине GPIOA 8
// WR GPIOA 9
// RD GPIOA 10
// MREQ  GPIOA 15
// Шина адреса пин к пину на порту GPIOB
#define RAMM_ADR_PORT (GPIOB)
// Шина данных пин к пину на порту GPIOA
#define RAMM_DATA_PORT (GPIOA)

// Задержка на NOPах. Привязана к частоте MCU.
#define RAMMDELAY(t) for(uint32_t n = 0; n < t; n++) asm("NOP")

#endif /* _Z80RAMM_ */
