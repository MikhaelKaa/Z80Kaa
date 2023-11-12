// Header: z80 ram manager cpu ctrl
// File Name: z80ramm.c
// Author: Mikhail Kaa
// Date: 11.11.2023

#include <stdio.h>
#include "z80ramm_.h"

// Флаг, установлен если Z80 находится в режиме предоставления шины внешним устройствам.
volatile uint8_t z80_is_stopped = 0;

// Переводит Z80 в режим предоставления шины внешним устройствам.
void z80ramm_suspend_cpu(void) {
    // BUSRQ.
    LL_GPIO_SetPinMode(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetPinPull(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_PULL_UP);
    // Выставляем низкий уровнь BUSRQ.
    LL_GPIO_ResetOutputPin(BUSRQ_GPIO_Port, BUSRQ_Pin);
    // Задержка. Вместо ожидания BUSASK.
    RAMMDELAY(65536);
    // С этого момента шины Z80 в HiZ, можем работать.
    z80ramm_data_pins2output();
    z80ramm_adr_pins2output();
    z80ramm_ctrl_pins2output();
    z80_is_stopped = 1;
    printf("z80ramm_suspend_cpu, bus in HiZ\r\n");
}

// Возвращает Z80 в режим испольнения кода из BBSRAM.
void z80ramm_resume_cpu(void) {
    // Переключаем шины в безопасное для Z80 состояние.
    z80ramm_data_pins2input();
    z80ramm_adr_pins2input();
    z80ramm_ctrl_pins2input();
    // Отпускаем BUSRQ, возвращаем шины для Z80.
    LL_GPIO_SetOutputPin(BUSRQ_GPIO_Port, BUSRQ_Pin);
    // BUSRQ input.
    LL_GPIO_SetPinMode(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_MODE_FLOATING);
    // Задержка. Вместо ожидания BUSASK.
    RAMMDELAY(65536);
    z80_is_stopped = 0;
    printf("z80ramm_resume_cpu\r\n");
}

void z80_reset(void) {
    printf("Z80 reset\r\n");
    LL_GPIO_SetOutputPin(Z80_RESET_GPIO_Port, Z80_RESET_Pin);
    RAMMDELAY(1000000);
    LL_GPIO_ResetOutputPin(Z80_RESET_GPIO_Port, Z80_RESET_Pin);
}
