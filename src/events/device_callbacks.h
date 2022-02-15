#ifndef __EVENTS_DEVICE_CALLBACKS_H__
#define __EVENTS_DEVICE_CALLBACKS_H__

#ifdef __cplusplus
extern "C"
{
#endif

void uart_irq_callback_handler(const struct device*, void*);
void lora_recv_callback_handler(const struct device*, uint8_t*, uint16_t, int16_t, int8_t);

#ifdef __cplusplus
}
#endif

#endif 