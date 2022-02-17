#include "./flash_data.h"

#include <drivers/flash.h>
#include <drivers/uart.h>
#include <drivers/lora.h>
#include <lorawan/lorawan.h>

#define UART_CONFIG_FLASH_MEM_PAGE 125U
#define LORAWAN_CONFIG_FLASH_MEM_PAGE 126U
#define LORA_CONFIG_FLASH_MEM_PAGE 127U

/**
 * @author Jin
 * @brief 
 * 
 * @param flash_dev 
 * @param cfg 
 * @return int -1 FAILED
 */
int flash_write_lora_config(const struct device *flash_dev,
                            const struct lora_modem_config *cfg)
{
    int flash_write_res = 0;
    int offset = 0;
    struct flash_pages_info pages_info = { 0, };

    flash_write_res += flash_get_page_info_by_idx(flash_dev,
                                                  LORA_CONFIG_FLASH_MEM_PAGE,
                                                  &pages_info);
    offset += pages_info.start_offset;

    flash_write_res += flash_erase(flash_dev,
                                   offset,
                                   16);

    flash_write_res += flash_write(flash_dev,
                                   offset,
                                   cfg,
                                   16);

    return flash_write_res;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param flash_dev 
 * @param cfg 
 * @return int 
 */
int flash_read_lora_config(const struct device *flash_dev,
                           struct lora_modem_config *cfg)
{
    int flash_read_res = 0;
    int offset = 0;
    struct flash_pages_info pages_info = { 0, };

    flash_read_res += flash_get_page_info_by_idx(flash_dev,
                                                 LORA_CONFIG_FLASH_MEM_PAGE,
                                                 &pages_info);
    offset += pages_info.start_offset;

    flash_read_res += flash_read(flash_dev,
                                 offset,
                                 cfg,
                                 sizeof(struct lora_modem_config));

    return flash_read_res;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param flash_dev 
 * @param cfg 
 * @return int 
 */
int flash_write_lorawan_config(const struct device* flash_dev, const struct lorawan_join_config* cfg)
{
    int flash_write_res = 0;
    int offset = 0;
    struct flash_pages_info pages_info = { 0, };

    flash_write_res += flash_get_page_info_by_idx(flash_dev,
                                                  LORAWAN_CONFIG_FLASH_MEM_PAGE,
                                                  &pages_info);
    offset += pages_info.start_offset;

    flash_write_res += flash_erase(flash_dev,
                                   offset,
                                   sizeof(struct lorawan_join_config));

    flash_write_res += flash_write(flash_dev,
                                   offset,
                                   cfg,
                                   sizeof(struct lorawan_join_config));

    return flash_write_res;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param flash_dev 
 * @param cfg 
 * @return int 
 */
int flash_read_lorawan_config(const struct device* flash_dev, struct lorawan_join_config* cfg)
{
    int flash_write_res = 0;
    int offset = 0;
    struct flash_pages_info pages_info = { 0, };

    flash_write_res += flash_get_page_info_by_idx(flash_dev,
                                                  LORAWAN_CONFIG_FLASH_MEM_PAGE,
                                                  &pages_info);
    offset += pages_info.start_offset;

    flash_write_res += flash_read(flash_dev,
                                  offset,
                                  cfg,
                                  sizeof(struct lorawan_join_config));

    return flash_write_res;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param flash_dev 
 * @param cfg 
 * @return int 
 */
int flash_write_uart_config(const struct device *flash_dev,
                            const struct uart_config *cfg)
{
    int flash_write_res = 0;
    int offset = 0;
    struct flash_pages_info pages_info = { 0, };

    flash_write_res += flash_get_page_info_by_idx(flash_dev,
                                                  UART_CONFIG_FLASH_MEM_PAGE,
                                                  &pages_info);
    offset += pages_info.start_offset;

    flash_write_res += flash_erase(flash_dev,
                                   offset,
                                   sizeof(struct uart_config));

    flash_write_res += flash_write(flash_dev,
                                   offset,
                                   cfg,
                                   sizeof(struct uart_config));

    return flash_write_res;
}

/**
 * @author Jin
 * @brief 
 * 
 * @param flash_dev 
 * @param cfg 
 * @return int 
 */
int flash_read_uart_config(const struct device *flash_dev,
                           struct uart_config *cfg)
{
    int flash_read_res = 0;
    int offset = 0;
    struct flash_pages_info pages_info = { 0, };

    flash_read_res += flash_get_page_info_by_idx(flash_dev,
                                                 UART_CONFIG_FLASH_MEM_PAGE,
                                                 &pages_info);
    offset += pages_info.start_offset;

    flash_read_res += flash_read(flash_dev,
                                 offset,
                                 cfg,
                                 sizeof(struct uart_config));

    return flash_read_res;
}

