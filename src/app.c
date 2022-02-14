#include "./app.h"
#include "./device/devices.h"
#include "./init/dev_init.h"

#include <zephyr.h>

#define NUM_APP_THREADS 3
#define EVENT_THREAD_IDX 0

static struct devices devs = { 0, };
static struct k_thread app_threads[NUM_APP_THREADS] = { 0, };

/**
 * @brief start app threads
 * 
 * @param app_data 
 */
static void _start_app_threads(struct app_data* app_data)
{

}

/**
 * @brief initialize this app
 * 
 * @param app_data 
 */
void app_init(struct app_data* app_data)
{
    app_data->devs = &devs;
    app_data->app_threads = app_threads;
    app_data->num_app_threads = NUM_APP_THREADS;
    get_devices(app_data->devs);
    dev_init(app_data->devs);

    _start_app_threads(app_data);
}

void app_start(const struct app_data* app_data)
{
    
}

void app_deinit(const struct app_data* app_data)
{

}

/**
 * @brief Get the event thread object
 * 
 * @param app_data 
 * @return struct k_thread* 
 */
struct k_thread* get_event_thread(struct app_data* app_data)
{
    return &app_data->app_threads[EVENT_THREAD_IDX];
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