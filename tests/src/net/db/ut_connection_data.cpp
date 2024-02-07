#include <gtest/gtest.h>

#include <engine/net/db/connection_data.hpp>





using namespace engine::net::db;

TEST(ut_connection_data, zero_parametrs_test)
{
	connection_data conn_data;

	ASSERT_EQ(conn_data.toString(), "");
}



TEST(ut_connection_data, one_parametr_test)
{
	connection_data conn_data_1
	{
		.dbname = "users"
	};

	connection_data conn_data_2
	{
		.hostaddr = "125.23.1.0"
	};

	ASSERT_EQ(conn_data_1.toString(), "dbname=users");
	ASSERT_EQ(conn_data_2.toString(), "hostaddr=125.23.1.0");
}



TEST(ut_connection_data, two_parametrs_test)
{
	connection_data conn_data_1
	{
		.dbname = "orders",
		.password = "12345"
	};

	ASSERT_EQ(conn_data_1.toString(), "dbname=orders password=12345");
}



TEST(ut_connection_data, four_parametrs_test)
{
	connection_data conn_data_1
	{
		.dbname = "orders",
		.hostaddr = "23.12.1.45",
		.user = "dima",
		.password = "12345"
	};

	ASSERT_EQ(conn_data_1.toString(), "dbname=orders hostaddr=23.12.1.45 user=dima password=12345");
}