// Header: z80 ram manager
// File Name: z80ramm.c
// Author: Mikhail Kaa
// Date: 03.11.2023
#include <stdio.h>
#include "z80ramm.h"
#include "retarget.h"

static volatile uint8_t z80_is_stopped = 0;

void z80ramm_suspend_cpu(void) {
    // BUSRQ.
    LL_GPIO_SetPinMode(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetPinPull(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_PULL_UP);
    // Выставляем низкий уровнь BUSRQ.
    LL_GPIO_ResetOutputPin(BUSRQ_GPIO_Port, BUSRQ_Pin);
    // Задержка. Вместо ожидания BUSASK.
    NOPDELAY(65536);
    z80_is_stopped = 1;
    // С этого момента шины Z80 в HiZ, можем работать.
    z80ramm_data_pins2output();
    z80ramm_adr_pins2output();
    z80ramm_ctrl_pins2output();
    printf("Z80 stopped, bus in HiZ\r\n");
}

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
    NOPDELAY(65536);
    z80_is_stopped = 0;
    printf("Z80 resume work\r\n");
}

void z80ramm_write(uint16_t adr, uint8_t data) {
    if(!z80_is_stopped) return;

    // Установим сигнал RD в высокий уровень.
    LL_GPIO_SetOutputPin(RD_GPIO_Port, RD_Pin);
    NOPDELAY(10);
    // Установим адрес на шине.
    LL_GPIO_WriteOutputPort(ADR_PORT, adr);
    NOPDELAY(10);
    // Установим сигнал MREQ в низкий уровень.
    LL_GPIO_ResetOutputPin(MREQ_GPIO_Port, MREQ_Pin);
    NOPDELAY(10);
    // WR в низкий уровень.
    LL_GPIO_ResetOutputPin(WR_GPIO_Port, WR_Pin);
    NOPDELAY(10);
    // Установим данные на шине.
    GPIOA->ODR = data;
    NOPDELAY(100);
    // WR в высокий уровень.
    LL_GPIO_SetOutputPin(WR_GPIO_Port, WR_Pin);
    NOPDELAY(10);
    // Установим сигнал MREQ в высокий уровень.
    LL_GPIO_SetOutputPin(MREQ_GPIO_Port, MREQ_Pin);
    // Установим на шине данных 0xff, так безопаснее.
    //GPIOA->ODR = 0xff;
}

// Чтение данных из BBSRAM по адресу
uint8_t z80ramm_read(uint16_t adr) {
    if(!z80_is_stopped) return 0;
    uint8_t data = 0;
    // WR в высокий уровень.
    LL_GPIO_SetOutputPin(WR_GPIO_Port, WR_Pin);
    NOPDELAY(10);
    // Установим адрес на шине.
    LL_GPIO_WriteOutputPort(ADR_PORT, adr);
    NOPDELAY(10);
    // Установим сигнал MREQ в низкий уровень.
    LL_GPIO_ResetOutputPin(MREQ_GPIO_Port, MREQ_Pin);
    NOPDELAY(10);
    // Установим сигнал RD в низкий уровень.
    LL_GPIO_ResetOutputPin(RD_GPIO_Port, RD_Pin);
    NOPDELAY(10);
    // Вычитываем данные с шины данных.
    data = (uint8_t)(GPIOA->IDR);
    // Установим сигнал MREQ в высокий уровень.
    LL_GPIO_SetOutputPin(MREQ_GPIO_Port, MREQ_Pin);
    return data;
}

void z80ramm_test(void) {
    if(!z80_is_stopped) z80ramm_suspend_cpu();

    uint8_t temp = 0;
    printf("test ram\r\n");
    for(uint16_t adr = 0; adr <= 512; adr++) {
        temp = z80ramm_read(adr);
        printf("read 0x%04x 0x%02x\r\n", adr, temp);
        z80ramm_write(adr, 0);
        if(z80ramm_read(adr) != 0) {
            printf("Error at 0x%04x\r\n", adr);
        } else {
            printf("OK at 0x%04x\r\n", adr);
        }
        z80ramm_write(adr, temp);
        printf("write 0x%04x 0x%02x\r\n", adr, temp);
        if(z80ramm_read(adr) != temp) {
            printf("Error at 0x%04x\r\n", adr);
        } else {
            printf("OK at 0x%04x\r\n", adr);
        }
        if(adr%32 == 0) printf_flush();
        NOPDELAY(10240);
        }

    z80ramm_resume_cpu();
    /*for(uint16_t adr = 0; adr <= 512; adr++) {
        data = z80ramm_read(adr);
        if(adr%16 == 0) {
            printf("\r\n0x%04x ", adr);
            printf_flush();
        }
        printf("%02x ", data);
    }
    printf("\r\n");
    printf_flush();*/
}

void mem_read_test(void) {
    if(!z80_is_stopped) z80ramm_suspend_cpu();
    uint8_t data = 0;
    for(uint16_t adr = 0; adr <= 512; adr++) {
        data = z80ramm_read(adr);
        if(adr%16 == 0) {
            printf("\r\n0x%04x ", adr);
            printf_flush();
        }
        printf("%02x ", data);
    }
    printf("\r\n");
    printf_flush();
    z80ramm_resume_cpu();
}

void mem_write_test(void) {
    if(!z80_is_stopped) z80ramm_suspend_cpu();
    for(uint16_t adr = 0; adr <= 512; adr++) {
        z80ramm_write(adr, adr);
        if(adr%16 == 0) {
            printf("\r\n0x%04x ", adr);
            printf_flush();
        }
        printf("%02x ", (uint8_t)adr);
    }
    printf("\r\ntest data written\r\n");
    printf_flush();
    z80ramm_resume_cpu();
}


void mem_erase_test(void) {
    if(!z80_is_stopped) z80ramm_suspend_cpu();
    for(uint16_t adr = 0; adr <= 32767; adr++) {
        z80ramm_write(adr, 0);
        if(z80ramm_read(adr) != 0) printf("Erase error@0x%04x\r\n", adr);
    }
    printf("\r\nBBSRAM erased\r\n");
    printf_flush();
    z80ramm_resume_cpu();
}
