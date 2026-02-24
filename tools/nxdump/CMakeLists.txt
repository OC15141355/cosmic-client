cmake_minimum_required(VERSION 3.14)
project(nxdump)
set(CMAKE_CXX_STANDARD 17)

# NoLifeNx sources from the client
set(NLNX_DIR ${CMAKE_SOURCE_DIR}/../../includes/nlnx)

add_executable(nxdump
    nxdump.cpp
    ${NLNX_DIR}/audio.cpp
    ${NLNX_DIR}/bitmap.cpp
    ${NLNX_DIR}/file.cpp
    ${NLNX_DIR}/node.cpp
    ${NLNX_DIR}/nx.cpp
)

target_include_directories(nxdump PRIVATE
    ${CMAKE_SOURCE_DIR}/../../includes
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LZ4 REQUIRED liblz4)

target_include_directories(nxdump PRIVATE ${LZ4_INCLUDE_DIRS})
target_link_directories(nxdump PRIVATE ${LZ4_LIBRARY_DIRS})
target_link_libraries(nxdump ${LZ4_LIBRARIES})
