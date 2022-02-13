#ifndef __DEVICE_DEVICES_H__
#define __DEVICE_DEVICES_H__

#ifdef __cplusplus
extern "C"
{
#endif

struct device;

struct devices
{
    const struct device* led;
    const struct device* fr_btn;
    const struct device* uart;
    const struct device* lora;
    const struct device* flash;
    const struct device* i2c;
    const struct device* spi;
};

void get_devices(struct devices*);

#ifdef __cplusplus
}
#endif

#endif