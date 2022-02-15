#include "./thread_init.h"
#include "../app.h"
#include "../device/devices.h"
#include "../util/custom_typedefs.h"

#include "../workers/at_command.h"
#include "../workers/event.h"

#include <zephyr.h>
#include <device.h>

#define EVENT_THREAD_IDX       0
#define EVENT_THREAD_PRIO      10

#define AT_COMMAND_THREAD_IDX  1
#define AT_COMMAND_THREAD_PRIO 11

// static struct z_thread_stack_element app_thread_stacks[NUM_APP_THREADS][APP_THREAD_STACK_SIZE + 32] = { };

/**
 * @author Jin
 * @brief init app threads
 * 
 * @param app_data 
 */
static void _init_app_threads(struct app_data* app_data)
{
    // app_data->app_thread_stacks = &app_thread_stacks[0];
    app_data->num_app_threads = NUM_APP_THREADS;
}

/**
 * @author Jin
 * @brief start app threads
 * 
 * @param app_data 
 */
static void _start_app_threads(const struct app_data* app_data)
{
    k_tid_t tid = nullptr;

    tid = k_thread_create((struct k_thread*)&app_data->app_threads[AT_COMMAND_THREAD_IDX],
                          (struct z_thread_stack_element*)app_data->app_thread_stacks[AT_COMMAND_THREAD_IDX],
                          APP_THREAD_STACK_SIZE,
                          (k_thread_entry_t)worker_at_command_handler,
                          (void*)app_data, nullptr, nullptr,
                          AT_COMMAND_THREAD_PRIO,
                          0,
                          K_NO_WAIT);
    if (tid == nullptr)
        enable_led_error(app_data->devs->led);

    tid = k_thread_create((struct k_thread*)&app_data->app_threads[EVENT_THREAD_IDX],
                          (struct z_thread_stack_element*)app_data->app_thread_stacks[EVENT_THREAD_IDX],
                          APP_THREAD_STACK_SIZE,
                          (k_thread_entry_t)worker_event_handler,
                          (void*)app_data, nullptr, nullptr,
                          EVENT_THREAD_PRIO,
                          0,
                          K_NO_WAIT);

    if (tid == nullptr)
        enable_led_error(app_data->devs->led);
}

/**
 * @author Jin
 * @brief 
 * 
 */
void threads_init(struct app_data* app_data)
{
    _init_app_threads(app_data);
}

/**
 * @author Jin
 * @brief 
 * 
 */
void threads_start(const struct app_data* app_data)
{
    _start_app_threads(app_data);

    for (int i = 0; i < NUM_APP_THREADS; i++)
        k_thread_join((struct k_thread*)&app_data->app_threads[i], K_FOREVER);
}

/**
 * @author Jin
 * @brief 
 * 
 */
void threads_destoy(const struct app_data* app_data)
{
    for (int i = 0; i < NUM_APP_THREADS; i++)
        k_thread_abort((struct k_thread*)&app_data->app_threads[i]);
}