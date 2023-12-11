#pragma once

#include <engine/net/net.hpp>

#include <engine/util/nocopyeble.hpp>

#include <asio/io_context.hpp>
#include <asio/signal_set.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/awaitable.hpp>



namespace engine::net::http
{
	using namespace asio::ip;

	class http_server: private util::nocopyeble
	{
	public:

		http_server() noexcept;
		http_server(http_server&&) = default;
		http_server& operator=(http_server&&) = default;

		void listen(std::string_view _address, uint16_t _port = 80);

	private:

		asio::awaitable<void> __listen();

		void setupSignals() noexcept;
		void bindAcceptor(std::string_view _address, uint16_t _port);

	private:

		asio::io_context m_execution_cxt;
		asio::signal_set m_signals;

		tcp_acceptor_t m_acceptor;
		
	};
}