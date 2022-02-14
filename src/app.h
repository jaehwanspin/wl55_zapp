#ifndef __APP_H__
#define __APP_H__

#ifdef __cplusplus
extern "C"
{
#endif 

#define NUM_APP_THREADS 3

struct app_data
{

};

void app_init(struct app_data*);
void app_start(const struct app_data*);
void app_deinit(const struct app_data*);

#ifdef __cplusplus
}
#endif

#endif