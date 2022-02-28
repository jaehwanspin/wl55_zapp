#ifndef __UTIL_BOOL_BUT_NOT_BOOL_H__
#define __UTIL_BOOL_BUT_NOT_BOOL_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef int bbn_bool;

#define bbnb_both                  2
#define bbnb_true                  1
#define bbnb_false                 0
#define bbnb_undefined             -1

#define bbnb_error             -1
#define bbnb_not_found             0
#define bbnb_found_but_hasnt_value 1
#define bbnb_found                 2

#ifdef __cplusplus
}
#endif

#endif