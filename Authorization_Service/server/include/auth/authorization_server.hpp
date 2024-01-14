#pragma once

#include <engine/net/http/http_server.hpp>



namespace auth
{
	using namespace engine::net::http;

	class authorization_server : protected http_server
	{
	public:

		authorization_server() noexcept;

		void startOn(std::string_view _address, uint16_t _port = 80);

	private:

		void registrateAPI() noexcept;

		response<string_body> /* API '/api/v1/users' */ createUserHandler(const request<string_body>& _request);

	};
}