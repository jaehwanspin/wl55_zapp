#include "./at_command.h"
#include "../app.h"
#include "../device/devices.h"
#include "../telemetry/uart_io.h"
#include "../iface/at_command.h"
#include "../util/custom_typedefs.h"
#include "../events/device_callbacks.h"

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
#include "../at/test.h"

#include <zephyr.h>
#include <drivers/uart.h>

#include <stdbool.h>
#include <string.h>

struct k_queue uart_data_que = { 0, };
struct at_command_context at_cmd_ctx = { 0, };

struct at_command_command at_cmds[] = {
    { "VER", at_ver_handler},
    { "FDEFAULT", at_fdefault_handler},
    { "RESET", at_reset_handler},
    { "LOWPOWER", at_low_power_handler},
    { "MSG", at_msg_handler},
    { "MSGHEX", at_msg_hex_handler},
    { "CMSG", at_c_msg_handler},
    { "CMSGHEX", at_c_msg_hex_handler},
    { "PMSG", at_p_msg_handler},
    { "PMSGHEX", at_p_msg_hex_handler},
    { "CH", at_ch_handler},
    { "DR", at_dr_handler},
    { "ADR", at_adr_handler},
    { "REPT", at_rept_handler},
    { "RETRY", at_retry_handler},
    { "POWER", at_power_handler},
    { "PORT", at_port_handler},
    { "MODE", at_mode_handler},
    { "PORT", at_port_handler},
    { "ID", at_id_handler},
};

/**

 * @author Jin
 * @brief 
 * 
 */
static void _init_at_command()
{
    struct at_command_cfg cfg = { "AT", "+", "=", at_test_handler };
    at_command_init(&at_cmd_ctx, &cfg);

    memcpy(&at_cmd_ctx.cmds[0], &at_cmds[0], sizeof(at_cmds));
    at_cmd_ctx.cmds_size = sizeof(at_cmds) / sizeof(struct at_command_command);
}

/**
 * @author Jin
 * @brief 
 * 
 * @param app_data 
 */
static void _init_worker(const struct app_data* app_data)
{
    k_queue_init(&uart_data_que);
    _init_at_command();

    uart_irq_callback_user_data_set(app_data->devs->uart,
                                    uart_irq_callback_handler,
                                    nullptr);
                                    
	uart_irq_rx_enable(app_data->devs->uart);
}

/**
 * @author Jin
 * @brief 
 * 
 * @param app_data 
 */
static void _loop(const struct app_data* app_data)
{
    char* data = k_queue_get(&uart_data_que, K_FOREVER);
    // uart_print(app_data->devs->uart, data, 1);
    at_command_update(&at_cmd_ctx, *data);
}

/**
 * @author Jin
 * @brief 
 * 
 * @param app_data 
 */
void worker_at_command_handler(const struct app_data* app_data)
{
    _init_worker(app_data);

    while (is_app_alive(app_data))
    {
        _loop(app_data);
    }
}