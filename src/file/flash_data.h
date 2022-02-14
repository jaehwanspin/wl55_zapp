#ifndef __FILE_FLASH_DATA_H__
#define __FILE_FLASH_DATA_H__

#ifdef __cplusplus
extern "C"
{
#endif

struct device;
struct lora_modem_config;
struct uart_config;


int flash_write_lora_config(const struct device*, const struct lora_modem_config*);
int flash_read_lora_config(const struct device*, struct lora_modem_config*);

int flash_write_uart_config(const struct device*, const struct uart_config*);
int flash_read_uart_config(const struct device*, struct uart_config*);

#ifdef __cplusplus
}
#endif

#endif