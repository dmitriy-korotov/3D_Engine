#include <engine/net/http/http_server.hpp>

#include <engine/logging/log.hpp>

#include <engine/net/http/session.hpp>

#include <asio/io_context.hpp>
#include <asio/signal_set.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/awaitable.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>

#include <sstream>



namespace engine::net::http
{
	class http_server::pimpl
	{
	public:

		pimpl() noexcept;
		~pimpl() = default;

		void listen(std::string_view _address, uint16_t _port);

	private:

		void setupSignals() noexcept;
		void bindAcceptor(std::string_view _address, uint16_t _port);

		asio::awaitable<void> accept();

	private:

		asio::io_context m_execution_cxt;
		asio::signal_set m_signals;

		tcp_acceptor_t m_acceptor;

	};





	http_server::pimpl::pimpl() noexcept
			: m_acceptor(m_execution_cxt)
			, m_signals(m_execution_cxt, SIGTERM, SIGINT)
	{ }



	auto http_server::pimpl::listen(std::string_view _address, uint16_t _port) -> void
	{
		setupSignals();
		bindAcceptor(_address, _port);

		std::stringstream acceptor_address;
		acceptor_address << m_acceptor.local_endpoint();
		LOG_INFO("[Http server INFO] Server is started on address '{0}'", acceptor_address.str());
		
		asio::co_spawn(m_execution_cxt, accept(), asio::detached);

		m_execution_cxt.run();
	}



	auto http_server::pimpl::setupSignals() noexcept -> void
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



	auto http_server::pimpl::bindAcceptor(std::string_view _address, uint16_t _port) -> void
	{
		auto endpoint = tcp::endpoint(address_v4::from_string(_address.data()), _port);

		m_acceptor.open(endpoint.protocol());
		m_acceptor.set_option(tcp::acceptor::reuse_address(true));
		m_acceptor.bind(endpoint);
		m_acceptor.listen();
	}



	auto http_server::pimpl::accept() -> asio::awaitable<void>
	{
		for (;;)
		{
			auto socket = co_await m_acceptor.async_accept(asio::use_awaitable);
			std::stringstream buffer;
			buffer << socket.remote_endpoint();
			LOG_INFO("[Http server INFO] Accepted: {0}", buffer.str());

			std::make_shared<session>(std::move(socket))->start();
		}
	}








	http_server::http_server() noexcept
			: m_pimpl(std::make_unique<pimpl>())
	{ }



	auto http_server::listen(std::string_view _address, uint16_t _port) -> void
	{
		impl()->listen(_address, _port);
	}



	auto http_server::impl() noexcept -> upimpl_t&
	{
		return m_pimpl;
	}



	auto http_server::impl() const noexcept -> const upimpl_t&
	{
		return m_pimpl;
	}



	http_server::~http_server()
	{ }
}