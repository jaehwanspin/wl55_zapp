#include "../telemetry/lorawan_io.h"
#include "../util/custom_typedefs.h"

#include <zephyr.h>
#include <drivers/uart.h>
#include <drivers/lora.h>

#include <string.h>

// from workers/at_command.c
extern struct k_queue uart_data_que;

// from workers/lorawan.c
extern struct k_queue lorawan_data_que;

#define UART_RX_BUF_POOL_MAX_SIZE 512

uint8_t uart_rx_buf_pool[UART_RX_BUF_POOL_MAX_SIZE] = { 0, };
size_t uart_rx_buf_pool_pos = 0;

#define LORAWAN_RX_DATA_POOL_MAX_SIZE 512

struct lorawan_data lorawan_rx_data_pool[LORAWAN_RX_DATA_POOL_MAX_SIZE] = { 0, };
size_t lorawan_rx_data_pool_pos = 0;

/**
 * @author Jin
 * @brief 
 * 
 * @return uint8_t* 
 */
static uint8_t* _get_available_buf_addr()
{
    uint8_t* ret = &uart_rx_buf_pool[uart_rx_buf_pool_pos++];
    if (uart_rx_buf_pool_pos == UART_RX_BUF_POOL_MAX_SIZE)
        uart_rx_buf_pool_pos = 0;
    return ret;
}

/**
 * @author Jin
 * @brief 
 * 
 * @return struct lorawan_data* 
 */
static struct lorawan_data* _get_available_data_addr()
{
    struct lorawan_data* ret = &lorawan_rx_data_pool[lorawan_rx_data_pool_pos++];
    if (lorawan_rx_data_pool_pos == LORAWAN_RX_DATA_POOL_MAX_SIZE)
        lorawan_rx_data_pool_pos = 0;
    return ret;
}


/**
 * @author Jin
 * @brief 
 * 
 * @param uart_dev 
 * @param user_data 
 */
void uart_irq_callback_handler(const struct device* uart_dev, void* user_data)
{
    uint8_t* c = _get_available_buf_addr();

    if (!uart_irq_update(uart_dev))
		return;

    while (uart_irq_rx_ready(uart_dev))
    {
        uart_fifo_read(uart_dev, c, sizeof(uint8_t));
        // to workers/at_command.c - _loop()
        k_queue_append(&uart_data_que, c);
    }
}

/**
 * @author Jin
 * @brief LoRaWAN data receive callback
 * 
 */
void lorawan_recv_callback_handler(uint8_t port, bool data_pending,
                                const struct device* lora_dev, uint8_t* data,
                                uint16_t size, int16_t rssi, int8_t snr)
{
    struct lorawan_data* lora_recv_data = _get_available_data_addr();
    memcpy(lora_recv_data->data, data, size);
    lora_recv_data->port = port;
    lora_recv_data->data_pending = data_pending;
    lora_recv_data->size = size;
    lora_recv_data->rssi = rssi;
    lora_recv_data->snr = snr;

    k_queue_append(&lorawan_data_que, lora_recv_data);
}

