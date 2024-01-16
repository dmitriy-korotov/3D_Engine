#include <auth/authorization_server.hpp>



namespace auth
{
	authorization_server::authorization_server() noexcept
	{ 
		registrateAPI();
	}



	auto authorization_server::startOn(std::string_view _address, uint16_t _port) -> void
	{
		listen(_address, _port);
	}



	auto authorization_server::registrateAPI() noexcept -> void
	{
		registrateURLHandler("/api/v1/users", engine::net::http::request_method::Post,
			[this](const request_t& _request) -> response_t
			{
				return createUserHandler(_request);
			});
	}



	response_t authorization_server::createUserHandler(const request_t& _request)
	{
		response<string_body> response;
		response.setBody("<html><h1>New user created!</h1></html>");
		return response;
	}
}