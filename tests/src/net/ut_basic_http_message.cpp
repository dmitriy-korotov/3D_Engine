#include <gtest/gtest.h>

#include <engine/net/http/request.hpp>
#include <engine/net/http/response.hpp>
#include <engine/net/http/json_body.hpp>
#include <engine/net/http/string_body.hpp>



using namespace engine::net::http;

class http_message_common : public testing::Test
{
public:

	request<json_body> request;
	response<string_body> response;

	void SetUp() noexcept
	{ }

	void TearDown() noexcept
	{ }

};



TEST_F(http_message_common, http_header_to_string_test)
{
	EXPECT_EQ(toString(http_header::connection), "Connection");
	EXPECT_EQ(toString(http_header::content_lenth), "Content-Length");
	EXPECT_EQ(toString(http_header::content_type), "Content-Type");
	EXPECT_EQ(toString(http_header::cookie), "Cookie");
	EXPECT_EQ(toString(http_header::date), "Date");
	EXPECT_EQ(toString(http_header::host), "Host");
	EXPECT_EQ(toString(http_header::encoding), "Accept-Encoding");
	EXPECT_EQ(toString(http_header::server), "Server");
	EXPECT_EQ(toString(http_header::keep_alive), "Keep-Alive");
	EXPECT_EQ(toString(http_header::accept), "Accept");
}



TEST_F(http_message_common, get_and_set_methods_test)
{
	request.setHttpVersion({ .major = 2, .minor = 5 });
	request.emplaceHeader("x-Content", "25");
	request.emplaceHeader(http_header::keep_alive, "timeout=5");
	request.emplaceHeaders({ {"x-Cost", "100"}, {"Label", "title"}, {"23", "URL"} });
	request.setBody("{\"user_id\": 126}");

	EXPECT_EQ(request.getHttpVersion().major, 2);
	EXPECT_EQ(request.getHttpVersion().minor, 5);

	EXPECT_EQ(request.at("x-Content"), "25");
	EXPECT_EQ(request.at(http_header::keep_alive), "timeout=5");
	EXPECT_EQ(request.get("x-Cost").value(), "100");
	EXPECT_EQ(request.get("Label").value(), "title");
	EXPECT_EQ(request.get("23").value(), "URL");

	EXPECT_EQ(request.getBody().dump(), "{\"user_id\":126}");
}



TEST_F(http_message_common, prepare_test)
{
	response.setHttpVersion({ .major = 2, .minor = 5 });
	response.setBody("TEST");
	response.prepare();

	std::string expected = "HTTP/2.5 200 OK\r\n"
						   "Content-Length: 4\r\n\r\n"
						   "TEST\r\n";

	ASSERT_EQ(response.build(), expected);
}



TEST_F(http_message_common, reset_test)
{
	response.setHttpVersion({ .major = 2, .minor = 5 });
	request.emplaceHeader("Content", "10000");
	request.emplaceHeader(http_header::server, "Yandex");
	response.setBody("Hello, world!");

	response.reset();

	EXPECT_EQ(response.hasBody(), false);
	EXPECT_EQ(response.getHttpVersion().major, 1);
	EXPECT_EQ(response.getHttpVersion().minor, 1);
}