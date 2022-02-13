#ifndef __INIT_DEV_INIT_H__
#define __INIT_DEV_INIT_H__

#ifdef __cplusplus
extern "C"
{
#endif

struct devices;

void dev_init(const struct devices*);

#ifdef __cplusplus
}
#endif

#endif