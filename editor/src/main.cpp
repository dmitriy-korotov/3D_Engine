#include <editor_app.hpp>

#include <engine/logging/log.hpp>

#include <engine/net/http/http_client.hpp>

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>

#include <iostream>
#include <memory>




auto sendRequest(std::shared_ptr<engine::net::http::http_client> client) -> asio::awaitable<void>
{
	for (;;)
	{
		std::string message;
		std::cout << "Input message:\t";
		std::cin >> message;

		if (message == "end")
			break;

		auto responce = co_await client->sendGetRequest(message, "127.0.0.1", 80);

		LOG_INFO("[Http client INFO] Recived: {0}", responce);
	}
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

	auto client = std::make_shared<engine::net::http::http_client>();

	asio::co_spawn(client->getContext(), sendRequest(client), asio::detached);

	client->getContext().run();

	return EXIT_SUCCESS;
}