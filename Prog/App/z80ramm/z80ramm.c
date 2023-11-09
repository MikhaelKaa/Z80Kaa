// Header: z80 ram manager
// File Name: z80ramm.c
// Author: Mikhail Kaa
// Date: 03.11.2023
#include <stdio.h>
#include "z80ramm.h"
#include "retarget.h"

// BUSRQ на пине GPIOA 8
// Шина адреса пин к пину на порту GPIOB
// Шина данных пин к пину на порту GPIOA
#define DATA_PORT (D0_GPIO_Port)

void z80ramm_init(void) {
    printf("Z80 ram manager init\r\n");

    // BUSRQ pin настраиваем на выход.
    LL_GPIO_SetPinMode(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    // Выставляем низкий уровнь.
    LL_GPIO_ResetOutputPin(BUSRQ_GPIO_Port, BUSRQ_Pin);

    // Задержка. Вместо ожидания BUSASK.
    for(int n = 0; n<65535; n++) asm("NOP");

    // С этого момента шины Z80 в HiZ, можем работать.

    // Адресная шина.
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_ALL, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_ALL, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_ALL, LL_GPIO_OUTPUT_PUSHPULL);

    // Шина данных.
    LL_GPIO_SetPinMode(DATA_PORT, D0_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(DATA_PORT, D0_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(DATA_PORT, D0_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(DATA_PORT, D0_Pin);

    LL_GPIO_SetPinMode(DATA_PORT, D1_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(DATA_PORT, D1_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(DATA_PORT, D1_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(DATA_PORT, D1_Pin);

    LL_GPIO_SetPinMode(DATA_PORT, D2_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(DATA_PORT, D2_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(DATA_PORT, D2_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(DATA_PORT, D2_Pin);

    LL_GPIO_SetPinMode(DATA_PORT, D3_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(DATA_PORT, D3_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(DATA_PORT, D3_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(DATA_PORT, D3_Pin);

    LL_GPIO_SetPinMode(DATA_PORT, D4_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(DATA_PORT, D4_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(DATA_PORT, D4_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(DATA_PORT, D4_Pin);

    LL_GPIO_SetPinMode(DATA_PORT, D5_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(DATA_PORT, D5_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(DATA_PORT, D5_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(DATA_PORT, D5_Pin);

    LL_GPIO_SetPinMode(DATA_PORT, D6_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(DATA_PORT, D6_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(DATA_PORT, D6_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(DATA_PORT, D6_Pin);

    LL_GPIO_SetPinMode(DATA_PORT, D7_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(DATA_PORT, D7_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(DATA_PORT, D7_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(DATA_PORT, D7_Pin);

    // WR.
    LL_GPIO_SetPinMode(WR_GPIO_Port, WR_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(WR_GPIO_Port, WR_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(WR_GPIO_Port, WR_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(WR_GPIO_Port, WR_Pin, LL_GPIO_PULL_UP);
    LL_GPIO_SetOutputPin(WR_GPIO_Port, WR_Pin);

    // RD.
    LL_GPIO_SetPinMode(RD_GPIO_Port, RD_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RD_GPIO_Port, RD_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RD_GPIO_Port, RD_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(RD_GPIO_Port, RD_Pin, LL_GPIO_PULL_UP);
    LL_GPIO_SetOutputPin(RD_GPIO_Port, RD_Pin);

    // MREQ.
    LL_GPIO_SetPinMode(MREQ_GPIO_Port, MREQ_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(MREQ_GPIO_Port, MREQ_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(MREQ_GPIO_Port, MREQ_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(MREQ_GPIO_Port, MREQ_Pin, LL_GPIO_PULL_UP);
    LL_GPIO_SetOutputPin(MREQ_GPIO_Port, MREQ_Pin);
}

void z80ramm_deinit(void) {
    printf("Z80 ram manager deinit\r\n");

    // Адресная шина.
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_ALL, LL_GPIO_MODE_INPUT);

    // Шина данных.
    LL_GPIO_SetOutputPin(DATA_PORT, D0_Pin);
    LL_GPIO_SetOutputPin(DATA_PORT, D1_Pin);
    LL_GPIO_SetOutputPin(DATA_PORT, D2_Pin);
    LL_GPIO_SetOutputPin(DATA_PORT, D3_Pin);
    LL_GPIO_SetOutputPin(DATA_PORT, D4_Pin);
    LL_GPIO_SetOutputPin(DATA_PORT, D5_Pin);
    LL_GPIO_SetOutputPin(DATA_PORT, D6_Pin);
    LL_GPIO_SetOutputPin(DATA_PORT, D7_Pin);
    //LL_GPIO_SetPinMode(DATA_PORT, D0_Pin, LL_GPIO_MODE_INPUT);
    //LL_GPIO_SetPinMode(DATA_PORT, D1_Pin, LL_GPIO_MODE_INPUT);
    //LL_GPIO_SetPinMode(DATA_PORT, D2_Pin, LL_GPIO_MODE_INPUT);
    //LL_GPIO_SetPinMode(DATA_PORT, D3_Pin, LL_GPIO_MODE_INPUT);
    //LL_GPIO_SetPinMode(DATA_PORT, D4_Pin, LL_GPIO_MODE_INPUT);
    //LL_GPIO_SetPinMode(DATA_PORT, D5_Pin, LL_GPIO_MODE_INPUT);
    //LL_GPIO_SetPinMode(DATA_PORT, D6_Pin, LL_GPIO_MODE_INPUT);
    //LL_GPIO_SetPinMode(DATA_PORT, D7_Pin, LL_GPIO_MODE_INPUT);

    // WR
    LL_GPIO_SetPinMode(WR_GPIO_Port, WR_Pin, LL_GPIO_MODE_INPUT);

    // RD
    LL_GPIO_SetPinMode(RD_GPIO_Port, RD_Pin, LL_GPIO_MODE_INPUT);

    // MREQ
    LL_GPIO_SetPinMode(MREQ_GPIO_Port, MREQ_Pin, LL_GPIO_MODE_INPUT);

    // BUSRQ pin
    // Отпускаем BUSRQ, возвращаем шины для Z80.
    LL_GPIO_SetOutputPin(BUSRQ_GPIO_Port, BUSRQ_Pin);
    LL_GPIO_SetPinMode(BUSRQ_GPIO_Port, BUSRQ_Pin, LL_GPIO_MODE_FLOATING);
}

void z80ramm_write(uint16_t adr, uint8_t data) {
    printf("write ram\r\n");
    printf("Do nothing!!!\r\n");
}

uint8_t z80ramm_read(uint16_t adr) {
    LL_GPIO_SetOutputPin(WR_GPIO_Port, WR_Pin);
    LL_GPIO_ResetOutputPin(RD_GPIO_Port, RD_Pin);
    LL_GPIO_ResetOutputPin(MREQ_GPIO_Port, MREQ_Pin);
    for(int n = 0; n<65535; n++) asm("NOP");
    uint8_t data = 0;
    for(uint16_t adr = 0; adr <= 255; adr++) {
        LL_GPIO_WriteOutputPort(GPIOB, adr);
        for(int n = 0; n<65535; n++) asm("NOP");
        data = (uint8_t)(GPIOA->IDR);
        printf("read ram at adr 0x%04x = 0x%02x\r\n", adr, data);
        //for(int n = 0; n<65535; n++) asm("NOP");
        printf_flush();
        for(int n = 0; n<65535; n++) asm("NOP");
    }
    LL_GPIO_SetOutputPin(WR_GPIO_Port, WR_Pin);
    LL_GPIO_SetOutputPin(RD_GPIO_Port, RD_Pin);
    LL_GPIO_SetOutputPin(MREQ_GPIO_Port, MREQ_Pin);
    return 0;
}
