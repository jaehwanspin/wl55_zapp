#include "./devices.h"

#include <device.h>
#include <drivers/flash.h>
#include <drivers/gpio.h>
#include <drivers/uart.h>
#include <drivers/lora.h>

static void _get_flash(struct devices* devs)
{
    devs->flash = device_get_binding(DT_CHOSEN_ZEPHYR_FLASH_CONTROLLER_LABEL);
}

static void _get_led(struct devices* devs)
{
    devs->led = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led0), gpios));
}

static void _get_uart(struct devices* devs)
{
    devs->uart = DEVICE_DT_GET(DT_CHOSEN(zephyr_shell_uart));
}

static void _get_lora(struct devices* devs)
{
    devs->lora = DEVICE_DT_GET(DT_ALIAS(lora0));
}

static void _get_spi(struct devices* devs)
{
     
}

static void _get_i2c(struct devices* devs)
{

}

void get_devices(struct devices* devs)
{
    _get_flash(devs);
    _get_led(devs);
    _get_uart(devs);
    _get_flash(devs);
    _get_lora(devs);
    _get_i2c(devs);
    _get_spi(devs);
}