// Header: z80 ram manager gpio control
// File Name: z80_bus_cfg.c
// Author: Mikhail Kaa
// Date: 10.11.2023

#include <stdio.h>
#include "z80_bus_io.h"

// Выводы шины адреса в воздухе.
void z80_bus_adr_p2f(void) {
    #if(Z80_DEBUG_ENV != 1)
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A0_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A1_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A2_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A3_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A4_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A5_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A6_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A7_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A8_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A9_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A10_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A11_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A12_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A13_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A14_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A15_Pin, LL_GPIO_MODE_FLOATING);
    #else
    printf("DBG_ENV: z80_bus_adr_p2f\r\n");
    #endif
}

// Выводы шины адреса на выход, пушпулл.
void z80_bus_adr_p2o(void) {
    #if(Z80_DEBUG_ENV != 1)
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A0_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A0_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A0_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A1_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A1_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A1_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A2_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A2_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A2_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A3_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A3_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A3_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A4_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A4_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A4_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A5_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A5_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A5_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A6_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A6_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A6_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A7_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A7_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A7_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A8_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A8_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A8_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A9_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A9_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A9_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A10_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A10_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A10_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A11_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A11_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A11_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A12_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A12_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A12_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A13_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A13_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A13_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A14_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A14_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A14_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinMode(RAMM_ADR_PORT, A15_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_ADR_PORT, A15_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_ADR_PORT, A15_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    #else
    printf("DBG_ENV: z80_bus_adr_p2o\r\n");
    #endif
}

// Выводы шины данных в воздухе.
void z80_bus_data_p2f(void) {
    #if(Z80_DEBUG_ENV != 1)
    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D0_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D1_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D2_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D3_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D4_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D5_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D6_Pin, LL_GPIO_MODE_FLOATING);
    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D7_Pin, LL_GPIO_MODE_FLOATING);
    #else
    printf("DBG_ENV: z80_bus_data_p2f\r\n");
    #endif
}

// Выводы шины данных на выход, открытый коллектор.
void z80_bus_data_p2o(void) {
    #if(Z80_DEBUG_ENV != 1)
    // Шина данных.
    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D0_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_DATA_PORT, D0_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_DATA_PORT, D0_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(RAMM_DATA_PORT, D0_Pin);

    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D1_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_DATA_PORT, D1_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_DATA_PORT, D1_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(RAMM_DATA_PORT, D1_Pin);

    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D2_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_DATA_PORT, D2_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_DATA_PORT, D2_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(RAMM_DATA_PORT, D2_Pin);

    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D3_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_DATA_PORT, D3_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_DATA_PORT, D3_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(RAMM_DATA_PORT, D3_Pin);

    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D4_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_DATA_PORT, D4_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_DATA_PORT, D4_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(RAMM_DATA_PORT, D4_Pin);

    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D5_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_DATA_PORT, D5_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_DATA_PORT, D5_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(RAMM_DATA_PORT, D5_Pin);

    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D6_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_DATA_PORT, D6_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_DATA_PORT, D6_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(RAMM_DATA_PORT, D6_Pin);

    LL_GPIO_SetPinMode(RAMM_DATA_PORT, D7_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RAMM_DATA_PORT, D7_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RAMM_DATA_PORT, D7_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetOutputPin(RAMM_DATA_PORT, D7_Pin);
    #else
    printf("DBG_ENV: z80_bus_data_p2o\r\n");
    #endif
}

// Выводы управления WR, RD, MREQ в воздухе.
void z80_bus_ctrl_p2f(void) {
    #if(Z80_DEBUG_ENV != 1)
    // WR.
    LL_GPIO_SetOutputPin(WR_GPIO_Port, WR_Pin);
    LL_GPIO_SetPinMode(WR_GPIO_Port, WR_Pin, LL_GPIO_MODE_FLOATING);
    // RD.
    LL_GPIO_SetOutputPin(RD_GPIO_Port, RD_Pin);
    LL_GPIO_SetPinMode(RD_GPIO_Port, RD_Pin, LL_GPIO_MODE_FLOATING);
    // MREQ.
    LL_GPIO_SetOutputPin(MREQ_GPIO_Port, MREQ_Pin);
    LL_GPIO_SetPinMode(MREQ_GPIO_Port, MREQ_Pin, LL_GPIO_MODE_FLOATING);
    #else
    printf("DBG_ENV: z80_bus_ctrl_p2f\r\n");
    #endif
}

// Выводы управления WR, RD, MREQ на выход, пушпулл.
void z80_bus_ctrl_p2o(void) {
    #if(Z80_DEBUG_ENV != 1)
    // WR.
    LL_GPIO_SetPinMode(WR_GPIO_Port, WR_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(WR_GPIO_Port, WR_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(WR_GPIO_Port, WR_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetOutputPin(WR_GPIO_Port, WR_Pin);

    // RD.
    LL_GPIO_SetPinMode(RD_GPIO_Port, RD_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(RD_GPIO_Port, RD_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RD_GPIO_Port, RD_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetOutputPin(RD_GPIO_Port, RD_Pin);

    // MREQ.
    LL_GPIO_SetPinMode(MREQ_GPIO_Port, MREQ_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(MREQ_GPIO_Port, MREQ_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(MREQ_GPIO_Port, MREQ_Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetOutputPin(MREQ_GPIO_Port, MREQ_Pin);
    #else
    printf("DBG_ENV: z80_bus_ctrl_p2o\r\n");
    #endif
}
