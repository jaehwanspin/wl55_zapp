#include "./lorawan.h"
#include "../app.h"
#include "../device/devices.h"
#include "../telemetry/uart_io.h"
#include "../telemetry/lora_io.h"

#include <zephyr.h>

#include <stdbool.h>

struct k_queue lorawan_data_que;

/**
 * @author Jin
 * @brief 
 * 
 */
static void _init_worker()
{
    k_queue_init(&lorawan_data_que);
}

/**
 * @author Jin
 * @brief 
 * 
 */
static void _loop(const struct app_data* app_data)
{
    struct lorawan_data* data = k_queue_get(&lorawan_data_que, K_FOREVER);

    
}

/**
 * @author Jin
 * @brief 
 * 
 */
void worker_lorawan_handler(const struct app_data* app_data)
{
    _init_worker();

    while (is_app_alive(app_data))
    {
        _loop(app_data);
    }
}