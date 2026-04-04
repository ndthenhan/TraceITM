add_library(randomapp STATIC
    random.c
    printrandom.c
)

target_link_libraries(randomapp PUBLIC 
stm32cubemx
itmprintf
)

target_include_directories(randomapp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)