cmake_minimum_required(VERSION 3.26)



set(ENGINE_LOG_LIB logging CACHE INTERNAL "")

project(${ENGINE_LOG_LIB})



set(ENGINE_LOG_LIB_HEADERS
			include/engine/logging/log.hpp
)

set(ENGINE_LOG_LIB_SOURCES
	
)

set(ENGINE_LOG_LIB_ALL_FILES ${ENGINE_LOG_LIB_HEADERS} ${ENGINE_LOG_LIB_SOURCES})



add_library(${ENGINE_LOG_LIB} INTERFACE)
add_library(${ENGINE_ALIAS}::${ENGINE_LOG_LIB} ALIAS ${ENGINE_LOG_LIB})

target_include_directories(${ENGINE_LOG_LIB} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${ENGINE_LOG_LIB} INTERFACE spdlog)

set_target_properties(${ENGINE_LOG_LIB} PROPERTIES LINKER_LANGUAGE CXX)

target_compile_features(${ENGINE_LOG_LIB} INTERFACE cxx_std_20)



set_target_properties(${ENGINE_LOG_LIB} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ENGINE_BINARY_DIR})