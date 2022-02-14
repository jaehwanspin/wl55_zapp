#ifndef __APP_H__
#define __APP_H__

#ifdef __cplusplus
extern "C"
{
#endif 

#include <stddef.h>
#include <stdbool.h>

struct k_thread;
struct devices;

struct app_data
{
    struct devices*  devs;
    struct k_thread* app_threads;
    size_t           num_app_threads;
    bool             app_alive;
};

void app_init(struct app_data*);
void app_start(const struct app_data*);
void app_deinit(const struct app_data*);

struct k_thread* get_event_thread(struct app_data*);

bool is_app_alive(const struct app_data*);

#ifdef __cplusplus
}
#endif

#endif