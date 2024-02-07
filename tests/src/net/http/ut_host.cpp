#include <gtest/gtest.h>

#include <engine/net/http/host.hpp>



using namespace engine::net::http;

TEST(host_class, construct_from_address_and_port_test)
{
	host host("127.0.0.1", 8000);

	ASSERT_EQ(host.getAddress(), "127.0.0.1");
	ASSERT_EQ(host.getPort(), 8000);
}



TEST(host_class, get_and_set_methods_test)
{
	host host;

	host.setAddress("4.43.1.65");
	host.setPort(80);

	ASSERT_EQ(host.getAddress(), "4.43.1.65");
	ASSERT_EQ(host.getPort(), 80);
}



TEST(host_class, construct_from_hostname_and_port_test)
{
	ASSERT_NO_THROW(host host("google.com", 80));
}