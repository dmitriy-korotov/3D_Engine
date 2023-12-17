cmake_minimum_required(VERSION 3.26)

project(uengine_project)

add_subdirectory(core)
add_subdirectory(editor)
add_subdirectory(authorization_service)
add_subdirectory(tests)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT editor)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(
		uninstall
		zlibstatic
		spdlog
		imgui
		glad
		assimp
		UpdateAssimpLibsDebugSymbolsAndDLLs
		gmock
		gmock_main
		gmock
		gtest_main

		PROPERTIES FOLDER external
)