cmake_minimum_required(VERSION 3.0.0)
project(chTools VERSION 0.1.0)

include(CTest)
enable_testing()

FILE(GLOB SC_FILES "*.c" "*.h")
include_directories(./encode ./encode/binary ./string)

add_subdirectory(encode/binary)

add_subdirectory(strings)

add_executable(chTools main.c)
target_link_libraries(chTools encode_binary strings)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
