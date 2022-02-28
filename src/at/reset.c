#include "./reset.h"
#include "../app.h"
#include "../device/devices.h"
#include "../telemetry/uart_io.h"

#include "../util/custom_typedefs.h"

#include <string.h>

#include <sys/reboot.h>

// from src/main.c
extern struct app_data app_data;
static struct device* uart = nullptr;

/**
 * @author Jin
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int at_reset_handler(int argc, char** argv)
{
    int res = 0;
    uart = (struct device*)app_data.devs->uart;

    str8_16_t resp_msg =
        { '+', 'R', 'E', 'S', 'E', 'T', ':', ' ', 'O', 'K', '\r' };
    uart_print(uart, (uint8_t*)&resp_msg, strlen((char*)&resp_msg));

    sys_reboot(SYS_REBOOT_WARM);

    return res;
}