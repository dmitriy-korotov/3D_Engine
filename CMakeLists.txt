cmake_minimum_required(VERSION 3.26)

project(3D_Engine)

add_subdirectory(3D_Engine_Core)
add_subdirectory(3D_Engine_Editor)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT 3D_Engine_Editor)
