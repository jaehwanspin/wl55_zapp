#ifndef __APP_H__
#define __APP_H__

#ifdef __cplusplus
extern "C"
{
#endif 

#include <stddef.h>
#include <stdbool.h>

#include <zephyr.h>

struct devices;

#ifndef NUM_APP_THREADS
#define NUM_APP_THREADS 3
#endif

#ifndef APP_THREAD_STACK_SIZE
#define APP_THREAD_STACK_SIZE 2048
#endif 


struct app_data
{
    struct devices*                devs;
    struct k_thread                app_threads[NUM_APP_THREADS];
    struct z_thread_stack_element app_thread_stacks[NUM_APP_THREADS][APP_THREAD_STACK_SIZE + 32];
    size_t                         num_app_threads;

    struct k_mutex                 uart_output_mtx;

    bool                           app_alive;
};

void app_init(struct app_data*);
void app_start(const struct app_data*);
void app_deinit(const struct app_data*);

bool is_app_alive(const struct app_data*);

#ifdef __cplusplus
}
#endif

#endif