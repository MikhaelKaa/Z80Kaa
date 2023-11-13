// Header: z80 ram manager
// File Name: z80ramm.c
// Author: Mikhail Kaa
// Date: 03.11.2023

#include <stdio.h>
#include "z80ramm_.h"
#include "retarget.h"

// Запись байта в BBSRAM. Проверяет флаг z80_is_stopped, если он не установлен - ничего не делает.
// uint16_t adr - адрес
// uint8_t data - данные
void z80ramm_write(uint16_t adr, uint8_t data) {
    if(!z80_is_stopped) return;

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

// Чтение данных из BBSRAM по адресу. Проверяет флаг z80_is_stopped, если он не установлен - возвращает ноль.
// uint16_t adr - адрес
// возвращаемое значение - данные по адресу.
uint8_t z80ramm_read(uint16_t adr) {
    if(!z80_is_stopped) return 0;
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
