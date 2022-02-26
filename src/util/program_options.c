#include "./program_options.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <memory.h>

#define _PARSED_KEY_VAL_MAX_SIZE (size_t)16U
struct _program_options_parsed
{
    size_t    size;
    str8_8_t  key[_PARSED_KEY_VAL_MAX_SIZE];
    str8_64_t val[_PARSED_KEY_VAL_MAX_SIZE];
};

#define NEW_PARSEDS_MAX_SIZE (size_t)64U
static struct _program_options_parsed new_parseds[NEW_PARSEDS_MAX_SIZE];
static size_t new_parseds_idx = 0;

/**
 * @author Jin
 * @brief 
 * 
 * @return struct _program_options_parsed* 
 */
static struct _program_options_parsed* _get_new_parsed()
{
    struct _program_options_parsed* res = &new_parseds[new_parseds_idx++];
    if (new_parseds_idx == NEW_PARSEDS_MAX_SIZE)
        new_parseds_idx = 0;
    return res;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param ctx 
 * @param argc 
 * @param argv 
 */
static void _parse_args(struct program_options_context* ctx,
                        int argc, char** argv)
{
    for (int i = 0; i < argc; i++)
    {
        
    }
}

/**
 * @author Jin
 * @brief 
 * 
 * @param ctx 
 * @param delims 
 * @param opts 
 * @param opts_size 
 */
void program_options_init(struct program_options_context* ctx,
                          struct program_options_delims* delims,
                          struct program_options_option* opts, size_t opts_size)
{
    ctx->parsed = _get_new_parsed();
    ctx->delims = delims;
    ctx->opts = opts;
    ctx->opts_size = opts_size;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param ctx 
 * @param argc 
 * @param argv 
 * @return true 
 * @return false 
 */
bool program_options_set_args(struct program_options_context* ctx,
                              int argc, char** argv)
{
    bool res = false;

    _parse_args(ctx, argc, argv);
    if (ctx->parsed->size) res = true;    

    return res;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param ctx 
 * @param option 
 * @param value 
 * @return true 
 * @return false 
 */
bool program_options_find_uint(struct program_options_context* ctx,
                               const char* option, uint32_t* value)
{
    bool found = false;



    return found;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param ctx 
 * @param option 
 * @param value 
 * @return true 
 * @return false 
 */
bool program_options_find_int(struct program_options_context* ctx,
                              const char* option, int32_t* value)
{
    bool found = false;

    return found;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param ctx 
 * @param option 
 * @param value 
 * @return true 
 * @return false 
 */
bool program_options_find_string(struct program_options_context* ctx,
                                 const char* option, char* value)
{
    bool found = false;

    

    return found;
}
