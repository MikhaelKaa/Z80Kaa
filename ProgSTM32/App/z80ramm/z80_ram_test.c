// Header: z80 ram manager тестовые функции, для отладки.
// File Name: z80_ram_test.c
// Author: Mikhail Kaa
// Date: 11.11.2023

#include <stdio.h>
#include "z80_ram_rw.h"
#include "retarget.h"

void z80_ram_test(void) {
    if(!z80_is_stopped) z80_cpu_suspend();

    uint8_t temp = 0;
    printf("test ram\r\n");
    for(uint16_t adr = 0; adr <= 512; adr++) {
        temp = z80_ram_read(adr);
        printf("read 0x%04x 0x%02x\r\n", adr, temp);
        z80_ram_write(adr, 0);
        if(z80_ram_read(adr) != 0) {
            printf("Error at 0x%04x\r\n", adr);
        } else {
            printf("OK at 0x%04x\r\n", adr);
        }
        z80_ram_write(adr, temp);
        printf("write 0x%04x 0x%02x\r\n", adr, temp);
        if(z80_ram_read(adr) != temp) {
            printf("Error at 0x%04x\r\n", adr);
        } else {
            printf("OK at 0x%04x\r\n", adr);
        }
        if(adr%32 == 0) printf_flush();
        RAMMDELAY(10240);
        }

    z80_cpu_resume();
}

void z80_ram_read_test(void) {
    if(!z80_is_stopped) z80_cpu_suspend();
    uint8_t data = 0;
    for(uint16_t adr = 0; adr <= 511; adr++) {
        data = z80_ram_read(adr);
        if(adr%16 == 0) {
            printf("\r\n0x%04x ", adr);
            printf_flush();
        }
        printf("%02x ", data);
    }
    printf("\r\n");
    printf_flush();
    z80_cpu_resume();
}

void z80_ram_write_test(void) {
    if(!z80_is_stopped) z80_cpu_suspend();
    for(uint16_t adr = 0; adr <= 511; adr++) {
        z80_ram_write(adr, (uint8_t)adr);
        if(adr%16 == 0) {
            printf("\r\n0x%04x ", adr);
            printf_flush();
        }
        printf("%02x ", (uint8_t)adr);
    }
    printf("\r\ntest data written\r\n");
    printf_flush();
    z80_cpu_resume();
}


void z80_ram_erase_all(void) {
    if(!z80_is_stopped) z80_cpu_suspend();
    for(uint16_t adr = 0; adr <= (RAM_LEN-1); adr++) {
        z80_ram_write(adr, 0);
        if(z80_ram_read(adr) != 0) printf("Erase error@0x%04x\r\n", adr);
    }
    printf("\r\nBBSRAM erased\r\n");
    printf_flush();
    z80_cpu_resume();
}
