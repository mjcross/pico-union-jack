cmake_minimum_required(VERSION 3.23)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico-displaydrivs C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(ili9341)
add_subdirectory(gfx)
add_subdirectory(speed_test
)
