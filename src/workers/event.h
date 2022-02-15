#ifndef __WORKERS_EVENT_H__
#define __WORKERS_EVENT_H__

#ifdef __cplusplus
extern "C"
{
#endif

struct app_data;

void worker_event_handler(const struct app_data*);

#ifdef __cplusplus
}
#endif

#endif