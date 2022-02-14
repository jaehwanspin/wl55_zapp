#include "./app.h"

struct app_data app_data = { 0 };

/**
 * @author Jin
 * @brief App entrance
 * 
 */
void main(void)
{
    app_init(&app_data);
    app_start(&app_data);
}
