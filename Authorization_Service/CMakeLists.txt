cmake_minimum_required(VERSION 3.26)



project(authorization_service LANGUAGES CXX VERSION ${ENGINE_VERSION})



add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/auth_lib ${CMAKE_CURRENT_BINARY_DIR}/auth_lib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/client ${CMAKE_CURRENT_BINARY_DIR}/client)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/server ${CMAKE_CURRENT_BINARY_DIR}/server)
