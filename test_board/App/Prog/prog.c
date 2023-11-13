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
const uint8_t protocol_version[4] = {'v', '0', '0', '1'};
uint8_t rawdata[DATA_LEN] = {0};

uint8_t test_array[32768];

void mem_print(uint8_t *buf, uint16_t len);

enum commands {
    version = 0,
    read,
    write,
    cpu_suspend,
    cpu_resume,
    reset,
};

typedef struct prog_packet
{
    uint8_t header;
    uint8_t command;  
    uint8_t cmd_data[5];
    uint8_t crc8;
}prog_packet_t;


uint8_t (*prog_out)(uint8_t* Buf, uint16_t Len);

void prog_in(uint8_t* Buf, uint16_t Len) {
    printf("packet len=%d\r\n", Len);
    uint16_t adr = 0;
    // Все входящие данные размером 8 и заголовком 0x55 интерпретируем как команды.
    if( (Len == sizeof(prog_packet_t)) && (PACK->header = head) ) {
        printf("header if 0x55\r\n");
        switch (PACK->command)
        {
        case version:
            printf("command version \r\n");
            if(prog_out) prog_out((uint8_t*)&protocol_version, sizeof(protocol_version));
            break;

        case read:
            printf("command read \r\n");
            adr = *((uint16_t*)&(PACK->cmd_data[0]));
            printf("read from adr=%d\r\n", adr);
            memcpy(rawdata, &test_array[adr], sizeof(rawdata));
            if(prog_out) prog_out(rawdata, sizeof(rawdata));
            break;

        case write:
            printf("command write \r\n");
            adr = *((uint16_t*)&(PACK->cmd_data[0]));
            printf("write to adr=%d\r\n", adr);
            memcpy(&test_array[adr], rawdata, sizeof(rawdata));
            break;

        case cpu_suspend:
            printf("command cpu_suspend \r\n");
            break;

        case cpu_resume:
            printf("command cpu_resume \r\n");
            break;

        case reset:
            printf("command reset \r\n");
            break;
        
        default:
            break;
        }
    }

    // Все входящие данные размером 64 копируем в временный буфер.
    if(Len == data_len) {
        memcpy(rawdata, Buf, sizeof(rawdata));
        mem_print(rawdata, sizeof(rawdata));
    }
    
}

void mem_print(uint8_t *buf, uint16_t len) {
    for(uint16_t adr = 0; adr < len; adr++) {
        if(adr%16 == 0) {
            printf("\r\n0x%04x ", adr);
            //printf_flush();
        }
        printf("%02x ", buf[adr]);
    }
    printf("\r\n");
    //printf_flush();
}
