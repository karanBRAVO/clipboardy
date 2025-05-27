cmake_minimum_required(VERSION 3.10)

project(clipboardy)

set(CMAKE_CXX_STANDARD 17)

# Include headers
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Source files
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/includes/*.cpp
    ${CMAKE_SOURCE_DIR}/main.cpp
)

# Add executable
add_executable(clipboardy ${SOURCES})

# Find and link XCB
find_package(PkgConfig REQUIRED)
pkg_check_modules(XCB REQUIRED xcb)

include_directories(${XCB_INCLUDE_DIRS})
link_directories(${XCB_LIBRARY_DIRS})
add_definitions(${XCB_CFLAGS_OTHER})

target_link_libraries(clipboardy ${XCB_LIBRARIES})
