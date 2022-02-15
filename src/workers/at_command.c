#include "./at_command.h"
#include "../app.h"
#include "../device/devices.h"
#include "../telemetry/uart_io.h"

#include "../iface/at_command.h"

#include "../at/mode.h"
#include "../at/retry.h"
#include "../at/msg_hex.h"
#include "../at/ver.h"
#include "../at/msg.h"
#include "../at/reset.h"
#include "../at/c_msg.h"
#include "../at/port.h"
#include "../at/c_msg_hex.h"
#include "../at/p_msg.h"
#include "../at/ch.h"
#include "../at/dr.h"
#include "../at/rept.h"
#include "../at/low_power.h"
#include "../at/p_msg_hex.h"
#include "../at/adr.h"
#include "../at/fdefault.h"
#include "../at/id.h"
#include "../at/power.h"

#include <zephyr.h>

#include <stdbool.h>

struct at_command_context at_cmd_ctx = { 0, };

static void _init_worker()
{

}

static void _loop(const struct app_data* app_data)
{
    uart_printf(app_data->devs->uart, "at_command_thread\r\n");
    k_sleep(K_MSEC(500));
}

void worker_at_command_handler(const struct app_data* app_data)
{
    _init_worker();

    while (is_app_alive(app_data))
    {
        _loop(app_data);
    }
}