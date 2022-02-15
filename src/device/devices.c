#include "./devices.h"

#include "../app.h"

#include <device.h>
#include <drivers/flash.h>
#include <drivers/gpio.h>
#include <drivers/uart.h>
#include <drivers/lora.h>
#include <drivers/i2c.h>

static struct devices devs = { 0, };

static const struct gpio_dt_spec led_spec =
    GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

static const struct gpio_dt_spec fr_btn_spec =
    GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);

static const struct gpio_dt_spec dfu_btn_spec =
    GPIO_DT_SPEC_GET(DT_ALIAS(sw1), gpios);

/**
 * @brief flash memory
 * 
 * @param devs 
 */
static void _get_flash(struct devices* devs)
{
    devs->flash = device_get_binding(DT_CHOSEN_ZEPHYR_FLASH_CONTROLLER_LABEL);
}

/**
 * @brief GPIO LED
 * 
 * @param devs 
 */
static void _get_led(struct devices* devs)
{
    devs->led = &led_spec;
}

/**
 * @brief GPIO Factory reset button
 * 
 * @param devs 
 */
static void _get_fr_btn(struct devices* devs)
{
    devs->fr_btn = &fr_btn_spec;
}

/**
 * @brief GPIO DFU mode button
 * 
 * @param devs 
 */
static void _get_dfu_btn(struct devices* devs)
{
    devs->dfu_btn = &dfu_btn_spec;
}

/**
 * @brief UART device
 * 
 * @param devs 
 */
static void _get_uart(struct devices* devs)
{
    devs->uart = DEVICE_DT_GET(DT_CHOSEN(zephyr_shell_uart));

}

/**
 * @author Jin
 * @brief LoRa device
 * 
 * @param devs 
 */
static void _get_lora(struct devices* devs)
{
    devs->lora = DEVICE_DT_GET(DT_ALIAS(lora0));
}

/**
 * @author Jin
 * @brief SPI
 * 
 * @param devs 
 */
static void _get_spi(struct devices* devs)
{
     devs->spi = DEVICE_DT_GET(DT_NODELABEL(spi1));
}

/**
 * @author Jin
 * @brief I2C
 * 
 * @param devs 
 */
static void _get_i2c(struct devices* devs)
{
    devs->i2c = DEVICE_DT_GET(DT_NODELABEL(i2c2));
}

/**
 * @author Jin
 * @brief Get the devices object
 * 
 * @param devs 
 */
void get_devices(struct app_data* app_data)
{
    app_data->devs = &devs;
    _get_led(app_data->devs);
    _get_fr_btn(app_data->devs);
    _get_dfu_btn(app_data->devs);
    _get_flash(app_data->devs);

    _get_uart(app_data->devs);
    k_mutex_init(&app_data->uart_output_mtx);
    
    _get_flash(app_data->devs);
    _get_lora(app_data->devs);
    _get_i2c(app_data->devs);
    _get_spi(app_data->devs);
}

/**
 * @author Jin
 * @brief 
 * 
 * @param led_dev 
 */
void enable_led_error(const struct gpio_dt_spec* led_dev)
{
    while (true)
    {
        gpio_pin_toggle(led_dev->port, led_dev->pin);
        k_sleep(K_MSEC(200));
    }
}