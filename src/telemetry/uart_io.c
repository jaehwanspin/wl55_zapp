#include "./uart_io.h"

#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include <drivers/uart.h>

#define UART_PRINTF_MAX_SIZE (size_t)256U

char format_write_buf[UART_PRINTF_MAX_SIZE] = { 0, };

int uart_print(const struct device* uart_dev, uint8_t* data, size_t size)
{
     for (int i = 0; i < size; i++)
		uart_poll_out(uart_dev, data[i]);
     return size;
}

int uart_printf(const struct device* uart_dev, const char* fmt, ...)
{
     va_list va_args;

     va_start(va_args, fmt);
     vsprintf(format_write_buf, fmt, va_args);
     va_end(va_args);

     return uart_print(uart_dev, (uint8_t*)format_write_buf,
          strlen(format_write_buf));
}