/**
 * @file Y_uart.c
 * @author yyy
 * @brief uart driver
 * @version 0.1
 * @date 2023.07.28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Y_uart.h"
#include "stdio.h"
#include "string.h"

int fputc(int _c, register FILE *_fp)
{
        while (SCI_getTxFIFOStatus(mySCI0_BASE) == SCI_FIFO_TX15);
                HWREGH(mySCI0_BASE + SCI_O_TXBUF) = _c;
        return _c;
}

int putc(int _c, register FILE *_fp)
{
    while (SCI_getTxFIFOStatus(mySCI0_BASE) == SCI_FIFO_TX15);
            HWREGH(mySCI0_BASE + SCI_O_TXBUF) = _c;
    return _c;
}

int putchar(int data)
{
  while (SCI_getTxFIFOStatus(mySCI0_BASE) == SCI_FIFO_TX15);
  HWREGH(mySCI0_BASE + SCI_O_TXBUF) =data;
  return data;
}

int fputs(const char *_ptr, register FILE *_fp)
{
    unsigned int i, len;
    len = strlen(_ptr);
    for(i=0 ; i<len ; i++)
    {
        while (SCI_getTxFIFOStatus(mySCI0_BASE) == SCI_FIFO_TX15);
        HWREGH(mySCI0_BASE + SCI_O_TXBUF) = (uint8_t) _ptr[i];
    }
    return len;
}
void delay_ms(Uint16 t)
{
    while(t--)
    {
        DEVICE_DELAY_US(1000);
    }
}


