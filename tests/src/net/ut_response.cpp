#include <gtest/gtest.h>

#include <engine/net/http/response.hpp>
#include <engine/net/http/json_body.hpp>





using namespace engine::net::http;

class http_response : public testing::Test
{
public:

	response<json_body> response;

	void SetUp() noexcept
	{ }

	void TearDown() noexcept
	{ }

};



TEST_F(http_response, build_method_test)
{
	response.setHttpVersion({ .major = 2, .minor = 0 });
	response.setStatus(response_status::not_found);
	response.emplaceHeader("x-Label", "value");
	response.emplaceHeader(http_header::encoding, "utf-8");
	response.setBody(json_t::parse("{\"key\":\"value\"}"));

	std::string expected = "HTTP/2.0 404 Not found\r\n"
						   "x-Label: value\r\n"
						   "Accept-Encoding: utf-8\r\n\r\n"
						   "{\"key\":\"value\"}\r\n";

	ASSERT_EQ(response.build(), expected);
}



TEST_F(http_response, get_and_set_methods_test)
{
	response.setHttpVersion({ .major = 2, .minor = 0 });
	response.setStatus(response_status::not_found);
	response.emplaceHeader("x-Label", "value");
	response.emplaceHeader(http_header::encoding, "utf-8");
	response.setBody(json_t::parse("{\"key\":\"value\"}"));

	EXPECT_EQ(response.getStatus(), response_status::not_found);
	EXPECT_EQ(response.getHttpVersion().major, 2);
	EXPECT_EQ(response.getHttpVersion().minor, 0);
}



TEST_F(http_response, response_status_to_string_test)
{
	auto ok = toString(response_status::ok);
	EXPECT_EQ(ok, "OK");

	auto forbidden = toString(response_status::forbidden);
	EXPECT_EQ(forbidden, "Forbidden");

	auto bad_getway = toString(response_status::bad_getway);
	EXPECT_EQ(bad_getway, "Bad getway");

	auto not_found = toString(response_status::not_found);
	EXPECT_EQ(not_found, "Not found");
}



TEST_F(http_response, response_status_code_test)
{
	EXPECT_EQ(static_cast<uint16_t>(response_status::ok), 200);
	EXPECT_EQ(static_cast<uint16_t>(response_status::bad_getway), 501);
	EXPECT_EQ(static_cast<uint16_t>(response_status::forbidden), 403);
	EXPECT_EQ(static_cast<uint16_t>(response_status::not_found), 404);
}