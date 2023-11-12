// Header: z80 ram manager
// File Name: z80ramm.h
// Author: Mikhail Kaa
// Date: 11.11.2023

#ifndef Z80RAMM
#define Z80RAMM

#include "main.h"

// Флаг, установлен если Z80 находится в режиме предоставления шины внешним устройствам.
extern volatile uint8_t z80_is_stopped;

// Значение объема памяти микросхемы M48Z35Y или аналогичной.
#define RAM_LEN (32786U)



/* Чтение запись блоками. */

void z80ram_block_read(uint8_t *buf, uint16_t addr, uint16_t len); 
void z80ram_block_write(uint8_t *buf, uint16_t addr, uint16_t len); 

/* Чтение запись по одному байту. */

void z80ramm_write(uint16_t adr, uint8_t data);
uint8_t z80ramm_read(uint16_t adr);

/* Управление Z80 */

void z80_reset(void); 
void z80ramm_suspend_cpu(void);
void z80ramm_resume_cpu(void);

/* Управление GPIO */

void z80ramm_adr_pins2input(void);
void z80ramm_adr_pins2output(void);
void z80ramm_data_pins2input(void);
void z80ramm_data_pins2output(void);
void z80ramm_ctrl_pins2input(void);
void z80ramm_ctrl_pins2output(void);

/* Функции для отладки. */

void z80ramm_test(void);
void mem_read_test(void);
void mem_write_test(void);
void mem_erase_test(void);

#endif /* Z80RAMM */
