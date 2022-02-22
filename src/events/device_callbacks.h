#ifndef __EVENTS_DEVICE_CALLBACKS_H__
#define __EVENTS_DEVICE_CALLBACKS_H__

#ifdef __cplusplus
extern "C"
{
#endif

enum lorawan_datarate;

void uart_irq_callback_handler(const struct device*, void*);
void lorawan_recv_callback_handler(uint8_t, uint8_t, const struct device*, uint8_t*,
                                   uint16_t, int16_t, int8_t);

void lorawan_datarate_changed_callback_handler(enum lorawan_datarate);

#ifdef __cplusplus
}
#endif

#endif 