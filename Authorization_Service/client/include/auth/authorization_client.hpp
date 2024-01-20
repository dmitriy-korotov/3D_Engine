#pragma once

#include <engine/net/net.hpp>

#include <engine/net/http/http_client.hpp>

#include <auth/user.hpp>



namespace auth
{
	using namespace engine::net::http;

	class authorization_client
	{
	public:

		authorization_client(asio::io_context& _context) noexcept;

		asio::awaitable<bool> registrateUser(const user& _user) const;
		asio::awaitable<bool> autorizateUser(const std::string& _user_login, const std::string& _password) const;

	private:

		http_client m_client;

	};
}