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
static struct z_thread_stack_element app_thread_stacks[NUM_APP_THREADS][THREAD_STACK_SIZE] = { 0, };

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
    struct z_thread_stack_element** app_stacks = nullptr;
    struct z_thread_stack_element* temp_app_stacks_ptr[THREAD_STACK_SIZE] = { app_thread_stacks[0], app_thread_stacks[1], app_thread_stacks[2] };
    app_stacks = temp_app_stacks_ptr;
    app_data->app_stacks = app_stacks;
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

    tid = k_thread_create(&app_data->app_threads[AT_COMMAND_THREAD_IDX],
                          app_data->app_stacks[AT_COMMAND_THREAD_IDX],
                          THREAD_STACK_SIZE,
                          (k_thread_entry_t)worker_at_command_handler,
                          &app_data, nullptr, nullptr,
                          AT_COMMAND_THREAD_PRIO,
                          0,
                          K_NO_WAIT);
    if (tid == nullptr)
        enable_led_error(app_data->devs->led);

    tid = k_thread_create(&app_data->app_threads[EVENT_THREAD_IDX],
                          app_data->app_stacks[EVENT_THREAD_IDX],
                          THREAD_STACK_SIZE,
                          (k_thread_entry_t)worker_at_command_handler,
                          &app_data, nullptr, nullptr,
                          EVENT_THREAD_PRIO,
                          0,
                          K_NO_WAIT);

    if (tid == nullptr)
        enable_led_error(app_data->devs->led);
}

void threads_init(struct app_data* app_data)
{
    _init_app_threads(app_data);
}

void threads_start(const struct app_data* app_data)
{
    _start_app_threads(app_data);
}

void threads_destoy(const struct app_data* app_data)
{
    for (int i = 0; i < NUM_APP_THREADS; i++)
        k_thread_abort(&app_data->app_threads[i]);
}