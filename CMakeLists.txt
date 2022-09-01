cmake_minimum_required(VERSION 3.16)

project(edupage)

set(EP_LIB_NAME eplib)
set(EP_TEST_NAME eptest)

set(CMAKE_CXX_STANDARD 20)
set(EP_TEST
        src/test.cpp)
set(EP_SOURCES
        src/edupage.cpp)
set(EP_HEADERS
        include/edupage.hpp src/chromium.cpp)

set(ZLIB_USE_STATIC_LIBS ON)
find_package(ZLIB REQUIRED)

include_directories(include/)

# Test
add_executable(${EP_TEST_NAME}
        ${EP_TEST})
target_link_libraries(
        ${EP_TEST_NAME}
        PRIVATE
        ${EP_LIB_NAME}
)

# Library
add_library(${EP_LIB_NAME}
        ${EP_SOURCES}
        ${EP_HEADERS})
target_include_directories(
        ${EP_LIB_NAME}
        PRIVATE
        ${ZLIB_INCLUDE_DIRS}
)
target_link_libraries(
        ${EP_TEST_NAME}
        PRIVATE
        ${ZLIB_LIBRARIES}
)