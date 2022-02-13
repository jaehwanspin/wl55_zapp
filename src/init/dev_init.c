#include "./dev_init.h"

#include <drivers/uart.h>
#include <drivers/flash.h>
#include <drivers/lora.h>

#include <stdbool.h>

#include "../device/devices.h"

#define UART_CONFIG_FLASH_MEM_PAGE 126U
#define LORA_CONFIG_FLASH_MEM_PAGE 127U

/**
 * @brief sets to default LoRa config 920MHz
 * 
 * @param cfg 
 */
static void _set_default_lora_config(struct lora_modem_config* cfg)
{
    cfg->frequency = 920900000;
    cfg->bandwidth = BW_125_KHZ;
    cfg->datarate = SF_10;
    cfg->preamble_len = 8;
    cfg->coding_rate = CR_4_5;
    cfg->tx_power = 14;
    cfg->tx = true;
}

/**
 * @brief sets to default UART config 115200-8-N-1
 * 
 * @param cfg 
 */
static void _set_default_uart_config(struct uart_config* cfg)
{
    cfg->baudrate = 115200;
    cfg->data_bits = UART_CFG_DATA_BITS_8;
    cfg->flow_ctrl = UART_CFG_FLOW_CTRL_NONE;
    cfg->parity = UART_CFG_PARITY_NONE;
    cfg->stop_bits = UART_CFG_STOP_BITS_1;
}

static void _parse_lora_options(const struct device* flash_dev,
                                const struct device* lora_dev,
                                const struct lora_modem_config* out_cfg)
{
    int flash_read_res = -1;
    int offset = 0;
    struct flash_pages_info pages_info = { 0, };

    flash_read_res = flash_get_page_info_by_idx(flash_dev,
                                                LORA_CONFIG_FLASH_MEM_PAGE,
                                                &pages_info);
    offset += pages_info.start_offset;

    flash_read_res = flash_read(flash_dev,
                                offset,
                                out_cfg,
                                sizeof(struct lora_modem_config));
}


/**
 * @brief parses UART options from the flash memory
 * 
 * @param flash_dev 
 * @param uart_dev 
 * @param out_cfg 
 */
static void _parse_uart_options(const struct device* flash_dev,
                                const struct device* uart_dev,
                                const struct uart_config* out_cfg)
{

}

/**
 * @brief validates LoRa options
 *
 * KR Non-License frequency 920900000 Hz ~ 923300000 Hz
 * 
 * @param cfg 
 * @return true OK
 * @return false FAILED
 */
static bool _validate_lora_options(const struct lora_modem_config* cfg)
{
    bool res = true;

    if (cfg->frequency < 920900000 || cfg->frequency > 923300000)
        res = false;
    
    if (cfg->bandwidth != BW_125_KHZ ||
        cfg->bandwidth != BW_250_KHZ ||
        cfg->bandwidth != BW_500_KHZ)
        res = false;
    
    if (cfg->datarate < SF_6 || cfg->datarate > SF_12)
        res = false;
    
    return res;
}

static void _flash_mem_init(const struct devices* devs)
{

}

static void _lora_init(const struct devices* devs)
{
    int init_res = -1;
    struct lora_modem_config cfg = { 0, };

    _parse_lora_options(devs->flash, devs->lora, &cfg);

    if (!_validate_lora_options(&cfg))
        _set_default_lora_config(&cfg);

    init_res = lora_config(devs->lora, &cfg);

    if (init_res < 0)
        while (true);
}

static void _uart_init(const struct devices* devs)
{
    struct uart_config cfg = { 0, };
    
}

void dev_init(const struct devices* devs)
{
    _flash_mem_init(devs);
    _lora_init(devs);
}