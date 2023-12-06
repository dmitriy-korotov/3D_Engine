cmake_minimum_required(VERSION 3.26)

project(uengine_project)

add_subdirectory(core)
add_subdirectory(editor)
add_subdirectory(authorization_service)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT editor)
