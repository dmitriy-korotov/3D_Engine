#include <gtest/gtest.h>

#include <engine/net/http/request.hpp>
#include <engine/net/http/string_body.hpp>



using namespace engine::net::http;



TEST(HttpRequestTests, buid_method_test)
{
	request<string_body> request;

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



TEST(HttpRequestTests, copy_test)
{
	request<string_body> request;

	request.setMethod(request_method::Get);
	request.setHttpVersion({ .major = 2, .minor = 0 });
	request.setURL("/test/index.html");
	request.emplaceHeader(http_header::host, "engine");
	request.emplaceHeader(http_header::content_type, "application/json");
	request.setBody("<html>Hello World!</html>");

	auto new_request = request;
}