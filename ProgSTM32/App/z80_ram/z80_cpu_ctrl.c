// Header: z80 ram manager cpu ctrl
// File Name: z80_cpu_ctrl.c
// Author: Mikhail Kaa
// Date: 11.11.2023

#include <stdio.h>

#include "z80_bus_io.h"
#include "z80_ram_rw.h"

// Флаг, установлен если Z80 находится в режиме предоставления шины внешним устройствам.
volatile uint8_t z80_is_stopped = 0;

void z80_cpu_suspend(void) {
    #if(Z80_DEBUG_ENV != 1)
    // BUSRQ.
    LL_GPIO_SetPinMode(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    //LL_GPIO_SetPinPull(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_PULL_UP);
    // Выставляем низкий уровнь BUSRQ.
    LL_GPIO_ResetOutputPin(BUSRQ_GPIO_Port, BUSRQ_Pin);
    // Задержка. Вместо ожидания BUSASK.
    RAMMDELAY(65536);
    // С этого момента шины Z80 в HiZ, можем работать.
    z80_bus_data_p2o();
    z80_bus_adr_p2o();
    z80_bus_ctrl_p2o();
    z80_is_stopped = 1;
    printf("z80_cpu_suspend, bus in HiZ\r\n");
    #else
    z80_is_stopped = 1;
    printf("DBG_ENV: z80_cpu_suspend\r\n");
    #endif
}

void z80_cpu_resume(void) {
    #if(Z80_DEBUG_ENV != 1)
    // Переключаем шины в безопасное для Z80 состояние.
    z80_bus_data_p2f();
    z80_bus_adr_p2f();
    z80_bus_ctrl_p2f();
    // Отпускаем BUSRQ, возвращаем шины для Z80.
    LL_GPIO_SetOutputPin(BUSRQ_GPIO_Port, BUSRQ_Pin);
    // BUSRQ input.
    LL_GPIO_SetPinMode(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_MODE_FLOATING);
    // Задержка. Вместо ожидания BUSASK.
    RAMMDELAY(65536);
    z80_is_stopped = 0;
    printf("z80_cpu_resume\r\n");
    #else
    z80_is_stopped = 0;
    printf("DBG_ENV: z80_cpu_resume\r\n");
    #endif
}

void z80_cpu_reset(void) {
    #if(Z80_DEBUG_ENV != 1)
    LL_GPIO_SetOutputPin(Z80_RESET_GPIO_Port, Z80_RESET_Pin);
    RAMMDELAY(1000000);
    LL_GPIO_ResetOutputPin(Z80_RESET_GPIO_Port, Z80_RESET_Pin);
    printf("Z80 reset\r\n");
    #else
    printf("DBG_ENV: z80_cpu_reset\r\n");
    #endif
}

void z80_cpu_start(void) {
    #if(Z80_DEBUG_ENV != 1)
    // Переключаем шины в безопасное для Z80 состояние.
    z80_bus_data_p2f();
    z80_bus_adr_p2f();
    z80_bus_ctrl_p2f();
    // Отпускаем BUSRQ, возвращаем шины для Z80.
    LL_GPIO_SetOutputPin(BUSRQ_GPIO_Port, BUSRQ_Pin);
    // BUSRQ input.
    LL_GPIO_SetPinMode(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_MODE_FLOATING);
    printf("z80_cpu_start\r\n");
    z80_is_stopped = 0;
    z80_cpu_reset();
    #else
    z80_is_stopped = 0;
    printf("DBG_ENV: z80_cpu_start\r\n");
    #endif
}

void z80_cpu_reset_low(void) {
    LL_GPIO_SetOutputPin(Z80_RESET_GPIO_Port, Z80_RESET_Pin);
}


void z80_cpu_reset_high(void) {
    LL_GPIO_ResetOutputPin(Z80_RESET_GPIO_Port, Z80_RESET_Pin);
}
