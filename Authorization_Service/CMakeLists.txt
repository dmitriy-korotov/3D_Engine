cmake_minimum_required(VERSION 3.26)

project(Authorization_System)



set(AUTH_SERVICE_HEADERS
		
)

set(AUTH_SERVICE_SOURCES
	src/main.cpp
)



add_executable(${PROJECT_NAME} ${AUTH_SERVICE_HEADERS} ${AUTH_SERVICE_SOURCES})



target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE 3D_Engine_Core)
