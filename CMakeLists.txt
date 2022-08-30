# Project is built with Makefile - this file is only included for CLion
cmake_minimum_required(VERSION 3.10)
project(TextReaderOverlay)

set(CMAKE_CXX_STANDARD 20)

include_directories($ENV{DEVKITPRO}/devkitA64/aarch64-none-elf/include)
include_directories($ENV{DEVKITPRO}/devkitA64/lib/gcc/aarch64-none-elf/12.1.0/include)
include_directories($ENV{DEVKITPRO}/portlibs/switch/include)
include_directories($ENV{DEVKITPRO}/portlibs/switch/include/freetype2)
include_directories($ENV{DEVKITPRO}/libnx/lib)
include_directories($ENV{DEVKITPRO}/libnx/include)
include_directories($ENV{DEVKITARM})

link_directories($ENV{DEVKITPRO}/libnx/lib)
link_directories($ENV{DEVKITPRO}/libnx/include)

include_directories(include)
include_directories(libs/libtesla/include)
include_directories(libs/json/include)

file(
        GLOB
        SOURCE_FILES
        "source/*.cpp"
)

add_executable(TextReaderOverlay ${SOURCE_FILES})