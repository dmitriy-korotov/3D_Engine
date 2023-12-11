cmake_minimum_required(VERSION 3.26)



set(AUTH_SERVICE_CLIENT auth_client)

project(${AUTH_SERVICE_CLIENT})



set(AUTH_SERVICE_CLIENT_HEADERS
        include/auth/authorization_client.hpp
)

set(AUTH_SERVICE_CLIENT_SOURCES
        src/auth/authorization_client.cpp
)

set(AUTH_SERVICE_CLIENT_ALL_FILES ${AUTH_SERVICE_CLIENT_HEADERS} ${AUTH_SERVICE_CLIENT_SOURCES})



source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${AUTH_SERVICE_CLIENT_ALL_FILES})



add_library(${AUTH_SERVICE_CLIENT} STATIC ${AUTH_SERVICE_CLIENT_ALL_FILES})



target_include_directories(${AUTH_SERVICE_CLIENT} PUBLIC include)

target_link_libraries(${AUTH_SERVICE_CLIENT} PUBLIC ${AUTH_SERVICE_LIB})