#include <iostream>

#include <engine/authorization/server.hpp>



int main(int _argc, const char** _argv)
{
	try
	{
		authorization::server server;
	}
	catch (const std::exception& _ex)
	{
		std::cerr << "=> ERROR: " << _ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}