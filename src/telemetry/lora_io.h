#ifndef __TELEMETRY_LORA_IO_H__
#define __TELEMETRY_LORA_IO_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>

#define TELEMETRY_LORA_DATA_MAX_LEN (size_t)64U

struct device;

struct lora_data
{
    uint8_t data[TELEMETRY_LORA_DATA_MAX_LEN];
    size_t  size;
    int16_t rssi; // out
    int8_t  snr; // out
};

int lora_io_send(const struct device*, const struct lora_data*);

#ifdef __cplusplus
}
#endif

#endif