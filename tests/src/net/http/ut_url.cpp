#include <gtest/gtest.h>

#include <engine/net/http/url.hpp>
#include <engine/net/http/url_decoder.hpp>



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
	auto abs_endpoint = url::fromString("ftp:://google.com/registration");
	auto endpoint = url::fromString("/home/users/id");
	auto endpoint_with_query = url::fromString("/master/index.html?name=Maria&surname=Surname");

	EXPECT_EQ(abs_endpoint.getAbsolutePath(), "ftp:://google.com/registration");
	EXPECT_EQ(endpoint.getAbsolutePath(), "/home/users/id");
	EXPECT_EQ(endpoint_with_query.getAbsolutePath(), "/master/index.html");

	const auto& query = endpoint_with_query.getQueryString();

	EXPECT_EQ(query.at("name"), "Maria");
	EXPECT_EQ(query.at("surname"), "Surname");
}



TEST(url_class, decoding_test)
{
	auto test1 = "/path/to/file?my%20name=Dima&her%20surname=Korotov";
	auto test2 = "/?20%2010=Dima&her%20&20surname=Ivanov%32%21";
	auto test3 = "/yandex.ru?20%2010=Dima&her%20%20surname=Ivanov%20Ivan%20age";

	EXPECT_EQ(url_decoder::decode(test1), "/path/to/file?my name=Dima&her surname=Korotov");
	EXPECT_EQ(url_decoder::decode(test2), "/?20 10=Dima&her &20surname=Ivanov%32%21");
	EXPECT_EQ(url_decoder::decode(test3), "/yandex.ru?20 10=Dima&her  surname=Ivanov Ivan age");
}