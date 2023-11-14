// Header: z80 ram manager
// File Name: z80_ram_io.c
// Author: Mikhail Kaa
// Date: 03.11.2023

#include <stdio.h>
#include "z80_ram_rw.h"
#include "z80_bus_io.h"
#include "retarget.h"

int z80_ram_read_block(uint8_t *buf, uint16_t addr, uint16_t len) {
    if((0 == buf) || (addr+len >= RAM_LEN) || (0 == z80_is_stopped)) return -1;
    uint16_t i = 0;
    while(i != len) {
        buf[i] = z80_ram_read(addr+i);
        i++;
    }
    return 0;
}

int z80_ram_write_block(uint8_t *buf, uint16_t addr, uint16_t len) {
    if((0 == buf) || (addr+len >= RAM_LEN) || (0 == z80_is_stopped)) return -1;
    uint16_t i = 0;
    while(i != len) {
        z80_ram_write(addr+i, buf[i]);
        i++;
    }
    return 0;
} 

void z80_ram_write(uint16_t adr, uint8_t data) {
    //if(!z80_is_stopped) return;
    // Установим сигнал RD в высокий уровень.
    LL_GPIO_SetOutputPin(RD_GPIO_Port, RD_Pin);
    RAMMDELAY(10); // TODO: Возможно задерки можно уменшить, а некоторые вообще убрать.
    // Установим адрес на шине.
    LL_GPIO_WriteOutputPort(RAMM_ADR_PORT, adr);
    RAMMDELAY(10);
    // Установим сигнал MREQ в низкий уровень.
    LL_GPIO_ResetOutputPin(MREQ_GPIO_Port, MREQ_Pin);
    RAMMDELAY(10);
    // WR в низкий уровень.
    LL_GPIO_ResetOutputPin(WR_GPIO_Port, WR_Pin);
    RAMMDELAY(10);
    // Установим данные на шине.
    GPIOA->ODR = data;
    RAMMDELAY(100);
    // WR в высокий уровень.
    LL_GPIO_SetOutputPin(WR_GPIO_Port, WR_Pin);
    RAMMDELAY(10);
    // Установим сигнал MREQ в высокий уровень.
    LL_GPIO_SetOutputPin(MREQ_GPIO_Port, MREQ_Pin);
}

uint8_t z80_ram_read(uint16_t adr) {
    //if(!z80_is_stopped) return 0;
    uint8_t data = 0;
    // WR в высокий уровень.
    LL_GPIO_SetOutputPin(WR_GPIO_Port, WR_Pin);
    RAMMDELAY(10);
    // Установим адрес на шине.
    LL_GPIO_WriteOutputPort(RAMM_ADR_PORT, adr);
    RAMMDELAY(10);
    // Установим сигнал MREQ в низкий уровень.
    LL_GPIO_ResetOutputPin(MREQ_GPIO_Port, MREQ_Pin);
    RAMMDELAY(10);
    // Установим сигнал RD в низкий уровень.
    LL_GPIO_ResetOutputPin(RD_GPIO_Port, RD_Pin);
    RAMMDELAY(10);
    // Вычитываем данные с шины данных.
    data = (uint8_t)(GPIOA->IDR);
    // Установим сигнал MREQ в высокий уровень.
    LL_GPIO_SetOutputPin(MREQ_GPIO_Port, MREQ_Pin);
    return data;
}
