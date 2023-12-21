#include <gtest/gtest.h>

#include <engine/net/http/request.hpp>
#include <engine/net/http/string_body.hpp>



using namespace engine::net::http;

class http_request : public testing::Test
{
public:

	request<string_body> request;

	void SetUp() noexcept
	{ }

	void TearDown() noexcept
	{ }

};




TEST_F(http_request, buid_method_test)
{
	request.setMethod(request_method::Get);
	request.setHttpVersion({ .major = 2, .minor = 0 });
	request.setURL("/test/index.html");
	request.emplaceHeader(http_header::host, "engine");
	request.emplaceHeader(http_header::content_type, "application/json");
	request.setBody("<html>Hello World!</html>");

	std::string expected = "GET /test/index.html HTTP/2.0\r\n"
						   "Host: engine\r\n"
						   "Content-Type: application/json\r\n\r\n"
						   "<html>Hello World!</html>\r\n";

	ASSERT_EQ(request.build(), expected);
}



TEST_F(http_request, get_and_set_methods_test)
{
	request.setMethod(request_method::Post);
	request.setHttpVersion({ .major = 1, .minor = 2 });
	request.setURL("/api/v1/users");

	ASSERT_EQ(request.getMethod(), request_method::Post);
	ASSERT_EQ(request.getHttpVersion().major, 1);
	ASSERT_EQ(request.getHttpVersion().minor, 2);
	ASSERT_EQ(request.getURL(), "/api/v1/users");
}



TEST_F(http_request, request_method_to_string_test)
{
	EXPECT_EQ(toString(request_method::Get), "GET");
	EXPECT_EQ(toString(request_method::Delete), "DELETE");
	EXPECT_EQ(toString(request_method::Post), "POST");
	EXPECT_EQ(toString(request_method::Put), "PUT");
	EXPECT_EQ(toString(request_method::Trace), "TRACE");
}
