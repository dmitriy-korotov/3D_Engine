cmake_minimum_required(VERSION 3.26)



project(engine_tests LANGUAGES CXX VERSION ${ENGINE_VERSION})



set(ENGINE_TEST_FILES

	src/main.cpp

	src/net/ut_url.cpp
	src/net/ut_basic_http_message.cpp
	src/net/ut_request.cpp
	src/net/ut_response.cpp
	src/net/ut_http_parsing.cpp
	src/net/ut_host.cpp

)



source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_TEST_FILES})



add_executable(${PROJECT_NAME} ${ENGINE_TEST_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest ${ENGINE_ALIAS}::${ENGINE_NET_LIB})



set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ENGINE_BINARY_DIR})