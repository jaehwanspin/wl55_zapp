#ifndef __IFACE_AT_COMMAND_H__
#define __IFACE_AT_COMMAND_H__

/**
 * @author Jin
 * @brief AT command library
 *     _  _____    ____ ___  __  __ __  __    _    _   _ ____  
 *    / \|_   _|  / ___/ _ \|  \/  |  \/  |  / \  | \ | |  _ \ 
 *   / _ \ | |   | |  | | | | |\/| | |\/| | / _ \ |  \| | | | |
 *  / ___ \| |   | |__| |_| | |  | | |  | |/ ___ \| |\  | |_| |
 * /_/   \_\_|    \____\___/|_|  |_|_|  |_/_/   \_\_| \_|____/ 
 * 
 *     _         _   _                          _ _       
 *    / \  _   _| |_| |__   ___  _ __   _      | (_)_ __  
 *   / _ \| | | | __| '_ \ / _ \| '__| (_)  _  | | | '_ \ 
 *  / ___ \ |_| | |_| | | | (_) | |     _  | |_| | | | | |
 * /_/   \_\__,_|\__|_| |_|\___/|_|    (_)  \___/|_|_| |_|
 * 
 */


#ifdef __cpusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdbool.h>

#ifndef AT_COMMAND_ARGV_MAX_SIZE
#define AT_COMMAND_ARGV_MAX_SIZE (size_t)8U
#endif

#ifndef AT_COMMAND_RX_BUFFER_MAX_SIZE
#define AT_COMMAND_RX_BUFFER_MAX_SIZE (size_t)32U
#endif

#ifndef AT_COMMAND_PROMPT_MAX_SIZE
#define AT_COMMAND_PROMPT_MAX_SIZE (size_t)16U
#endif

#ifndef AT_COMMAND_ERROR_MSG_MAX_SIZE
#define AT_COMMAND_ERROR_MSG_MAX_SIZE (size_t)32U
#endif

#ifndef AT_COMMAND_COMMAND_MAX_SIZE
#define AT_COMMAND_COMMAND_MAX_SIZE (size_t)16U
#endif

#ifndef AT_COMMAND_COMMANDS_MAX_SIZE
#define AT_COMMAND_COMMANDS_MAX_SIZE (size_t)32U
#endif

typedef int(*at_command_cb_func_t)(int, char**);

struct at_command_cfg
{
    char prompt[AT_COMMAND_PROMPT_MAX_SIZE];
    char error_msg[AT_COMMAND_ERROR_MSG_MAX_SIZE];
};

struct at_command_command
{
    char command[AT_COMMAND_COMMAND_MAX_SIZE];
    at_command_cb_func_t cb_func;
};

struct at_command_context
{
    size_t rx_buffer_size;
    char rx_buffer[AT_COMMAND_RX_BUFFER_MAX_SIZE];
    struct at_command_cfg cfg;
    size_t cmds_size;
    struct at_command_command cmds[AT_COMMAND_COMMANDS_MAX_SIZE];
};

bool at_command_init(struct at_command_context*, struct at_command_cfg*);
bool at_command_add_cmd(struct at_command_context*, const char*, at_command_cb_func_t);
bool at_command_remove_cmd(struct at_command_context*, const char*);
void at_command_update(struct at_command_context*, char);
void at_command_deinit(struct at_command_context*);

#ifdef __cpusplus
}
#endif

#endif