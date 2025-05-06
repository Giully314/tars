cmake_minimum_required(VERSION 3.31)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD a9e1cf81-9932-4810-974b-6eccaf14e457)

project(TARS LANGUAGES CXX)

set(CMAKE_CXX_MODULE_STD 1)

set(CMAKE_CXX_STANDARD 26)

# TODO: set build or release

# TODO: set compiler flags

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)


add_executable(main)
target_sources(main PRIVATE main.cpp)
target_link_libraries(main PRIVATE tars)