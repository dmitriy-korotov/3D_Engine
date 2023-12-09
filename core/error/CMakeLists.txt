cmake_minimum_required(VERSION 3.26)



set(ENGINE_ERROR_LIB error CACHE INTERNAL "")

project(${ENGINE_ERROR_LIB})



set(ENGINE_ERROR_LIB_HEADERS

		include/engine/error/fwd.hpp
		include/engine/error/fwd/application_error.hpp
		include/engine/error/fwd/window_error.hpp
		
		include/engine/error/application_error.hpp
		include/engine/error/window_error.hpp
	
)

set(ENGINE_ERROR_LIB_SOURCES
	
)

set(ENGINE_ERROR_LIB_ALL_FILES ${ENGINE_ERROR_LIB_HEADERS} ${ENGINE_ERROR_LIB_SOURCES})



add_library(${ENGINE_ERROR_LIB} INTERFACE)
add_library(${ENGINE_ALIAS}::${ENGINE_ERROR_LIB} ALIAS ${ENGINE_ERROR_LIB})

target_include_directories(${ENGINE_ERROR_LIB} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(${ENGINE_ERROR_LIB} PROPERTIES LINKER_LANGUAGE CXX)

target_compile_features(${ENGINE_ERROR_LIB} INTERFACE cxx_std_20)