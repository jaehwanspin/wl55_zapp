#include "./program_options.h"

#include <string.h>

/**
 * @author Jin
 * @brief 
 * 
 * @param ctx 
 * @param option 
 * @return int 
 */
static int _find_option(struct program_options_context* ctx,
                         const char* option)
{
    int found_idx = -1;

    for (int i = 0; i < ctx->options_count; i++)
    {
        for (int j = 0; j < ctx->argc; j++)
        {
            volatile void* fucking = 0;
            
        }
    }

    return found_idx;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param ctx 
 * @param argc 
 * @param argv 
 */
void program_options_init(struct program_options_context* ctx,
                          int argc, char** argv)
{
    ctx->argc = argc;
    ctx->argv = argv;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param ctx 
 * @param options_size 
 * @param options 
 * @return true 
 * @return false 
 */
bool program_options_add_options(struct program_options_context* ctx,
                                 size_t options_size,
                                 struct program_options_option* options)
{
    bool res = false;

    if (ctx != nullptr && options != nullptr)
    {
        ctx->options_count = options_size;
        ctx->options = options;
        res = true;
    }

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
