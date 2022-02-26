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
    PROGRAM_OPTIONS_VALUE_TYPE_NONE   = 0U,
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

struct program_options_delims
{
    str8_8_t main_delim;
    str8_8_t sub_delim;
};

struct _program_options_parsed;

struct program_options_context
{
    struct _program_options_parsed* parsed;
    struct program_options_delims* delims;
    size_t                         opts_size;
    struct program_options_option* opts;
};

void program_options_init(struct program_options_context*,
                          struct program_options_delims*,
                          struct program_options_option*, size_t);
bool program_options_set_args(struct program_options_context*, int, char**);
bool program_options_find_uint(struct program_options_context*, const char*, uint32_t*);
bool program_options_find_int(struct program_options_context*, const char*, int32_t*);
bool program_options_find_string(struct program_options_context*, const char*, char*);

#ifdef __cplusplus
}
#endif

#endif