#pragma once

#include <engine/net/net.hpp>

#include <engine/error/error.hpp>

#include <engine/net/http/http_client.hpp>

#include <auth/user.hpp>



namespace auth
{
	using namespace engine::net::http;
	using namespace engine::error;

	class authorization_client
	{
	public:

		explicit authorization_client(asio::io_context& _context) noexcept;
		authorization_client(asio::io_context& _context, const host& _host) noexcept;

		void connect(const host& _host) noexcept;
		void disconnect() noexcept;

		asio::awaitable<error> registrateUser(const user& _user) const;
		asio::awaitable<error> autorizateUser(const std::string& _user_login, const std::string& _password) const;

	private:

		http_client m_client;

	};
}