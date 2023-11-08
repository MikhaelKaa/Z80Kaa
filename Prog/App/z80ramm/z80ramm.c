// Header: z80 ram manager
// File Name: z80ramm.c
// Author: Mikhail Kaa
// Date: 03.11.2023
#include <stdio.h>
#include "z80ramm.h"

//void group_pin_set_out(GPIO_TypeDef *GPIOx, uint32_t Pin);
void group_pin_set_out(GPIO_TypeDef *GPIOx, uint32_t Pin) {
    LL_GPIO_SetPinMode(GPIOx, Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(GPIOx, Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(GPIOx, Pin, LL_GPIO_OUTPUT_PUSHPULL); 
}

void group_pin_set_in(GPIO_TypeDef *GPIOx, uint32_t Pin) {
    LL_GPIO_SetPinMode(GPIOx, Pin, LL_GPIO_MODE_INPUT);
}

void group_pin_set_hiz(GPIO_TypeDef *GPIOx, uint32_t Pin) {
    LL_GPIO_SetPinMode(GPIOx, Pin, LL_GPIO_MODE_FLOATING);
}


void z80ramm_init(void) {
    printf("z80ramm_init\r\n");
    group_pin_set_out(GPIOA, LL_GPIO_PIN_0);
}

void z80ramm_deinit(void) {
    printf("z80ramm_deinit\r\n");
    group_pin_set_hiz(GPIOA, LL_GPIO_PIN_0);
}

void z80ramm_write(uint16_t adr, uint8_t data) {
    printf("pin write\r\n");
    LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_0);
    for(int n = 0; n<65535; n++) asm("NOP");
    LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_0);
}

uint8_t z80ramm_read(uint16_t adr) {
    int read = LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0);
    printf("pin read %d\r\n", read);
    return 0;
}
