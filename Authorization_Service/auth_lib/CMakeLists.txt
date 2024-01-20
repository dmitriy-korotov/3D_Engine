cmake_minimum_required(VERSION 3.26)



set(AUTH_SERVICE_LIB auth_lib CACHE INTERNAL "")

project(${AUTH_SERVICE_LIB} LANGUAGES CXX VERSION ${ENGINE_VERSION})



set(AUTH_SERVICE_LIB_HEADERS

        include/auth/fwd.hpp
        include/auth/fwd/user.hpp

        include/auth/user.hpp

)

set(AUTH_SERVICE_LIB_SOURCES

        src/auth/user.cpp

)

set(AUTH_SERVICE_LIB_ALL_FILES ${AUTH_SERVICE_LIB_HEADERS} ${AUTH_SERVICE_LIB_SOURCES})



source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${AUTH_SERVICE_LIB_ALL_FILES})



add_library(${AUTH_SERVICE_LIB} STATIC ${AUTH_SERVICE_LIB_ALL_FILES})



target_include_directories(${AUTH_SERVICE_LIB} PUBLIC include)



set_target_properties(${AUTH_SERVICE_LIB} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${ENGINE_BINARY_DIR})