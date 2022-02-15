#include "./app.h"
#include "./device/devices.h"
#include "./init/dev_init.h"
#include "./init/thread_init.h"

#include <zephyr.h>

/**
 * @brief initialize this app
 * 
 * @param app_data 
 */
void app_init(struct app_data* app_data)
{
    get_devices(app_data);
    dev_init(app_data->devs);
    // todo env_init
    threads_init(app_data);
}

void app_start(const struct app_data* app_data)
{
    threads_start(app_data);
}

void app_deinit(const struct app_data* app_data)
{
    
}

/**
 * @brief is this app still alive?
 * 
 * @param app_data 
 * @return true alive
 * @return false dead
 */
bool is_app_alive(const struct app_data* app_data)
{
    return app_data->app_alive;
}