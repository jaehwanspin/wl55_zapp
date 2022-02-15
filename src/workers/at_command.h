#ifndef __WORKERS_AT_COMMAND_H__
#define __WORKERS_AT_COMMAND_H__

#ifdef __cplusplus
extern "C"
{
#endif

struct app_data;

void worker_at_command_handler(const struct app_data*);

#ifdef __cplusplus
}
#endif

#endif