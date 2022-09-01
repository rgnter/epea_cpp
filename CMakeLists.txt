cmake_minimum_required(VERSION 3.16)

project(epea)

set(CMAKE_CXX_STANDARD 20)
set(EPEA_SOURCES
        src/algorithms.cpp)
set(EPEA_HEADERS
        include/epea.hpp
        src/chromium.cpp)

set(ZLIB_USE_STATIC_LIBS ON)
find_package(ZLIB REQUIRED)

include_directories(include/)

# Library
add_library(${PROJECT_NAME}
        ${EPEA_SOURCES}
        ${EPEA_HEADERS})
target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${ZLIB_INCLUDE_DIRS}
)
target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        ${ZLIB_LIBRARIES}
)