cmake_minimum_required(VERSION 3.26)

project(Authorization_Service)



set(AUTH_LIB authlib)



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



add_library(${AUTH_LIB} STATIC ${AUTH_SERVICE_LIB_ALL_FILES})



add_executable(${PROJECT_NAME} ${AUTH_SERVICE_HEADERS} ${AUTH_SERVICE_SOURCES})



target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE 3D_Engine_Core)



target_include_directories(${AUTH_LIB} PUBLIC include)

target_link_libraries(${AUTH_LIB} PRIVATE 3D_Engine_Core)
