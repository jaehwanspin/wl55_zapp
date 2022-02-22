#include "./lorawan.h"
#include "../app.h"
#include "../util/custom_typedefs.h"
#include "../device/devices.h"
#include "../telemetry/uart_io.h"
#include "../telemetry/lorawan_io.h"

#include <zephyr.h>
#include <lorawan/lorawan.h>

#include <stdbool.h>

struct k_queue lorawan_data_que;
struct k_poll_event lorawan_events;

/**
 * @author Jin
 * @brief 
 * 
 * @param app_data 
 */
static void _init_lorawan(const struct app_data* app_data)
{
    // k_queue_init(&lorawan_data_que);
    // k_poll_event_init(&lorawan_events,
    //                   K_POLL_TYPE_FIFO_DATA_AVAILABLE,
    //                   K_POLL_MODE_NOTIFY_ONLY,

    int join_res = 0;
    struct lorawan_join_config* cfg = nullptr;
    
    cfg = app_data->lorawan_cfg;
    join_res = lorawan_join(cfg);

    if (join_res < 0) enable_led_error(app_data->devs->led);
}

/**
 * @author Jin
 * @brief 
 * 
 */
static void _init_worker(const struct app_data* app_data)
{
       
}

static void _process_datarate_changed()
{

}

/**
 * @author Jin
 * @brief 
 * 
 */
static void _process_recv_data()
{
    struct lorawan_data* data = k_queue_get(&lorawan_data_que, K_FOREVER);

}

/**
 * @author Jin
 * @brief 
 * 
 */
static void _loop(const struct app_data* app_data)
{
    

}

/**
 * @author Jin
 * @brief 
 * 
 */
void worker_lorawan_handler(const struct app_data* app_data)
{
    _init_worker(app_data);

    while (is_app_alive(app_data))
    {
        _loop(app_data);
    }
}