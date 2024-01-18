#pragma once

#include <engine/net/net.hpp>

#include <engine/util/nocopyeble.hpp>

#include <engine/net/http/request.hpp>
#include <engine/net/http/response.hpp>
#include <engine/net/http/response_parser.hpp>
#include <engine/net/http/string_body.hpp>

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/awaitable.hpp>
#include <asio/use_awaitable.hpp>



namespace engine::net::http
{
	using namespace asio::ip;

	using request_t = request<string_body>;
	using response_t = response<string_body>;

	class http_client
	{
	public:

		http_client(asio::io_context& _context) noexcept;

		asio::awaitable<void> connect(const tcp::endpoint& _host_address) noexcept;
		void disconnect() noexcept;

		asio::awaitable<response_t> sendRequest(const request_t& _request) noexcept;

	private:

		tcp_socket_t m_socket;

	};
}