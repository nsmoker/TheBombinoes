cmake_minimum_required(VERSION 3.6)
project(TheBombinoes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/build/")

file(GLOB bombSrc 
    "src/*.h"
    "src/*.cpp"
)

add_executable(TheBombinoes
    ${bombSrc}
)

find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)

target_include_directories(TheBombinoes PUBLIC
    "$<BUILD_INTERFACE:${SDL2_INCLUDE_DIRS}>"
    "$<BUILD_INTERFACE:${SDL2TTF_INCLUDE_DIRS}>"
)

target_link_libraries(TheBombinoes PUBLIC
    ${SDL2_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
)