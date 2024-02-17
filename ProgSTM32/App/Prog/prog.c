// Header: serial programmator
// File Name: prog.c
// Author: Mikhail Kaa
// Date: 13.11.2023

#include <stdio.h>
#include <string.h>
#include "prog.h"


#define PACK (((prog_packet_t*)Buf))
#define DATA_LEN (64U)
const uint8_t head = 0x55;
const uint8_t data_len = DATA_LEN;
uint8_t temporary_buf[DATA_LEN] = {0};

void mem_print(uint8_t *buf, uint16_t adr, uint16_t len);

enum commands {
    version = 0,
    answer,
    read,
    write,
    erase_all,
    cpu_suspend,
    cpu_resume,
    cpu_reset,
    cpu_start,
    reset_low,
    reset_high,
    dbg_print,
};

typedef struct prog_packet
{
    uint8_t header;
    uint8_t command;  
    uint8_t cmd_data[5];
    uint8_t crc8;
}prog_packet_t;


//const uint8_t protocol_version[4] = {'v', '0', '0', '1'};
const uint8_t answer_ok[8] = {0x55, answer, 'o', 'k', ' ', ' ', 0x00, 0x00};
const uint8_t answer_fail[8] = {0x55, answer, 'f', 'a', 'i', 'l', 0x00, 0x00};
const uint8_t answer_ver[8] = {0x55, answer, 'v', '0', '0', '1', 0x00, 0x00};


uint8_t (*prog_out)(uint8_t* Buf, uint16_t Len);

void prog_in(uint8_t* Buf, uint16_t Len) {
    uint16_t adr = 0;
    // Все входящие данные размером 8 и заголовком 0x55 интерпретируем как команды.
    if( (Len == sizeof(prog_packet_t)) && (PACK->header = head) ) {
        switch (PACK->command)
        {
        case version:
            printf("command version \r\n");
            if(prog_out) prog_out((uint8_t*)&answer_ver, sizeof(answer_ver));
            break;

        case read:
            adr = *((uint16_t*)&(PACK->cmd_data[0]));
            printf("read from adr=0x%04x\r\n", adr);
            if(z80_ram_read_block(temporary_buf, adr, sizeof(temporary_buf)) /*!= 0*/) {
                printf("z80_ram_read_block error\r\n");
                if(prog_out) prog_out((uint8_t*)&answer_fail, sizeof(answer_fail));
                break;
            }
            mem_print(temporary_buf, 0, sizeof(temporary_buf));
            if(prog_out) prog_out(temporary_buf, sizeof(temporary_buf));
            break;

        case write:
            adr = *((uint16_t*)&(PACK->cmd_data[0]));
            printf("write to adr=0x%04x\r\n", adr);
            if(z80_ram_write_block(temporary_buf, adr, sizeof(temporary_buf)) /*!= 0*/) {
                printf("z80_ram_write_block error\r\n");
                if(prog_out) prog_out((uint8_t*)&answer_fail, sizeof(answer_fail));
                break;
            }
            if(prog_out) prog_out((uint8_t*)&answer_ok, sizeof(answer_ok));
            mem_print(temporary_buf, 0, sizeof(temporary_buf));
            break;

        case cpu_suspend:
            z80_cpu_suspend();
            if(prog_out) prog_out((uint8_t*)&answer_ok, sizeof(answer_ok));
            break;

        case cpu_resume:
            z80_cpu_resume();
            if(prog_out) prog_out((uint8_t*)&answer_ok, sizeof(answer_ok));
            break;

        case cpu_reset:
            z80_cpu_reset();
            if(prog_out) prog_out((uint8_t*)&answer_ok, sizeof(answer_ok));
            break;

        case cpu_start:
            z80_cpu_start();
            if(prog_out) prog_out((uint8_t*)&answer_ok, sizeof(answer_ok));
            break;

        case reset_low:
            z80_cpu_reset_low();
            if(prog_out) prog_out((uint8_t*)&answer_ok, sizeof(answer_ok));
            break;

        case reset_high:
            z80_cpu_reset_high();
            if(prog_out) prog_out((uint8_t*)&answer_ok, sizeof(answer_ok));
            break;

        case erase_all:
            z80_ram_erase_all();
            if(prog_out) prog_out((uint8_t*)&answer_ok, sizeof(answer_ok));
            break;
        
        case dbg_print:
            adr = *((uint16_t*)&(PACK->cmd_data[0]));
            z80_ram_read_block(temporary_buf, adr, sizeof(temporary_buf));
            printf("dbg_print adr=%04x\r\n", adr);
            mem_print(temporary_buf, 0, sizeof(temporary_buf));
            if(prog_out) prog_out((uint8_t*)&answer_ok, sizeof(answer_ok));
            break;
        default:
            break;
        }
    }

    // Все входящие данные размером 64 копируем в временный буфер.
    if(Len == data_len) {
        printf("new 64 bytes\r\n");
        memcpy(temporary_buf, Buf, sizeof(temporary_buf));
        if(prog_out) prog_out((uint8_t*)&answer_ok, sizeof(answer_ok));
    }
    
}

void mem_print(uint8_t *buf, uint16_t adr, uint16_t len) {
    for(uint16_t i = 0; i < len; i++) {
        if(i%16 == 0) {
            printf("\r\n0x%04x ", i+adr);
        }
        printf("%02x ", (buf+adr)[i]);
    }
    printf("\r\n");
}
