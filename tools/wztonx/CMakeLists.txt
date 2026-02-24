cmake_minimum_required(VERSION 3.14)
project(wztonx)
set(CMAKE_CXX_STANDARD 17)

add_executable(wztonx
    wztonx.cpp
    keys.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LZ4 REQUIRED liblz4)
pkg_check_modules(ZLIB REQUIRED zlib)

target_include_directories(wztonx PRIVATE ${LZ4_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS})
target_link_directories(wztonx PRIVATE ${LZ4_LIBRARY_DIRS} ${ZLIB_LIBRARY_DIRS})
target_link_libraries(wztonx ${LZ4_LIBRARIES} ${ZLIB_LIBRARIES})
