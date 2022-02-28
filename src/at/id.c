#include "./id.h"
#include "../app.h"
#include "../device/devices.h"
#include "../telemetry/uart_io.h"
#include "../util/arg_parse.h"

#include "../util/custom_typedefs.h"

#include <string.h>

static struct arg_parse_option opts[] = {
    {  }
};

const char* options[] = {
    "DevAddr",
    "DevEui",
    "AppEui"
};

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
int at_id_handler(int argc, char** argv)
{
    int res = 0;
    uart = (struct device*)app_data.devs->uart;

    switch (argc)
    {
    case 2: // all
    {
        uart_print(uart, "you!\r\n", 7);
        break;
    }
    case 3:
    {
        uart_print(uart, "hey!\r\n", 7);
        break;
    }
    default:
    {
        uart_print(uart, "yeah\r\n", 7);
        break;
    }
    }
   
    return res;
}