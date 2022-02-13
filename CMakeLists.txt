cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(my_zephyr_app)

target_sources(app PRIVATE
               src/at/ver.c
               src/at/id.c
               src/device/devices.c
               src/events/device_callbacks.c
               src/file/flash_data.c
               src/iface/at_command.c
               src/init/dev_init.c
               src/init/env_init.c
               src/telemetry/lora_io.c
               src/telemetry/uart_io.c
               src/main.c)
