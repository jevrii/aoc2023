cmake_minimum_required(VERSION 3.12)
project(codeforces LANGUAGES CXX)

set(CMAKE_CPP_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -g")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build_result)

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,10000000")

# add_compile_definitions(LOCAL)
add_executable(codeforces main.cpp)
