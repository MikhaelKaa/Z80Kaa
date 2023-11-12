//01.11.2020
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "retarget.h"
#define USB_CDC_ON
#ifdef USB_CDC_ON
#include "usbd_cdc_if.h"
#endif
// printf buffer
#define BUF_SZ  (8192U)
uint8_t  buf[BUF_SZ];
volatile int counter = 0U;

// uart на отладочной плате
//extern UART_HandleTypeDef huart1;

// Circular update
void printf_flush(void)
{
  if(counter)
  {
    int size = counter;
    #ifdef USB_CDC_ON
    if(0 != CDC_Transmit_FS(buf, size)) return;
    #endif
    //if(HAL_BUSY == HAL_UART_Transmit_DMA(&huart1, buf, size)) return;
    counter = 0;
  }
}

int _write(int fd, char* ptr, int len)
{
  (void)fd;
  int i = 0;
  while (ptr[i] && (i < len)) {
    buf[counter++%BUF_SZ] = (uint8_t)ptr[i++];
  }
  return len;
}
