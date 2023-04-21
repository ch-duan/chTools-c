cmake_minimum_required(VERSION 3.0.0)
project(chTools VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB SC_FILES "*.c" "*.cpp" "*.h")
include_directories(./encode ./encode/binary ./string ./ ./crc)

add_subdirectory(encode/binary)

add_subdirectory(strings)
add_subdirectory(crc)

add_executable(chTools main.c ${SC_FILES})
target_link_libraries(chTools encode_binary strings crc)
include_directories(D:/env/mingw-w64/x86_64-8.1.0-win32-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32/include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
