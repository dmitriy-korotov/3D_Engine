cmake_minimum_required(VERSION 3.26)



set(ENGINE_VERSION 0.0.1 CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(ENGINE_EXTERNAL_LIBS_DIRECTORY external)
set(ENGINE_BINARY_DIR ${CMAKE_BINARY_DIR}/bin/)



project(uengine_project LANGUAGES CXX VERSION ${ENGINE_VERSION})



option(ENIGNE_BUILD_TESTS ON "Building engine tests")
option(ENGINE_ENABLE_ADDRESS_SANITIZER OFF "Enable address sanitizer")



add_subdirectory(${ENGINE_EXTERNAL_LIBS_DIRECTORY}/spdlog ${CMAKE_CURRENT_BINARY_DIR}/libs/spdlog)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(${ENGINE_EXTERNAL_LIBS_DIRECTORY}/json ${CMAKE_CURRENT_BINARY_DIR}/libs/json)

add_subdirectory(${ENGINE_EXTERNAL_LIBS_DIRECTORY}/stb ${CMAKE_CURRENT_BINARY_DIR}/libs/stb)

add_subdirectory(${ENGINE_EXTERNAL_LIBS_DIRECTORY}/glm ${CMAKE_CURRENT_BINARY_DIR}/libs/glm)

add_subdirectory(${ENGINE_EXTERNAL_LIBS_DIRECTORY}/glfw ${CMAKE_CURRENT_BINARY_DIR}/libs/glfw)

add_subdirectory(${ENGINE_EXTERNAL_LIBS_DIRECTORY}/glad ${CMAKE_CURRENT_BINARY_DIR}/libs/glad)

set(ASSIMP_BUILD_TESTS OFF CACHE INTERNAL "")
set(ASSIMP_INSTALL OFF CACHE INTERNAL "")
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")

add_subdirectory(${ENGINE_EXTERNAL_LIBS_DIRECTORY}/assimp ${CMAKE_CURRENT_BINARY_DIR}/libs/assimp)

add_subdirectory(${ENGINE_EXTERNAL_LIBS_DIRECTORY}/imgui ${CMAKE_CURRENT_BINARY_DIR}/libs/imgui)

add_subdirectory(${ENGINE_EXTERNAL_LIBS_DIRECTORY}/asio-1.28.0 ${CMAKE_CURRENT_BINARY_DIR}/libs/asio-1.28.0)

set(SKIP_BUILD_TEST ON)
set(PostgreSQL_ROOT "C:/Program Files/PostgreSQL/15" CACHE INTERNAL "")

add_subdirectory(${ENGINE_EXTERNAL_LIBS_DIRECTORY}/libpqxx ${CMAKE_CURRENT_BINARY_DIR}/libs/libpqxx)

if (${ENGINE_BUILD_TESTS})
	add_subdirectory(${ENGINE_EXTERNAL_LIBS_DIRECTORY}/gtest ${CMAKE_CURRENT_BINARY_DIR}/libs/tests)
endif()





add_subdirectory(core)
add_subdirectory(editor)
add_subdirectory(authorization_service)
if (${ENGINE_BUILD_TESTS})
	add_subdirectory(tests)
endif()



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
		pqxx

		PROPERTIES FOLDER external
)

if (${ENGINE_ENABLE_ADDRESS_SANITIZER})
	set_target_properties(uengine PROPERTIES COMPILE_FLAGS -fsanitize=address)
endif()

if (${ENGINE_BUILD_TESTS})
	set_target_properties(
			gmock
			gmock_main
			gtest
			gtest_main

			PROPERTIES FOLDER external
	)
endif()
