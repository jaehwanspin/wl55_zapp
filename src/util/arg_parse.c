#include "./arg_parse.h"

#include "./custom_typedefs.h"

union arg_parse_multitype_value
{
    int64_t  int_value;
    uint64_t uint_value;
    char*    string_value;
};

struct arg_parse_parsed_option
{
    str8_16_t                       key;
    enum arg_parse_value_types      value_type;
    union arg_parse_multitype_value value;
};


static size_t _find_index(struct arg_parse_context* ctx, int argc, char** argv)
{
    size_t idx = bbnb_not_found;

    

    return idx;
}


void arg_parse_init(struct arg_parse_context* ctx,
                    struct arg_parse_option* opts, size_t opts_size)
{
    ctx->opts = opts;
    ctx->opts_size = opts_size;
}

bool arg_parse_set_args(struct arg_parse_context* ctx, int argc, char** argv)
{
    bool res = true;

    if (argc && (argv != nullptr))
    {
        size_t found_idx = SIZE_MAX;

    }

    return res;
}

bbn_bool arg_parse_parse_uint(struct arg_parse_context* ctx, uint32_t* out_value)
{
    bbn_bool res = bbnb_not_found;

    return res;
}

bbn_bool arg_parse_parse_int(struct arg_parse_context* ctx, int32_t* out_value)
{
    bbn_bool res = bbnb_not_found;

    return res;
}

bbn_bool arg_parse_parse_string(struct arg_parse_context* ctx, char* out_value)
{
    bbn_bool res = bbnb_not_found;

    return res;
}
