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
		registrateURLHandler("/api/v1/users",
			[this](const request<string_body>& _request) -> response<string_body>
			{
				return createUserHandler(_request);
			});
	}



	response<string_body> authorization_server::createUserHandler(const request<string_body>& _request)
	{
		response<string_body> response;
		response.setBody("<html><h1>New user created!</h1></html>");
		return response;
	}
}