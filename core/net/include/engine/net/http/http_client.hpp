#pragma once

#include <engine/net/net.hpp>

#include <engine/util/nocopyeble.hpp>

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/awaitable.hpp>



namespace engine::net::http
{
	using namespace asio::ip;

	class http_client
	{
	public:

		http_client() noexcept;

		asio::awaitable<std::string> sendGetRequest(const std::string& _request, std::string_view _address, uint16_t _port = 80) noexcept;

		asio::io_context& getContext() noexcept;

	private:

		asio::io_context m_execution_cxt;

		tcp_socket_t m_socket;

	};
}