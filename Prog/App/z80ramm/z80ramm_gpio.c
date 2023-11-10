// Header: z80 ram manager gpio control
// File Name: z80ramm_gpio.c
// Author: Mikhail Kaa
// Date: 10.11.2023

/*
Знаю, что тут рука-лицо, но мне лень делать по другому.
Не стал разбираться, почему группой не удается назначить пины...
*/

#include <stdio.h>
#include "z80ramm.h"
#include "retarget.h"

void z80ramm_adr_pins2output(void){
// Адресная шина.
    LL_GPIO_SetPinMode(ADR_PORT, A0_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A0_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A0_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A1_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A1_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A1_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A2_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A2_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A2_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A3_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A3_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A3_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A4_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A4_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A4_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A5_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A5_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A5_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A6_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A6_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A6_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A7_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A7_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A7_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A8_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A8_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A8_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A9_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A9_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A9_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A10_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A10_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A10_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A11_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A11_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A11_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A12_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A12_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A12_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A13_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A13_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A13_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A14_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A14_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A14_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(ADR_PORT, A15_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(ADR_PORT, A15_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(ADR_PORT, A15_Pin, LL_GPIO_OUTPUT_PUSHPULL);
}

void z80ramm_adr_pins2input(void) {
    LL_GPIO_SetPinMode(ADR_PORT, A0_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A1_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A2_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A3_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A4_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A5_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A6_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A7_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A8_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A9_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A10_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A11_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A12_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A13_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A14_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(ADR_PORT, A15_Pin, LL_GPIO_MODE_FLOATING);
}

void z80ramm_data_pins2input(void) {
    LL_GPIO_SetPinMode(DATA_PORT, D0_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(DATA_PORT, D1_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(DATA_PORT, D2_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(DATA_PORT, D3_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(DATA_PORT, D4_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(DATA_PORT, D5_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(DATA_PORT, D6_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(DATA_PORT, D7_Pin, LL_GPIO_MODE_FLOATING);
    
    /*LL_GPIO_SetOutputPin(DATA_PORT, D0_Pin);
    LL_GPIO_SetOutputPin(DATA_PORT, D1_Pin);
    LL_GPIO_SetOutputPin(DATA_PORT, D2_Pin);
    LL_GPIO_SetOutputPin(DATA_PORT, D3_Pin);
    LL_GPIO_SetOutputPin(DATA_PORT, D4_Pin);
    LL_GPIO_SetOutputPin(DATA_PORT, D5_Pin);
    LL_GPIO_SetOutputPin(DATA_PORT, D6_Pin);
    LL_GPIO_SetOutputPin(DATA_PORT, D7_Pin);*/
}
void z80ramm_data_pins2output(void) {
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
}
void z80ramm_ctrl_pins2input(void) {
    // WR.
    LL_GPIO_SetOutputPin(WR_GPIO_Port, WR_Pin);
    LL_GPIO_SetPinMode(WR_GPIO_Port, WR_Pin, LL_GPIO_MODE_FLOATING);
    // RD.
    LL_GPIO_SetOutputPin(RD_GPIO_Port, RD_Pin);
    LL_GPIO_SetPinMode(RD_GPIO_Port, RD_Pin, LL_GPIO_MODE_FLOATING);
    // MREQ.
    LL_GPIO_SetOutputPin(MREQ_GPIO_Port, MREQ_Pin);
    LL_GPIO_SetPinMode(MREQ_GPIO_Port, MREQ_Pin, LL_GPIO_MODE_FLOATING);
}

void z80ramm_ctrl_pins2output(void) {
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
