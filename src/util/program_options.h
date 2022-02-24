#ifndef __UTIL_PROGRAM_OPTIONS_H__
#define __UTIL_PROGRAM_OPTIONS_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "./custom_typedefs.h"
#include "./bool_but_not_bool.h"

enum program_options_value_types
{
    PROGRAM_OPTIONS_VALUE_TYPE_STRING = 1U,
    PROGRAM_OPTIONS_VALUE_TYPE_UINT   = 2U,
    PROGRAM_OPTIONS_VALUE_TYPE_INT    = 3U
};

struct program_options_option
{
    str8_16_t                        option_name;
    bbn_bool                         has_value;
    enum program_options_value_types value_type;
};

struct program_options_context
{
    int                            argc;
    char**                         argv;
    size_t                         options_count;
    struct program_options_option* options;
};

void program_options_init(struct program_options_context*, int, char**);
bool program_options_add_options(struct program_options_context*, size_t, struct program_options_option*);
bool program_options_find_uint(struct program_options_context*, const char*, uint32_t*);
bool program_options_find_int(struct program_options_context*, const char*, int32_t*);
bool program_options_find_string(struct program_options_context*, const char*, char*);

#ifdef __cplusplus
}
#endif

#endif