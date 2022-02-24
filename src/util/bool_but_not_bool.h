#ifndef __UTIL_BOOL_BUT_NOT_BOOL_H__
#define __UTIL_BOOL_BUT_NOT_BOOL_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef int bbn_bool;

#define bbnb_both 2
#define bbnb_true 1
#define bbnb_false 0
#define bbnb_undefined -1

#ifdef __cplusplus
}
#endif

#endif