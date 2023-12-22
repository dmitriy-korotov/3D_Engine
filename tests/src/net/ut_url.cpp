#include <gtest/gtest.h>

#include <engine/net/http/url.hpp>



using namespace engine::net::http;



TEST(url_class, constructors_test)
{
	auto endpoint_without_qs = url("http://miet.ru/user");
	auto endpoint_with_qs = url("https://yandex.ru", { { "key", "value"}, {"name", "Dima"} });

	EXPECT_EQ(endpoint_without_qs.getAbsolutePath(), "http://miet.ru/user");
	EXPECT_EQ(endpoint_with_qs.getAbsolutePath(), "https://yandex.ru");

	const auto& query = endpoint_with_qs.getQueryString();

	EXPECT_EQ(query.at("key"), "value");
	EXPECT_EQ(query.at("name"), "Dima");
}



TEST(url_class, get_and_set_methods_test)
{
	auto endpoint = url("ftp:://google.com/registration");

	endpoint.setQueryString({ {"user_id", "1"}, {"size", "100"}, {"title", "World" } });

	EXPECT_EQ(endpoint.getAbsolutePath(), "ftp:://google.com/registration");

	const auto& query = endpoint.getQueryString();

	EXPECT_EQ(query.at("user_id"), "1");
	EXPECT_EQ(query.at("size"), "100");
	EXPECT_EQ(query.at("title"), "World");
}



TEST(url_class, parse_method_test)
{
	auto abs_endpoint = url::from_string("ftp:://google.com/registration");
	auto endpoint = url::from_string("/home/users/id");
	auto endpoint_with_query = url::from_string("/master/index.html?name=Maria&surname=Surname");

	EXPECT_EQ(abs_endpoint.getAbsolutePath(), "ftp:://google.com/registration");
	EXPECT_EQ(endpoint.getAbsolutePath(), "/home/users/id");
	EXPECT_EQ(endpoint_with_query.getAbsolutePath(), "/master/index.html");

	const auto& query = endpoint_with_query.getQueryString();

	EXPECT_EQ(query.at("name"), "Maria");
	EXPECT_EQ(query.at("surname"), "Surname");
}