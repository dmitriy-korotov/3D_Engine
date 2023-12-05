#include <engine/authorization/server.hpp>

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>

#include <iostream>



namespace authorization
{
	server::server(std::string_view _address, uint16_t _port)
		: m_acceptor(m_execution_cxt, { tcp::v4(), _port })
	{ }



	server::server() noexcept
			: server("127.0.0.1", 80)
	{ }



	auto server::start() -> void
	{
		asio::co_spawn(m_execution_cxt, listenConnections(), asio::detached);

		m_execution_cxt.run();
	}



	auto server::listenConnections() -> asio::awaitable<void>
	{
		for (;;)
		{
			auto socket = co_await m_acceptor.async_accept(asio::use_awaitable);
			std::cerr << socket.remote_endpoint() << std::endl;
		}
	}
}