#ifndef __UTIL_ARG_PARSE_H__
#define __UTIL_ARG_PARSE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "./custom_typedefs.h"
#include "./bool_but_not_bool.h"

enum arg_parse_value_types
{
    ARG_PARSE_VALUE_TYPE_NONE   = 0U,
    ARG_PARSE_VALUE_TYPE_STRING = 1U,
    ARG_PARSE_VALUE_TYPE_UINT   = 2U,
    ARG_PARSE_VALUE_TYPE_INT    = 3U
};

struct arg_parse_option
{
    str8_16_t                  option_name;
    bbn_bool                   has_value;
    enum arg_parse_value_types value_type;
};

union arg_parse_multitype_value
{
    int64_t  int_value;
    uint64_t uint_value;
    char*    string_value;
};

struct arg_parse_result
{
    str8_16_t                       option_name;
    union arg_parse_multitype_value value;
};

struct arg_parse_context
{
    struct arg_parse_option* opts;
    size_t                   opts_size;
};

void arg_parse_init(struct arg_parse_context*, struct arg_parse_option*, size_t);
bbn_bool arg_parse_set_args(struct arg_parse_context*, int, char**,
    struct arg_parse_result*);

#ifdef __cplusplus
}
#endif

#endif