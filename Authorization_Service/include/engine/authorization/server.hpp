#pragma once

#include <engine/util/nocopyeble.hpp>

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>

#include <asio/awaitable.hpp>



namespace authorization
{
	using namespace asio::ip;

	class server: private engine::util::nocopyeble
	{
	public:

		server() noexcept;
		server(std::string_view _address, uint16_t _port);

		void start();

	private:

		asio::awaitable<void> listenConnections();

	private:

		asio::io_context m_execution_cxt;

		tcp::acceptor m_acceptor;

	};
}