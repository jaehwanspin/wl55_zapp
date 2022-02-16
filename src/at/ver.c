#include "./ver.h"
#include "../app.h"
#include "../device/devices.h"
#include "../telemetry/uart_io.h"

#include "../util/custom_typedefs.h"

#include <string.h>

// from src/main.c
extern struct app_data app_data;

/**
 * @author Jin
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int at_ver_handler(int argc, char** argv)
{
    int res = 0;

    char telem_ver_resp[32] = { 0, };

    sprintf(telem_ver_resp, "+VER: %d.%d.%d\r",
        APP_VERSION_MAJOR,
        APP_VERSION_MINOR,
        APP_VERSION_PATCH);

    uart_print(app_data.devs->uart, (uint8_t*)telem_ver_resp, strlen(telem_ver_resp));

    return res;
}