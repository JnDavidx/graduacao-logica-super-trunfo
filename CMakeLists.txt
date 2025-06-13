cmake_minimum_required(VERSION 3.31)
project(cartas_super_trunfo)

add_executable(card)

target_sources(
    card
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/card.c
    ${CMAKE_CURRENT_LIST_DIR}/src/main.c
    ${CMAKE_CURRENT_LIST_DIR}/src/prompt.c
)

set(CMAKE_C_STANDARD C99)
set(CMAKE_C_FLAGS "-Wall -std=c99")

target_include_directories(card PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)