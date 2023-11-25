#include <iostream>

#include <asio/ip/address_v4.hpp>



int main(int _argc, const char** _argv)
{
	std::cout << "Hello world!" << std::endl;

	std::cout << asio::ip::make_address_v4("123.1.2.4") << std::endl;

	return 0;
}