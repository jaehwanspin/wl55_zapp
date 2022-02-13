#include <drivers/uart.h>
#include <drivers/lora.h>

#include "../telemetry/lora_io.h"

void uart_irq_callback(const struct device* uart_dev, void* user_data)
{
    uint8_t c;

    if (!uart_irq_update(uart_dev))
		return;

    while (uart_irq_rx_ready(uart_dev))
    {
        uart_fifo_read(uart_dev, &c, 1);
        // todo
    }
}

struct lora_data recv_data = { 0, };
void lora_recv_callback(const struct device* lora_dev, uint8_t* data,
                       uint16_t size, int16_t rssi, int8_t snr)
{
    
}

