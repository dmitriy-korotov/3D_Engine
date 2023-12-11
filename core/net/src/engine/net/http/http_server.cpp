#include <engine/net/http/http_server.hpp>

#include <engine/logging/log.hpp>

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>

#include <sstream>



namespace engine::net::http
{
	http_server::http_server() noexcept
			: m_acceptor(m_execution_cxt)
			, m_signals(m_execution_cxt, SIGTERM, SIGINT)
	{ }



	auto http_server::listen(std::string_view _address, uint16_t _port) -> void
	{
		LOG_INFO("[Http server INFO] Server is started.");

		setupSignals();
		bindAcceptor(_address, _port);

		asio::co_spawn(m_execution_cxt, __listen(), asio::detached);

		m_execution_cxt.run();
	}



	auto http_server::__listen() -> asio::awaitable<void>
	{
		for (;;)
		{
			auto socket = co_await m_acceptor.async_accept(asio::use_awaitable);
			std::stringstream buffer;
			buffer << socket.remote_endpoint();
			LOG_INFO("[Http server INFO] Accepted: {0}", buffer.str());
		}
	}



	auto http_server::setupSignals() noexcept -> void
	{
		m_signals.async_wait(
			[this]([[maybe_unused]] asio::error_code _error, [[maybe_unused]] int _signal) -> void
			{
				if (_error)
					LOG_ERROR("[Http server ERROR] Error code '{0}', message: {1}", _error.value(), _error.message());

				if (_signal == SIGINT)
				{
					LOG_INFO("[Http server INFO] Server is closed.");
					m_execution_cxt.stop();
				}
			});
	}



	auto http_server::bindAcceptor(std::string_view _address, uint16_t _port) -> void
	{
		auto endpoint = tcp::endpoint(address_v4::from_string(_address.data()), _port);

		m_acceptor.open(endpoint.protocol());
		m_acceptor.set_option(tcp::acceptor::reuse_address(true));
		m_acceptor.bind(endpoint);
		m_acceptor.listen();
	}
}