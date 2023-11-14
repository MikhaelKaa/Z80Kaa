// Header: z80 ram io internal header
// File Name: z80_ram_io_.h
// Author: Mikhail Kaa
// Date: 11.11.2023

#ifndef _Z80_RAM_IO_
#define _Z80_RAM_IO_

#include "z80_ram.h"

/* Управление GPIO */

// BUSRQ на пине GPIOA 8
// WR GPIOA 9
// RD GPIOA 10
// MREQ  GPIOA 15
// Шина адреса пин к пину на порту GPIOB
#define RAMM_ADR_PORT (GPIOB)
// Шина данных пин к пину на порту GPIOA
#define RAMM_DATA_PORT (GPIOA)

/// @brief Выводы шины адреса в воздухе.
/// @param  A0..A15
void z80_bus_adr_p2f(void);

/// @brief Выводы шины адреса на выход, пушпулл.
/// @param  A0..A15
void z80_bus_adr_p2o(void);

/// @brief Выводы шины данных в воздухе.
/// @param  D0..D7
void z80_bus_data_p2f(void);

/// @brief Выводы шины данных на выход, открытый коллектор.
/// @param  D0..D7
void z80_bus_data_p2o(void);

/// @brief Выводы управления  в воздухе.
/// @param  WR, RD, MREQ
void z80_bus_ctrl_p2f(void);

/// @brief Выводы управления  на выход, пушпулл.
/// @param  WR, RD, MREQ
void z80_bus_ctrl_p2o(void);

#endif /* _Z80_RAM_IO_ */
