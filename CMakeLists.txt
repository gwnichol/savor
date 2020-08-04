cmake_minimum_required(VERSION 3.11.1)

set(COMPOSITE_NAME savor)

add_library(${COMPOSITE_NAME}-spi src/spi.c)
target_include_directories(${COMPOSITE_NAME}-spi PRIVATE "./include")

add_library(savor INTERFACE)
target_link_libraries(savor INTERFACE ${COMPOSITE_NAME}-spi)
target_include_directories(savor INTERFACE "./include")

