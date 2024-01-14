cmake_minimum_required(VERSION 3.26)



set(AUTH_SERVICE_SERVER auth_server)

project(${AUTH_SERVICE_SERVER} LANGUAGES CXX VERSION ${ENGINE_VERSION})



set(AUTH_SERVICE_SERVER_HEADERS

        include/auth/fwd.hpp
        include/auth/fwd/authorization_server.hpp

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



target_link_libraries(${AUTH_SERVICE_SERVER} PRIVATE
                ${AUTH_SERVICE_LIB}
                pqxx
                ${ENGINE_ALIAS}::${ENGINE_LOG_LIB}
                ${ENGINE_ALIAS}::${ENGINE_NET_LIB}
)



set_target_properties(${AUTH_SERVICE_SERVER} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ENGINE_BINARY_DIR})

file(GLOB LIB_FILES "${PostgreSQL_ROOT}/bin/*.dll")

file(COPY ${LIB_FILES}
     DESTINATION ${ENGINE_BINARY_DIR}/Debug)