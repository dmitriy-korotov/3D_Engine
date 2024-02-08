#include <iostream>

#include <engine/logging/log.hpp>

#include <auth/authorization_server.hpp>

#include <engine/util/system.hpp>

int main(int _argc, const char** _argv)
{
	auth::authorization_server server;

	try 
	{
		if (!server.startOn("127.0.0.1"))
			LOG_CRITICAL("[Server CRITICAL] Can't start server");
	}
	catch (const std::exception& _ex)
	{
		LOG_ERROR("[Server CRITICAL] Exception: '{0}'", std::string(_ex.what()));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}