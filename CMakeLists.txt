cmake_minimum_required(VERSION 3.10)

project(clipboardy)

set(CMAKE_CXX_STANDARD 17)

# Platform-specific settings
if (MSVC)
    if(NOT DEFINED BOOST_ROOT)
        set(BOOST_ROOT $ENV{BOOST_ROOT})
    endif()

    # Windows-specific packages and flags
    add_compile_options(/bigobj)
    add_definitions(-D_WIN32_WINNT=0x0601)  # fixes the _WIN32_WINNT warning

    # Windows-specific includes
    include_directories(${CMAKE_SOURCE_DIR}/windows/headers)
    if(BOOST_ROOT)
        include_directories(${BOOST_ROOT})
    else()
        message(FATAL_ERROR "Please set BOOST_ROOT to point to your Boost installation.")
    endif()

    # Windows-specific source files
    file(GLOB WINDOWS_SOURCES ${CMAKE_SOURCE_DIR}/windows/*.cpp)
elseif (UNIX AND NOT APPLE)
    # Linux-specific packages and flags
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(XCB REQUIRED xcb)

    include_directories(${XCB_INCLUDE_DIRS})
    link_directories(${XCB_LIBRARY_DIRS})
    add_definitions(${XCB_CFLAGS_OTHER})

    # Linux-specific includes
    include_directories(${CMAKE_SOURCE_DIR}/linux/headers)

    # Linux-specific source files
    file(GLOB LINUX_SOURCES ${CMAKE_SOURCE_DIR}/linux/*.cpp)
endif()

# Shared (cross-platform) sources
include_directories(${CMAKE_SOURCE_DIR}/commons/headers)
file(GLOB COMMON_SOURCES ${CMAKE_SOURCE_DIR}/commons/*.cpp)

# Combine sources
set(ALL_SOURCES
    ${COMMON_SOURCES}
    ${WINDOWS_SOURCES}
    ${LINUX_SOURCES}
)

# Add executable
add_executable(clipboardy ${ALL_SOURCES})

# Linux: link XCB
if (UNIX AND NOT APPLE)
    target_link_libraries(clipboardy ${XCB_LIBRARIES})
endif()
