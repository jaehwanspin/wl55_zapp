#include "./arg_parse.h"

#include "./custom_typedefs.h"

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include <string.h>
#include <drivers/uart.h>
#include "../app.h"
#include "../device/devices.h"
#include "../telemetry/uart_io.h"

#include <string.h>

extern struct app_data app_data;

#define ARG_PARSE_STRING_POOL_MAX_SIZE (size_t)16U
static size_t arg_parse_string_pool_idx = 0;

static str8_64_t arg_parse_string_value_pool[ARG_PARSE_STRING_POOL_MAX_SIZE];

/**
 * @author Jin
 * @brief Get the one string object
 * 
 * @param result 
 */
static void _get_one_string(struct arg_parse_result* result)
{
    str8_64_t* val = &arg_parse_string_value_pool[arg_parse_string_pool_idx++];

    if (arg_parse_string_pool_idx == ARG_PARSE_STRING_POOL_MAX_SIZE)
        arg_parse_string_pool_idx = 0;

    result->value.string_value = (char*)val;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param value_type 
 * @param val 
 * @param result 
 * @return bbn_bool 
 */
static bbn_bool _parse_value(enum arg_parse_value_types value_type,
    char* val, struct arg_parse_result* result)
{
    bbn_bool res = bbnb_true;

    switch (value_type)
    {
    case ARG_PARSE_VALUE_TYPE_STRING:
    {
        _get_one_string(result);
        strcpy(result->value.string_value, val);
        // uart_print(app_data.devs->uart, val, strlen(val));
        // uart_print(app_data.devs->uart, "\r\n", 2);
        // uart_print(app_data.devs->uart, result->value.string_value, strlen(result->value.string_value));
        // uart_print(app_data.devs->uart, "\r\n", 2);
        break;
    }
    case ARG_PARSE_VALUE_TYPE_INT:
    {
        size_t str_len = strlen(val);
        bool is_integral = true;
        
        is_integral = is_integral && (isdigit((int)val[0]) || val[0] == '-');
        
        for (int i = 1; i < str_len; i++)
            is_integral = is_integral && isdigit((int)val[i]);

        if (!is_integral)
            res = bbnb_error;
        else
            result->value.int_value = strtoll(val, nullptr, 10);

        break;
    }
    case ARG_PARSE_VALUE_TYPE_UINT:
    {
        size_t str_len = strlen(val);
        bool is_integral = true;

        for (int i = 0; i < str_len; i++)
            is_integral = is_integral && isdigit((int)val[i]);

        if (!is_integral)
            res = bbnb_error;
        else
            result->value.int_value = strtoull(val, nullptr, 10);

        break;
    }
    case ARG_PARSE_VALUE_TYPE_NONE:
        break;
    }

    return res;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param ctx 
 * @param key 
 * @param val 
 * @param result 
 * @return bbn_bool 
 */
static bbn_bool _set_result(struct arg_parse_context* ctx,
    char* key, char* val, struct arg_parse_result* result)
{
    bbn_bool res = bbnb_not_found;

    for (int i = 0; i < ctx->opts_size; i++)
    {
        if (0 == strcmp(key, (char*)&ctx->opts[i].option_name))
        {
            strcpy((char*)&result->option_name, (char*)&ctx->opts[i].option_name);
            
            switch (ctx->opts[i].has_value)
            {
            case bbnb_both:
            {
                if (val != nullptr)
                {
                    if (_parse_value(ctx->opts[i].value_type, val, result))
                        res = bbnb_found;
                    else
                        res = bbnb_error;
                }
                else
                    res = bbnb_found_but_not_has_value;
                break;
            }
            case bbnb_true:
            {
                if (_parse_value(ctx->opts[i].value_type, val, result))
                        res = bbnb_found;
                    else
                        res = bbnb_error;
                break;
            }
            case bbnb_false:
            {
                res = bbnb_found;
                break;
            }
            }
        }
    }

    return res;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param ctx 
 * @param opts 
 * @param opts_size 
 */
void arg_parse_init(struct arg_parse_context* ctx,
                    struct arg_parse_option* opts, size_t opts_size)
{
    ctx->opts = opts;
    ctx->opts_size = opts_size;
}

/**
 * @brief 
 * 
 * @param ctx 
 * @param argc 
 * @param argv 
 * @param result 
 * @return true 
 * @return false 
 */
bbn_bool arg_parse_set_args(struct arg_parse_context* ctx, int argc, char** argv,
    struct arg_parse_result* result)
{
    bbn_bool res = bbnb_error;

    if (argv[2] != nullptr)
    {
        char* key_str = strtok(argv[2], ", ");
        char* val_str = strtok(nullptr, nullptr);

        if (key_str == nullptr)
            res = bbnb_not_found;
        else
        {
            res = _set_result(ctx, key_str, val_str, result);
        }
    }

    return res;
}