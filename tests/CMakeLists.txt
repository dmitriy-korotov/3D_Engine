cmake_minimum_required(VERSION 3.26)

project(engine_tests)



add_subdirectory(../external/gtest ${CMAKE_CURRENT_BINARY_DIR}/tests)



set(ENGINE_TEST_FILES

	src/main.cpp

	src/net/ut_basic_http_message.cpp
	src/net/ut_request.cpp
	src/net/ut_response.cpp

)



source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_TEST_FILES})



add_executable(${PROJECT_NAME} ${ENGINE_TEST_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest uengine::net)
