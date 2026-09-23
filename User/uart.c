#include "uart.h"
#include "usart.h"
#include "stdarg.h"

static uint8_t tx_buf[128];

void UART_Sending(const char* fmt,...)
{
    va_list ap;
    va_start (ap,fmt);
    vsnprintf((char*)tx_buf,128,fmt,ap);
    va_end(ap);

    uint8_t len=strlen((char*)tx_buf);
    HAL_UART_Transmit_DMA(&huart1,tx_buf,len);
}
