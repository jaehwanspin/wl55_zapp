#include "./at_command.h"

#include "../util/custom_typedefs.h"

#include <string.h>
#include <memory.h>

/**
 * @brief clears rx buffer
 * 
 * @param ctx 
 */
static void _at_command_reset_buffer(struct at_command_context* ctx)
{
    ctx->rx_buffer_size = 0;
    memset(ctx->rx_buffer, 0, sizeof(ctx->rx_buffer));
}

/**
 * @brief prints prompt( ex. "command> " )
 * 
 * @param ctx AT command context
 */
static void _at_command_print_prompt(struct at_command_context* ctx)
{
    // uart_print(ctx->cfg.prompt);
    // uart_print("\r\n");
}

/**
 * @brief prints error ( ex. "command : not found" )
 * 
 * @param ctx AT command context
 * @param cmd command string
 */
static void _at_command_print_error(struct at_command_context* ctx, char* cmd)
{
    // printf("%s : %s\r\n", cmd, ctx->cfg.error_msg);
    // uart_print(cmd);
    // uart_print(" : ");
    // uart_print(ctx->cfg.error_msg);
    // uart_print("\r\n");
}

/**
 * @brief parses command line from context buffer
 * 
 * @param ctx AT command context
 */
static void _at_command_parse_cmd(struct at_command_context* ctx)
{
    if (ctx->rx_buffer[0])
    {
        bool found = false;
        int argc = 0;
        char* argv[AT_COMMAND_ARGV_MAX_SIZE] = {  { 0, }, };
        char* rx_ptr = ctx->rx_buffer;

        // uart_print("\r\n");

        while (argv[argc++] = strtok_r(rx_ptr, " ", &rx_ptr));
        argc--;

        for (int i = 0; i < ctx->cmds_size; i++)
        {
            if (0 == strcmp(argv[0], ctx->cmds[i].command))
            {
                found = true;
                ctx->cmds[i].cb_func(argc, argv);
                break;
            }
        }

        if (!found)
            _at_command_print_error(ctx, argv[0]);
        _at_command_reset_buffer(ctx);
    }
    // else
        // uart_print("\r\n");

    _at_command_print_prompt(ctx);
}

/**
 * @author Jin
 * @brief removes buffer
 * 
 * @param ctx AT command context
 */
static void _at_command_process_backspace(struct at_command_context* ctx)
{
    if (ctx->rx_buffer_size)
    {
        ctx->rx_buffer[ctx->rx_buffer_size - 1] = 0;
        ctx->rx_buffer_size--;
        // uart_print("\b \b\x1B[1P");
    }
}

/**
 * @brief prints cancel and new line and clears buffer
 * 
 * @param ctx 
 */
static void _at_command_process_cancel(struct at_command_context* ctx)
{
    // uart_print("^C\r\n");
    _at_command_reset_buffer(ctx);
    _at_command_print_prompt(ctx);
}

/**
 * @brief adds buffer and prints what I wrote
 * 
 * @param ctx AT command context
 * @param single_buffer single buffer
 */
static void _at_command_add_char_into_buffer(struct at_command_context* ctx, char single_buffer)
{
    if (ctx->rx_buffer_size < AT_COMMAND_RX_BUFFER_MAX_SIZE)
    {
        ctx->rx_buffer[ctx->rx_buffer_size++] = single_buffer;
        char out_char[2] = { single_buffer, 0 };
        uart_print(out_char);
    }
}

/**
 * @brief constructor
 * 
 * @param ctx AT command context
 * @param cfg AT command configuration data
 * @return true success
 * @return false fail(AT command context is null, empty error message, empty prompt)
 */
bool at_command_init(struct at_command_context* ctx, struct at_command_cfg* cfg)
{
    bool res = false;
    if (cfg != nullptr && cfg->error_msg && cfg->prompt)
    {
        memcpy(&ctx->cfg, cfg, sizeof(struct at_command_cfg));
    }

    return res;
}

/**
 * @author Jin
 * @brief command addition
 * 
 * @param ctx AT command context
 * @param cmd command, command handler(callback)
 * @return true success
 * @return false fail(AT command context is null, empty command, context overflow)
 */
bool at_command_add_cmd(struct at_command_context* ctx, const char* cmd, at_command_cb_func_t cb_func)
{
    bool res = false;
    if (ctx != nullptr && ctx->cmds_size <= AT_COMMAND_COMMANDS_MAX_SIZE)
    {
        strcpy(ctx->cmds[ctx->cmds_size].command, cmd);
        ctx->cmds[ctx->cmds_size].cb_func = cb_func;
        ctx->cmds_size++;
    }

    return res;
}

/**
 * @brief command removal
 * 
 * @param ctx AT command context
 * @param cmd_name command name
 * @return true success
 * @return false fail(AT command context is null, command not found, empty commands)
 */
bool at_command_remove_cmd(struct at_command_context* ctx, const char* cmd_name)
{
    bool res = false;
    if (ctx != nullptr && ctx->cmds_size > 0)
    {
        int i = 0;
        while (i < ctx->cmds_size)
        {
            if (0 == strcmp(ctx->cmds[i].command, cmd_name))
                break;
            i++;
        }

        if (i == AT_COMMAND_COMMANDS_MAX_SIZE)
            goto remove_cmd_res;
    }

remove_cmd_res:
    return res;
}

/**
 * @brief update in infinite loop
 * 
 * @param ctx AT command context
 * @param rx_value single rx buffer
 */
void at_command_update(struct at_command_context* ctx, char rx_value)
{
    switch (rx_value)
    {
    case '\b':
    {
        _at_command_process_backspace(ctx);
        break;
    }
    case '\r':
    {
        _at_command_parse_cmd(ctx);
        break;
    }
    case 0x03:
    {
        _at_command_process_cancel(ctx);
        break;
    }
    default:
    {
        _at_command_add_char_into_buffer(ctx, rx_value);
        break;
    }
    }
}

/**
 * @brief destructor
 * 
 * @param ctx AT command context
 */
void at_command_deinit(struct at_command_context* ctx)
{
    if (ctx != nullptr)
        memset(ctx, 0, sizeof(struct at_command_context));
}
