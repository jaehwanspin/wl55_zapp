cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(my_zephyr_app)

set(APP_SRC src/at/test.c
            src/at/ver.c
            src/at/id.c
            src/at/fdefault.c
            src/at/reset.c
            src/at/low_power.c
            src/at/msg.c
            src/at/msg_hex.c
            src/at/c_msg.c
            src/at/c_msg_hex.c
            src/at/p_msg.c
            src/at/p_msg_hex.c
            src/at/ch.c
            src/at/dr.c
            src/at/adr.c
            src/at/rept.c
            src/at/retry.c
            src/at/power.c
            src/at/port.c
            src/at/mode.c
            src/device/devices.c
            src/events/device_callbacks.c
            src/file/flash_data.c
            src/iface/at_command.c
            src/init/dev_init.c
            src/init/env_init.c
            src/init/thread_init.c
            src/telemetry/lora_io.c
            src/telemetry/uart_io.c
            src/util/custom_typedefs.c
            src/workers/at_command.c
            src/workers/event.c
            src/workers/lorawan.c
            src/app.c
            src/main.c
)

target_sources(app PRIVATE ${APP_SRC})
