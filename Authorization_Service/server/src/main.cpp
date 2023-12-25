#include <iostream>

#include <engine/logging/log.hpp>

#include <engine/net/http/http_server.hpp>





using namespace engine::net::http;

int main(int _argc, const char** _argv)
{
	http_server server;

	server.setupWorkDirectory("C:\\Users\\User\\Documents\\projects\\FirstWebSite");

	server.registrateURLHandler("/user",
		[](const request<string_body>& _request) -> response<string_body>
		{
			response<string_body> response;
			response.setBody("<html><h1 style=\"color: red;\">User!</h1></html>");
			return response;
		});

	server.registrateURLHandler("/registration",
		[](const request<string_body>& _request) -> response<string_body>
		{
			response<string_body> response;
			response.setBody("<html><h1 style=\"color: red;\">Registration!</h1></html>");
			return response;
		});

	server.registrateURLHandler("/home",
		[](const request<string_body>& _request) -> response<string_body>
		{
			response<string_body> response;
			response.setBody("<html><h1 style=\"color: red;\">Home!</h1></html>");
			return response;
		});

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