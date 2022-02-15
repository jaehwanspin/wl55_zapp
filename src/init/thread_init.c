#include "./thread_init.h"
#include "../app.h"
#include "../device/devices.h"
#include "../util/custom_typedefs.h"

#include "../workers/at_command.h"
#include "../workers/event.h"

#include <zephyr.h>
#include <device.h>

#define NUM_APP_THREADS 3

#define EVENT_THREAD_IDX       0
#define EVENT_THREAD_PRIO      10

#define AT_COMMAND_THREAD_IDX  1
#define AT_COMMAND_THREAD_PRIO 11

#define THREAD_STACK_SIZE 2048

static struct k_thread  app_threads[NUM_APP_THREADS] = { 0, };
static k_thread_stack_t app_thread_stacks[NUM_APP_THREADS][THREAD_STACK_SIZE] = { 0, };

K_THREAD_STACK_DEFINE(hey, 1024);

/**
 * @author Jin
 * @brief init app threads
 * 
 * @param app_data 
 */
static void _init_app_threads(struct app_data* app_data)
{
    app_data->app_threads = app_threads;
    app_data->app_stacks = app_thread_stacks;
    app_data->num_app_threads = NUM_APP_THREADS;
}

/**
 * @author Jin
 * @brief start app threads
 * 
 * @param app_data 
 */
static void _start_app_threads(struct app_data* app_data)
{
    k_tid_t tid = nullptr;

    tid = k_thread_create(&app_data->app_threads[AT_COMMAND_THREAD_IDX],
                          app_data->app_stacks[AT_COMMAND_THREAD_IDX],
                          THREAD_STACK_SIZE,
                          worker_at_command_handler,
                          nullptr, nullptr, nullptr,
                          AT_COMMAND_THREAD_PRIO,
                          0,
                          K_NO_WAIT);
    if (tid == nullptr)
        enable_led_error(app_data->devs->led);

    // tid = 
    
}

void threads_init(struct app_data* app_data)
{
    _init_app_threads(app_data);
}