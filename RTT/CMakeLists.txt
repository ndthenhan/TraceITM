add_library(rtt STATIC
    SEGGER_RTT.c
    SEGGER_RTT_printf.c
)

target_link_libraries(rtt PUBLIC 
stm32cubemx
itmprintf
)

target_include_directories(rtt PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)