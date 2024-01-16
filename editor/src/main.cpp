#include <editor_app.hpp>

#include <engine/logging/log.hpp>

#include <engine/net/http/http_client.hpp>
#include <engine/net/http/string_body.hpp>

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>

#include <iostream>
#include <memory>



using namespace engine::net::http;



auto sendRequest(std::shared_ptr<http_client> client) -> asio::awaitable<void>
{
	for (;;)
	{
		try
		{
			std::string message;
			std::cout << "Input message:\t";
			std::cin >> message;

			if (message == "end")
				break;

			request<string_body> request;
			request.setURL(url::fromString("/api/v1/users"));
			request.setMethod(request_method::Post);
			request.setBody(message);

			response<string_body> responce = co_await client->sendRequest(request, tcp::endpoint(asio::ip::address_v4::from_string("127.0.0.1"), 80));

			LOG_INFO("[Http client INFO] Recived: {0}", responce.build());
		}
		catch (const std::exception& _ex)
		{
			LOG_INFO("[Http client INFO] Exception: {0}", std::string(_ex.what()));
		}
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