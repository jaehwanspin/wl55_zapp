#ifndef __INIT_THREAD_INIT_H__
#define __INIT_THREAD_INIT_H__

#ifdef __cplusplus
extern "C"
{
#endif

struct app_data;

void threads_init(struct app_data*);
void threads_start(const struct app_data*);
void threads_destoy(const struct app_data*);

#ifdef __cplusplus
}
#endif

#endif