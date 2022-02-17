#ifndef __WORKERS_LORAWAN_H__
#define __WORKERS_LORAWAN_H__

#ifdef __cplusplus
extern "C"
{
#endif

struct app_data;

void worker_lorawan_handler(const struct app_data*);

#ifdef __cplusplus
}
#endif

#endif