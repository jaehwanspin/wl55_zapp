#include "./arg_parse.h"

#include "./custom_typedefs.h"

#include <string.h>

#define ARG_PARSE_STRING_POOL_MAX_SIZE (size_t)16U
static size_t arg_parse_string_pool_idx = 0;

static str8_64_t arg_parse_string_value_pool[ARG_PARSE_STRING_POOL_MAX_SIZE];
static void get_one_string(struct arg_parse_result* result)
{
    str8_64_t* val = &arg_parse_string_value_pool[arg_parse_string_pool_idx++];

    if (arg_parse_string_pool_idx == ARG_PARSE_STRING_POOL_MAX_SIZE)
        arg_parse_string_pool_idx = 0;

    result->value.string_value = (char*)val;
}

void arg_parse_init(struct arg_parse_context* ctx,
                    struct arg_parse_option* opts, size_t opts_size)
{
    ctx->opts = opts;
    ctx->opts_size = opts_size;
}

bool arg_parse_set_args(struct arg_parse_context* ctx, int argc, char** argv,
    struct arg_parse_result* result)
{
    bool res = bbnb_not_found;

    if (argc > 3 && (argv != nullptr))
    {
        char* pre_arg = argv[3];
        char* key = strtok(pre_arg, ",");

        if (key == nullptr)
        {
            res = bbnb_not_found;
        }
        else
        {
            
        }
    }
    else
        res = bbnb_error;

    return res;
}