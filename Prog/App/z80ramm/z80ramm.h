// Header: z80 ram manager
// File Name: z80ramm.h
// Author: Mikhail Kaa
// Date: 03.11.2023

#ifndef Z80RAMM
#define Z80RAMM

#include "main.h"

// Задержка на NOPах. Привязана к частоте MCU.
#define NOPDELAY(t) for(int n = 0; n < t; n++) asm("NOP")

// BUSRQ на пине GPIOA 8
// Шина адреса пин к пину на порту GPIOB
#define ADR_PORT (GPIOB)
// Шина данных пин к пину на порту GPIOA
#define DATA_PORT (GPIOA)

void z80ramm_write(uint16_t adr, uint8_t data);
uint8_t z80ramm_read(uint16_t adr);
void z80ramm_test(void);

void z80ramm_suspend_cpu(void);
void z80ramm_resume_cpu(void);

void z80ramm_adr_pins2input(void);
void z80ramm_adr_pins2output(void);
void z80ramm_data_pins2input(void);
void z80ramm_data_pins2output(void);
void z80ramm_ctrl_pins2input(void);
void z80ramm_ctrl_pins2output(void);

#endif /* Z80RAMM */
