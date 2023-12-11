#include <editor_app.hpp>

#include <engine/net/http/http_client.hpp>

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>

#include <iostream>




auto sendRequest(engine::net::http::http_client& client) -> asio::awaitable<void>
{
	auto responce = co_await client.sendGetRequest("127.0.0.1", 80);
}




int main(int _argc, char** _argv)
{
	/*auto& application = editor::Editor::instance();

	application.setConfig("C:\\Users\\User\\MyProjects\\3D_Engine\\core\\res\\config\\config.json");
	
	if (application.start().has_value())
	{
		std::cerr << "ERROR: Can't start application" << std::endl;
		return EXIT_FAILURE;
	}*/

	engine::net::http::http_client client;

	asio::co_spawn(client.getContext(), sendRequest(client), asio::detached);

	client.getContext().run();

	return EXIT_SUCCESS;
}