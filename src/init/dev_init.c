#include "./dev_init.h"
#include "../app.h"
#include "../device/devices.h"
#include "../file/flash_data.h"

#include <drivers/gpio.h>
#include <drivers/uart.h>
#include <drivers/flash.h>
#include <drivers/lora.h>

#include <lorawan/lorawan.h>

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


uint8_t default_dev_eui[] = { 0xDD, 0xEE, 0xAA, 0xDD, 0xBB, 0xEE, 0xEE, 0xFF };
uint8_t default_join_eui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t default_app_key[] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE,
                              0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88,
                              0x09, 0xCF, 0x4F, 0x3C };

/**
 * @author Jin
 * @brief sets to default LoRaWAN join options
 * 
 * @param cfg 
 */
static void _set_default_lorawan_config(struct lorawan_join_config* cfg)
{
    cfg->mode = LORAWAN_ACT_OTAA;
    cfg->dev_eui = default_dev_eui;
    cfg->otaa.join_eui = default_join_eui;
    cfg->otaa.app_key = default_app_key;
    cfg->otaa.nwk_key = default_app_key;
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
        enable_led_error(err_led);
}

static void _parse_lorawan_options(const struct device* flash_dev,
                                   struct lorawan_join_config* cfg,
                                   const struct gpio_dt_spec* err_led)
{
    int flash_read_res = flash_read_lorawan_config(flash_dev, cfg);

    if (flash_read_res < 0)
        enable_led_error(err_led);
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
        enable_led_error(err_led);
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
 * @brief 
 * 
 * @param cfg 
 * @return true 
 * @return false 
 */
static bool _validate_lorawan_options(const struct lorawan_join_config* cfg)
{
    bool res = true;

    if (cfg->mode != LORAWAN_ACT_OTAA ||
        cfg->mode != LORAWAN_ACT_ABP)
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
   (void)nothing;
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
        enable_led_error(devs->led);
    }

    init_res = flash_write_lora_config(devs->flash, &cfg);

    if (init_res < 0)
    {
        enable_led_error(devs->led);
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
        enable_led_error(devs->led);
    }

    init_res = flash_write_uart_config(devs->flash, &cfg);

    if (init_res < 0)
    {
        enable_led_error(devs->led);
    }
}

struct lorawan_join_config lorawan_cfg = { 0, };
/**
 * @author Jin
 * @brief 
 * 
 * @param devs 
 */
static void _lorawan_init(const struct devices* devs)
{
    _parse_lorawan_options(devs->flash, &lorawan_cfg, devs->led);

    if (!_validate_lorawan_options(&lorawan_cfg))
        _set_default_lorawan_config(&lorawan_cfg);    
}

/**
 * @author Jin
 * @brief disable LED output
 * 
 * @param devs 
 */
static void _gpio_init(const struct devices* devs)
{
    disable_led_error(devs->led);
}

// from main.c
extern struct app_data app_data;

/**
 * @author Jin
 * @brief initialize devices (UART, LoRa)
 * 
 * @param devs 
 */
void dev_init(const struct devices* devs)
{
    _gpio_init(devs);
    _flash_mem_init(devs);
    _uart_init(devs);
    _lora_init(devs);
    _lorawan_init(devs);
    app_data.lorawan_cfg = &lorawan_cfg;
}