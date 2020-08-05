# Supplemental AVR (savor)

This is a library that I am writing while programming my ATMega328p. I'm wanting to start out with SPI, SD Cards, and support for the FAT32 file system.

## Usage

The easiest way to include this set of libraries in your project is to place this repo within your project as a submodule and build your project with CMAKE using:

```cmake
add_subdirectory(lib/savor)
target_link_libraries(${EXEC_NAME} savor)
```

A full example CMakeLists.txt for a project using this library is:

```cmake
cmake_minimum_required(VERSION 3.12)

project(SampleProject)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR atmega328p)
set(CMAKE_CROSSCOMPILING 1)

set(CMAKE_C_COMPILER avr-gcc)
set(SOURCES src/main.c)

set(CMAKE_C_FLAGS "-g -Wall -mcall-prologues -mmcu=${CMAKE_SYSTEM_PROCESSOR} -Os")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-gc-sections -Wl,-relax")

add_subdirectory(lib/savor)

add_executable(${PROJECT_NAME}.elf ${SOURCES})
target_link_libraries(${PROJECT_NAME}.elf savor)

set(CMAKE_C_OBJCOPY avr-objcopy CACHE PATH "" FORCE)


add_custom_target(hex ALL DEPENDS ${PROJECT_NAME}.hex)
add_custom_command(OUTPUT ${PROJECT_NAME}.hex COMMAND ${CMAKE_C_OBJCOPY} ARGS -R .eeprom -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex DEPENDS ${PROJECT_NAME}.elf )

add_custom_target(flash DEPENDS ${PROJECT_NAME}.hex)
add_custom_command(TARGET flash USES_TERMINAL COMMAND "avrdude -c stk500v2 -P $(pavr2cmd --prog-port) -p ${CMAKE_SYSTEM_PROCESSOR} -U flash:w:${PROJECT_NAME}.hex:i")
```

This requires `avrdude` and `pavr2cmd`. `pavr2cmd` is used for the Pololu AVR Programmer device.
