#include "./event.h"
#include "../app.h"
#include "../device/devices.h"
#include "../telemetry/uart_io.h"

#include <zephyr.h>

#include <stdbool.h>

static void _init_worker()
{

}

static void _loop(const struct app_data* app_data)
{
    uart_printf(app_data->devs->uart, "event_thread\r\n");
    k_sleep(K_MSEC(500));
}

void worker_event_handler(const struct app_data* app_data)
{
    _init_worker();

    while (is_app_alive(app_data))
    {
        _loop(app_data);
    }
}