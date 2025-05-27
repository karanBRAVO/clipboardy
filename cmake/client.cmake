# Cross-platform sources and headers
include_directories(${CMAKE_SOURCE_DIR}/platform/cross/headers)
set(CLIENT_SOURCES
    ${CMAKE_SOURCE_DIR}/client/main.cpp
    ${CMAKE_SOURCE_DIR}/platform/cross/clip.cpp
    ${CMAKE_SOURCE_DIR}/platform/cross/clipboard_manager.cpp
    ${CMAKE_SOURCE_DIR}/platform/cross/websocket_client.cpp
)

# Platform-specific sources and headers
if(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/platform/windows/headers)
    list(APPEND CLIENT_SOURCES
        ${CMAKE_SOURCE_DIR}/platform/windows/clip_win.cpp
    )
elseif(UNIX AND NOT APPLE)
    include_directories(${CMAKE_SOURCE_DIR}/platform/linux/headers)
    list(APPEND CLIENT_SOURCES
        ${CMAKE_SOURCE_DIR}/platform/linux/clip_x11.cpp
    )
endif()
