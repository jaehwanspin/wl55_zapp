#ifndef __IFACE_AT_COMMAND_H__
#define __IFACE_AT_COMMAND_H__

/**
 * @brief AT command library for firmware
 * @author Jin
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

#ifndef AT_COMMAND_RX_BUFFER_MAX_SIZE
#define AT_COMMAND_RX_BUFFER_MAX_SIZE (size_t)128U
#endif

typedef int(*at_command_cb_func_t)(int, char**);

struct at_command_cfg
{
    char main_command[8];
    char sub_commands[8][64];
};

struct at_command_cmd
{
    at_command_cb_func_t callback;
};

struct at_command_context
{
    char                  main_command[8]; // default "AT"
    char                  rx_buffer[AT_COMMAND_RX_BUFFER_MAX_SIZE];
    struct at_command_cfg cfg;

};

bool at_command_init(struct at_command_context*, const struct at_command_cfg*);
bool at_command_add_cmd(struct at_command_context*, const char*, at_command_cb_func_t);
void at_command_update(struct at_command_context*, char);
bool at_command_deinit(struct at_command_context*);

#ifdef __cpusplus
}
#endif

#endif