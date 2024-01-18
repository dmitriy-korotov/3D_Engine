#include <editor_app.hpp>

#include <engine/logging/log.hpp>

#include <engine/net/http/http_client.hpp>
#include <engine/net/http/string_body.hpp>

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>

#include <iostream>
#include <memory>



using namespace engine::net::http;



auto ConnectToServer(http_client& _client) -> asio::awaitable<void>
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

			co_await _client.connect(tcp::endpoint(asio::ip::address_v4::from_string("127.0.0.1"), 80));
			response<string_body> responce = co_await _client.sendRequest(request);

			LOG_INFO("[Http client INFO] Recived: {0}", responce.build());
		}
		catch (const std::exception& _ex)
		{
			LOG_INFO("[Http client INFO] Exception: {0}", std::string(_ex.what()));
		}
	}
	_client.disconnect();
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

	asio::io_context context;

	http_client client(context);

	try
	{
		asio::co_spawn(context, ConnectToServer(client), asio::detached);

		context.run();
	}
	catch (const std::exception& _ex)
	{
		LOG_ERROR("Catched exception: '{0}'", std::string(_ex.what()));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}