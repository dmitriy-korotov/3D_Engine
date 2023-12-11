#include <iostream>

#include <engine/logging/log.hpp>

#include <engine/net/http/http_server.hpp>



int main(int _argc, const char** _argv)
{
	engine::net::http::http_server server;

	try 
	{
		server.listen("127.0.0.1");
	}
	catch (const std::exception& _ex)
	{
		LOG_ERROR("[Server ERROR]: {0}", std::string(_ex.what()));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}