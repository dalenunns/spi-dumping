# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)
#include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
# Set name of project (as PROJECT_NAME) and C/C++ Standards
project(spi-pio C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()
# point out the CMake, where to find the executable source file
 add_executable(${PROJECT_NAME}
         clocked_input
 )

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/clocked_input.pio)

# create map/bin/hex/uf2 files.
pico_add_extra_outputs(${PROJECT_NAME})
# Pull in our pico_stdlib which pulls in commonly used features (gpio, timer-delay etc)
# target_link_libraries(${PROJECT_NAME}
#             pico_stdlib
#             hardware_spi
# )

#pico_generate_pio_header(pio_clocked_input ${CMAKE_CURRENT_LIST_DIR}/clocked_input.pio)

target_sources(${PROJECT_NAME} PRIVATE clocked_input.c)

target_link_libraries(${PROJECT_NAME} PRIVATE
        pico_stdlib
        hardware_pio
        hardware_spi
        )

#pico_add_extra_outputs(pio_clocked_input)


pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)