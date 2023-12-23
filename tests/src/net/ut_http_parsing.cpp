#include <gtest/gtest.h>

#include <engine/net/http/request_parser.hpp>
#include <engine/net/http/response_parser.hpp>
#include <engine/net/http/string_body.hpp>
#include <engine/net/http/json_body.hpp>



using namespace engine::net::http;

TEST(http_parsing, request_parsing_test)
{
	std::string string_request =
		"GET /users?id=10 HTTP/2.0\r\n"
		"Content-Length: 10\r\n"
		"Host: Yandex\r\n"
		"Connection: keep-alive\r\n\r\n"
		"Test body!\r\n";

	request_parser<string_body> parser;
	parser.parse(string_request);

	auto request = std::move(parser).get();

	ASSERT_EQ(request.getMethod(), request_method::Get);
	ASSERT_EQ(request.getHttpVersion().major, 2);
	ASSERT_EQ(request.getHttpVersion().minor, 0);

	ASSERT_EQ(request.at(http_header::content_lenth), "10");
	ASSERT_EQ(request.at(http_header::host), "Yandex");
	ASSERT_EQ(request.at(http_header::connection), "keep-alive");

	ASSERT_EQ(request.getBody(), "Test body!");
}



TEST(http_parsing, response_parsing_test)
{
	std::string string_response =
		"HTTP/1.1 404 Not found\r\n"
		"Content-Length: 1550\r\n"
		"Server: google.com\r\n"
		"x-Field: something\r\n\r\n"
		"{\"key\": \"value\", \"name\": \"Dima\"}\r\n";

	response_parser<json_body> parser;
	parser.parse(string_response);

	auto response = parser.get();

	ASSERT_EQ(response.getStatus(), response_status::not_found);
	ASSERT_EQ(response.getHttpVersion().major, 1);
	ASSERT_EQ(response.getHttpVersion().minor, 1);

	ASSERT_EQ(response.at(http_header::content_lenth), "1550");
	ASSERT_EQ(response.at(http_header::server), "google.com");
	ASSERT_EQ(response.at("x-Field"), "something");

	auto body = std::move(response).getBody();

	ASSERT_EQ(std::string(body["key"]), "value");
	ASSERT_EQ(std::string(body["name"]), "Dima");
}