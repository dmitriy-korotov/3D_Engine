#include <iostream>

#include <engine/logging/log.hpp>

#include <auth/authorization_server.hpp>



int main(int _argc, const char** _argv)
{
	auth::authorization_server server;
	
	try 
	{
		server.startOn("127.0.0.1");
	}
	catch (const std::exception& _ex)
	{
		LOG_ERROR("[Server ERROR]: {0}", std::string(_ex.what()));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}