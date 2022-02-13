#ifndef __TELEMETRY_UART_IO_H__
#define __TELEMETRY_UART_IO_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>

struct device;

int uart_print(const struct device*, uint8_t*, size_t);
int uart_printf(const struct device*, const char*, ...);

#ifdef __cplusplus
}
#endif

#endif