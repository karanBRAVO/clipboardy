# Cross-platform sources and headers
include_directories(${CMAKE_SOURCE_DIR}/platform/cross/headers)
set(SERVER_SOURCES
    ${CMAKE_SOURCE_DIR}/server/main.cpp
    ${CMAKE_SOURCE_DIR}/platform/cross/clip.cpp
    ${CMAKE_SOURCE_DIR}/platform/cross/http_session.cpp
    ${CMAKE_SOURCE_DIR}/platform/cross/listener.cpp
    ${CMAKE_SOURCE_DIR}/platform/cross/shared_state.cpp
    ${CMAKE_SOURCE_DIR}/platform/cross/websocket_session.cpp
)

# Platform-specific includes and sources
if (WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/platform/windows/headers)
    list(APPEND SERVER_SOURCES
        ${CMAKE_SOURCE_DIR}/platform/windows/clip_win.cpp
    )
elseif (UNIX AND NOT APPLE)
    include_directories(${CMAKE_SOURCE_DIR}/platform/linux/headers)
    list(APPEND SERVER_SOURCES
        ${CMAKE_SOURCE_DIR}/platform/linux/clip_x11.cpp
    )
endif()
