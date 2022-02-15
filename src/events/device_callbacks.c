#include "../telemetry/lora_io.h"

#include <zephyr.h>
#include <drivers/uart.h>
#include <drivers/lora.h>

// from workers/at_command.c
extern struct k_queue uart_data_que;

/**
 * @author Jin
 * @brief 
 * 
 * @param uart_dev 
 * @param user_data 
 */
void uart_irq_callback_handler(const struct device* uart_dev, void* user_data)
{
    uint8_t c;

    if (!uart_irq_update(uart_dev))
		return;

    while (uart_irq_rx_ready(uart_dev))
    {
        uart_fifo_read(uart_dev, &c, 1);
        // to workers/at_command.c - _loop()
        k_queue_append(&uart_data_que, &c);
    }
}

/**
 * @author Jin
 * @brief 
 * 
 */
struct lora_data recv_data = { 0, };
void lora_recv_callback_handler(const struct device* lora_dev, uint8_t* data,
                                uint16_t size, int16_t rssi, int8_t snr)
{
    
}

