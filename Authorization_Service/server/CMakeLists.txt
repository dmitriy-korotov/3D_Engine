cmake_minimum_required(VERSION 3.26)



set(AUTH_SERVICE_SERVER auth_server)

project(${AUTH_SERVICE_SERVER})



set(CMAKE_CXX_STANDARD 20)



set(SKIP_BUILD_TEST ON)
set(PostgreSQL_ROOT "C:/Program Files/PostgreSQL/15" CACHE INTERNAL "")

set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
add_subdirectory(../../external/libpqxx ${CMAKE_CURRENT_BINARY_DIR}/libpqxx)
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")



set(AUTH_SERVICE_SERVER_HEADERS
        include/auth/authorization_server.hpp
)

set(AUTH_SERVICE_SERVER_SOURCES
        src/auth/authorization_server.cpp
        src/main.cpp
)

set(AUTH_SERVICE_SERVER_ALL_FILES ${AUTH_SERVICE_SERVER_HEADERS} ${AUTH_SERVICE_SERVER_SOURCES})



source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${AUTH_SERVICE_SERVER_ALL_FILES})



add_executable(${AUTH_SERVICE_SERVER} ${AUTH_SERVICE_SERVER_ALL_FILES})



target_include_directories(${AUTH_SERVICE_SERVER} PUBLIC include)

target_link_directories(${AUTH_SERVICE_SERVER} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/pqxxlib/src/Debug)
#target_link_directories(${AUTH_SERVICE_SERVER} PRIVATE "C:/Program Files/PostgreSQL/15/lib")



target_link_libraries(${AUTH_SERVICE_SERVER} PRIVATE ${AUTH_SERVICE_LIB} pqxx)