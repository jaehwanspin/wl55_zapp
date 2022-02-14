#include "./dev_init.h"
#include "../device/devices.h"
#include "../file/flash_data.h"

#include <drivers/gpio.h>
#include <drivers/uart.h>
#include <drivers/flash.h>
#include <drivers/lora.h>

#include <stdbool.h>

/**
 * @author Jin
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
 * @author Jin
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


/**
 * @author Jin
 * @brief parses LoRa options or error led on
 * 
 * @param flash_dev 
 * @param lora_dev 
 * @param out_cfg 
 * @param err_led 
 */
static void _parse_lora_options(const struct device* flash_dev,
                                const struct device* lora_dev,
                                struct lora_modem_config* out_cfg,
                                const struct gpio_dt_spec* err_led)
{
    int flash_read_res = flash_read_lora_config(flash_dev, out_cfg);

    if (flash_read_res < 0)
    {
        while (true)
        {
            gpio_pin_toggle(err_led->port, err_led->pin);
            k_sleep(K_MSEC(200));
        }
    }
}


/**
 * @author Jin
 * @brief parses UART options from the flash memory
 * 
 * @param flash_dev 
 * @param uart_dev 
 * @param out_cfg 
 */
static void _parse_uart_options(const struct device* flash_dev,
                                const struct device* uart_dev,
                                struct uart_config* out_cfg,
                                const struct gpio_dt_spec* err_led)
{
    int flash_read_res = flash_read_uart_config(flash_dev, out_cfg);

    if (flash_read_res < 0)
    {
        while (true)
        {
            gpio_pin_toggle(err_led->port, err_led->pin);
            k_sleep(K_MSEC(200));
        }
    }
}

/**
 * @author Jin
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

/**
 * @author Jin
 * @brief validates UART options
 * 
 * @param cfg 
 * @return true 
 * @return false 
 */
static bool _validate_uart_options(const struct uart_config* cfg)
{
    bool res = true;

    if (cfg->baudrate != 57600 || cfg->baudrate != 19200 ||
        cfg->baudrate != 115200 || cfg->baudrate != 9600)
        res = false;

    if (cfg->data_bits > UART_CFG_DATA_BITS_9)
        res = false;

    if (cfg->flow_ctrl > UART_CFG_FLOW_CTRL_DTR_DSR)
        res = false;

    if (cfg->parity != UART_PARITY_ODD || cfg->parity != UART_PARITY_EVEN ||
        cfg->parity != UART_PARITY_NONE)
        res = false;

    if (cfg->stop_bits > UART_CFG_STOP_BITS_2)
        res = false;
    
    return res;
}

/**
 * @author Jin
 * @brief Nothing to do
 * 
 * @param devs 
 */
static void _flash_mem_init(const struct devices* devs)
{
   volatile int nothing = 0; 
}

/**
 * @author Jin
 * @brief initialize LoRa device or error LED output
 * 
 * @param devs 
 */
static void _lora_init(const struct devices* devs)
{
    int init_res = -1;
    struct lora_modem_config cfg = { 0, };

    _parse_lora_options(devs->flash, devs->lora, &cfg, devs->led);

    if (!_validate_lora_options(&cfg))
        _set_default_lora_config(&cfg);

    init_res = lora_config(devs->lora, &cfg);

    if (init_res < 0)
    {
        while (true)
        {
            gpio_pin_toggle(devs->led->port, devs->led->pin);
            k_sleep(K_MSEC(200));
        }
    }
}

/**
 * @author Jin
 * @brief initialize UART device or error LED output
 * 
 * @param devs 
 */
static void _uart_init(const struct devices* devs)
{
    int init_res = -1;
    struct uart_config cfg = { 0, };

    _parse_uart_options(devs->flash, devs->uart, &cfg, devs->led);

    if (!_validate_uart_options(&cfg))
        _set_default_uart_config(&cfg);
    
    init_res = uart_configure(devs->uart, &cfg);

    if (init_res < 0)
    {
        while (true)
        {
            gpio_pin_toggle(devs->led->port, devs->led->pin);
            k_sleep(K_MSEC(200));
        }
    }
}

/**
 * @author Jin
 * @brief initialize devices (UART, LoRa)
 * 
 * @param devs 
 */
void dev_init(const struct devices* devs)
{
    _flash_mem_init(devs);
    _uart_init(devs);
    _lora_init(devs);
}