cmake_minimum_required(VERSION 3.15)

project(clipboardy)

set(CMAKE_CXX_STANDARD 17)

# Define options for which target to build
option(BUILD_CLIENT "Build the client executable" OFF)
option(BUILD_SERVER "Build the server executable" OFF)

if (MSVC)
    # set the boost root directory
    if(NOT DEFINED BOOST_ROOT)
        set(BOOST_ROOT $ENV{BOOST_ROOT})
    endif()

    if(BOOST_ROOT)
        include_directories(${BOOST_ROOT})
    else()
        message(FATAL_ERROR "Please set BOOST_ROOT to point to your Boost installation.")
    endif()

    # Windows-specific packages and flags
    add_compile_options(/bigobj)
    add_definitions(-D_WIN32_WINNT=0x0601)  # fixes the _WIN32_WINNT warning
elseif (UNIX AND NOT APPLE)
    # find xcb package
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(XCB REQUIRED xcb)

    include_directories(${XCB_INCLUDE_DIRS})
    link_directories(${XCB_LIBRARY_DIRS})
    add_definitions(${XCB_CFLAGS_OTHER})
endif()

# -------------------------
# Client target
# -------------------------

if (BUILD_CLIENT)
    include(${CMAKE_SOURCE_DIR}/cmake/client.cmake)
    add_executable(client ${CLIENT_SOURCES})

    if (UNIX AND NOT APPLE)
        target_link_libraries(client ${XCB_LIBRARIES})
    endif()
endif()

# -------------------------
# Server target
# -------------------------

if (BUILD_SERVER)
    include(${CMAKE_SOURCE_DIR}/cmake/server.cmake)
    add_executable(server ${SERVER_SOURCES})

    if (UNIX AND NOT APPLE)
        target_link_libraries(server ${XCB_LIBRARIES})
    endif()
endif()
