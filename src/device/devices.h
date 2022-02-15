#ifndef __DEVICE_DEVICES_H__
#define __DEVICE_DEVICES_H__

#ifdef __cplusplus
extern "C"
{
#endif

struct app_data;

struct gpio_dt_spec;
struct device;

struct devices
{
    const struct gpio_dt_spec* led;
    const struct gpio_dt_spec* fr_btn;
    const struct gpio_dt_spec* dfu_btn;
    const struct device*       uart;
    const struct device*       lora;
    const struct device*       flash;
    const struct device*       i2c;
    const struct device*       spi;
};

void get_devices(struct app_data*);

void enable_led_error(const struct gpio_dt_spec*);

#ifdef __cplusplus
}
#endif

#endif