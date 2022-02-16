#include "./test.h"
#include "../app.h"
#include "../device/devices.h"
#include "../telemetry/uart_io.h"

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
int at_test_handler(int argc, char** argv)
{
    int res = 0;
    uint8_t test_resp[] = {'+', 'A', 'T', ':', ' ', 'O', 'K', '\r'};
    uart_print(app_data.devs->uart, test_resp, sizeof(test_resp));

    return res;
}