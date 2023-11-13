// Header: z80 ram manager тестовые функции, для отладки.
// File Name: z80ramm.c
// Author: Mikhail Kaa
// Date: 11.11.2023

#include <stdio.h>
#include "z80ramm_.h"
#include "retarget.h"

// Тест чтения записи памяти.
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
        RAMMDELAY(10240);
        }

    z80ramm_resume_cpu();
}

// Тест выводит в консоль первые 512 байт.
void mem_read_test(void) {
    if(!z80_is_stopped) z80ramm_suspend_cpu();
    uint8_t data = 0;
    for(uint16_t adr = 0; adr <= 511; adr++) {
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

// Тест заполняет первые 512 байт памяти значениями равными первым восьми битам адреса.
void mem_write_test(void) {
    if(!z80_is_stopped) z80ramm_suspend_cpu();
    for(uint16_t adr = 0; adr <= 511; adr++) {
        z80ramm_write(adr, (uint8_t)adr);
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

// Тест заполняем весь объем памяти нулями (стирает).
void mem_erase_test(void) {
    if(!z80_is_stopped) z80ramm_suspend_cpu();
    for(uint16_t adr = 0; adr <= (RAM_LEN-1); adr++) {
        z80ramm_write(adr, 0);
        if(z80ramm_read(adr) != 0) printf("Erase error@0x%04x\r\n", adr);
    }
    printf("\r\nBBSRAM erased\r\n");
    printf_flush();
    z80ramm_resume_cpu();
}
