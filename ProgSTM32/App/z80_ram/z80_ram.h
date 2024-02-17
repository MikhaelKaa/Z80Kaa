// Header: z80 ram io
// File Name: _Z80_RAM_IO_.h
// Author: Mikhail Kaa
// Date: 11.11.2023

#ifndef Z80_RAM_IO
#define Z80_RAM_IO

#include "main.h"

#define Z80_DEBUG_ENV (0)

// Значение объема памяти микросхемы M48Z35Y или аналогичной.
// Значение объема памяти установлено в 65536 байт.
#define RAM_LEN (0xffff)
#if (RAM_LEN != 0xffff) 
#error 
#endif

/* Управление Z80 */

// Флаг, установлен если Z80 находится в режиме предоставления шины внешним устройствам.
extern volatile uint8_t z80_is_stopped;

/// @brief Переводит Z80 в режим предоставления шины внешним устройствам.
/// @param none, но использует глобальный флаг z80_is_stopped
void z80_cpu_suspend(void);

/// @brief Возвращает Z80 в режим испольнения кода из BBSRAM.
/// @param  none, но использует глобальный флаг z80_is_stopped
void z80_cpu_resume(void);

/// @brief Сброс Z80.
void z80_cpu_reset(void); 

/// @brief Старт Z80 после записи нового бинарника в BBSRAM.
void z80_cpu_start(void);

/// @brief 
/// @param  
void z80_cpu_reset_low(void); 

/// @brief 
/// @param  
void z80_cpu_reset_high(void); 

/* Операции с памятью */

/// @brief Чтение памяти BBSRAM блоками.
/// @param Buf указатель на буфер в который будут вычитаны байты.
/// @param Addr адрес байта с которого начнется чтение.
/// @param Len количество байт для чтения.
/// @return 0 on 
int z80_ram_read_block(uint8_t *Buf, uint16_t Addr, uint16_t Len); 

/// @brief Запись памяти BBSRAM блоками.
/// @param Buf указатель на буфер из которого будут записаны байты.
/// @param Addr адрес байта с которого начнется запись.
/// @param Len количество байт для записи.
/// @return 0 
int z80_ram_write_block(uint8_t *Buf, uint16_t Addr, uint16_t Len); 

/// @brief Тест заполняем весь объем памяти нулями (стирает).
/// @param  адреса BBSRAM от 0 до (RAM_LEN-1)
void z80_ram_erase_all(void);

#endif /* Z80_RAM_IO */
