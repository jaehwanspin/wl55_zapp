#include "./app.h"

struct app_data app_data = { 0 };

/**
 * @author Jin
 * @brief App entrance
 * 
 */
void main(void)
{
    // while (1)
    // {
    //     k_sleep(K_MSEC(100));
    // }

    app_init(&app_data);
    app_start(&app_data);
}