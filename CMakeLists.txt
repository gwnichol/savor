cmake_minimum_required(VERSION 3.11.1)

set(COMPOSITE_NAME savor)

add_library(savor INTERFACE)
target_include_directories(savor INTERFACE "./include")

function(add_library_comp LIB_NAME SOURCE_NAME)
	add_library(${COMPOSITE_NAME}-${LIB_NAME} ${SOURCE_NAME} ${ARGN})
	target_include_directories(${COMPOSITE_NAME}-${LIB_NAME} PRIVATE "./include")
	target_link_libraries(savor INTERFACE ${COMPOSITE_NAME}-${LIB_NAME})
endfunction()

add_library_comp(sd src/sd.c include/${COMPOSITE_NAME}/sd.h)
add_library_comp(spi src/spi.c include/${COMPOSITE_NAME}/spi.h)

