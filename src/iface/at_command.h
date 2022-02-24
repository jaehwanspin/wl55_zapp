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
#define AT_COMMAND_RX_BUFFER_MAX_SIZE (size_t)528U
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
    char main_cmd[4];
    char main_delim[2];
    char sub_delim[2];
    at_command_cb_func_t test_handler;
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

#define AT_COMMAND_ERR_INVALID_PARAM            -1  // Parameters is invalid
#define AT_COMMAND_ERR_UNKOWN_COMMAND           -10 // Command unknown
#define AT_COMMAND_ERR_WRONG_FORMAT_COMMAND     -11 // Command is in wrong format
#define AT_COMMAND_ERR_UNAVAILABLE_IN_CURR_MODE -12 // Command is unavailable in current mode (Check with "AT+MODE")
#define AT_COMMAND_ERR_TOO_MANY_PARAMS          -20 // Too many parameters. LoRaWAN modem support max 15 parameters
#define AT_COMMAND_ERR_TOO_LONG_BUF             -21 // Length of command is too long (exceed 528 bytes)
#define AT_COMMAND_ERR_END_SYM_TIMEOUT          -22 // Receive end symbol timeout, command must end with <LF>
#define AT_COMMAND_ERR_INVALID_CHARACTER        -23 // Invalid character received
#define AT_COMMAND_ERR_EITHER_21_22_23          -24 // Either -21, -22 or -23

#ifdef __cpusplus
}
#endif

#endif