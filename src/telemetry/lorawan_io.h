#ifndef __TELEMETRY_LORAWAN_IO_H__
#define __TELEMETRY_LORAWAN_IO_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define TELEMETRY_LORAWAN_DATA_MAX_LEN (size_t)64U

struct device;

struct lorawan_data
{
    uint8_t port;
    bool    data_pending;
    uint8_t data[TELEMETRY_LORAWAN_DATA_MAX_LEN];
    size_t  size;
    int16_t rssi; // out
    int8_t  snr; // out
};

int lora_io_send(const struct device*, const struct lorawan_data*);

#ifdef __cplusplus
}
#endif

#endif