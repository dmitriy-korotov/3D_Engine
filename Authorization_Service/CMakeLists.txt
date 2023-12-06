cmake_minimum_required(VERSION 3.26)



project(auth_server)



add_subdirectory(../external/asio-1.28.0 ${CMAKE_CURRENT_BINARY_DIR}/asio-1.28.0)



set(AUTH_COMMON_LIB auth_lib)

set(AUTH_CLIENT_LIB auth_client)



set(AUTH_SERVICE_HEADERS
	include/engine/authorization/server.hpp
)

set(AUTH_SERVICE_LIB_HEADERS
	include/engine/authorization/client.hpp
)

set(AUTH_SERVICE_SOURCES
	src/main.cpp

	src/engine/authorization/server.cpp
)

set(AUTH_SERVICE_LIB_SOURCES
	src/engine/authorization/client.cpp
)

set(AUTH_SERVICE_ALL_FILES ${AUTH_SERVICE_HEADERS} ${AUTH_SERVICE_SOURCES})
set(AUTH_SERVICE_LIB_ALL_FILES ${AUTH_SERVICE_LIB_HEADERS} ${AUTH_SERVICE_LIB_SOURCES})



source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${AUTH_SERVICE_ALL_FILES})



add_library(${AUTH_COMMON_LIB} STATIC ${AUTH_SERVICE_LIB_ALL_FILES})



add_executable(${PROJECT_NAME} ${AUTH_SERVICE_HEADERS} ${AUTH_SERVICE_SOURCES})



target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE uengine::utility asio)



target_include_directories(${AUTH_COMMON_LIB} PUBLIC include)

target_link_libraries(${AUTH_COMMON_LIB} PRIVATE uengine asio)
