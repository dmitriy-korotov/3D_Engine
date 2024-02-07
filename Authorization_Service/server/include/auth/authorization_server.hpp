#pragma once

#include <engine/net/http/http_server.hpp>



namespace auth
{
	using namespace engine::net;

	class authorization_server : protected http::http_server
	{
	public:

		authorization_server() noexcept;

		void startOn(std::string_view _address, uint16_t _port = 80);

	private:

		void registrateAPI() noexcept;

		// API - POST - '/api/v1/users' 
		http::response_t createUserHandler(http::request_t& _request);

	};
}