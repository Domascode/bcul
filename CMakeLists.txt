cmake_minimum_required(VERSION 3.10)
project(bcul LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(bcul_lib STATIC
    src/bcul/bcul.cpp
    src/bcul/window_management.cpp
)

target_include_directories(bcul_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/bcul
)

target_link_libraries(bcul_lib PRIVATE
    gdi32
    user32
)

add_executable(bcul
    src/main.cpp
)

target_link_libraries(bcul PRIVATE
    bcul_lib
)

target_include_directories(bcul PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)