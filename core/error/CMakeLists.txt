cmake_minimum_required(VERSION 3.26)



set(ENGINE_ERROR_LIB error CACHE INTERNAL "")

project(${ENGINE_ERROR_LIB})



set(ENGINE_ERROR_LIB_HEADERS

		include/engine/error/fwd.hpp
		include/engine/error/fwd/application_error.hpp
		include/engine/error/fwd/window_error.hpp
		include/engine/error/fwd/error.hpp
		
		include/engine/error/application_error.hpp
		include/engine/error/window_error.hpp

		include/engine/error/error.hpp
	
)

set(ENGINE_ERROR_LIB_SOURCES
		
		src/engine/error/error.cpp

)

set(ENGINE_ERROR_LIB_ALL_FILES ${ENGINE_ERROR_LIB_HEADERS} ${ENGINE_ERROR_LIB_SOURCES})



source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_ERROR_LIB_ALL_FILES})



add_library(${ENGINE_ERROR_LIB} STATIC ${ENGINE_ERROR_LIB_ALL_FILES})
add_library(${ENGINE_ALIAS}::${ENGINE_ERROR_LIB} ALIAS ${ENGINE_ERROR_LIB})



target_include_directories(${ENGINE_ERROR_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(${ENGINE_ERROR_LIB} PROPERTIES LINKER_LANGUAGE CXX)



set_target_properties(${ENGINE_ERROR_LIB} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${ENGINE_BINARY_DIR})
