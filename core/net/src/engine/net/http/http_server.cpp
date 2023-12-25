#include <engine/net/http/http_server.hpp>

#include <engine/logging/log.hpp>

#include <engine/net/util/ip.hpp>

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

		void setupWorkDirectory(path _work_directory) noexcept;

		bool registrateURLHandler(const std::string& _url, url_handler_t _handler) noexcept;

	private:

		void setupSignals() noexcept;
		void bindAcceptor(std::string_view _address, uint16_t _port);

		asio::awaitable<void> accept();

	private:

		asio::io_context m_execution_cxt;
		asio::signal_set m_signals;

		tcp_acceptor_t m_acceptor;

		hcontext_sptr_t m_handlers_context = nullptr;

	};





	http_server::pimpl::pimpl() noexcept
			: m_acceptor(m_execution_cxt)
			, m_signals(m_execution_cxt, SIGTERM, SIGINT)
			, m_handlers_context(std::make_shared<handlers_context>())
	{ }



	auto http_server::pimpl::setupWorkDirectory(path _work_directory) noexcept -> void
	{
		m_handlers_context->work_directory = std::move(_work_directory);
	}



	auto http_server::pimpl::registrateURLHandler(const std::string& _url, url_handler_t _handler) noexcept -> bool
	{
		return m_handlers_context->handlers.emplace(_url, std::move(_handler)).second;
	}



	auto http_server::pimpl::listen(std::string_view _address, uint16_t _port) -> void
	{
		setupSignals();
		bindAcceptor(_address, _port);

		LOG_INFO("[Http server INFO] Server is started on address '{0}'", utility::toString(m_acceptor.local_endpoint()));
		
		asio::co_spawn(m_execution_cxt, accept(), asio::detached);

		m_execution_cxt.run();
	}



	auto http_server::pimpl::setupSignals() noexcept -> void
	{
		m_signals.async_wait(
			[this](asio::error_code _error, int _signal) -> void
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

			LOG_INFO("[Http server INFO] Accepted address '{0}'", utility::toString(socket.remote_endpoint()));
			
			std::make_shared<session>(std::move(socket), m_handlers_context)->start();
		}
	}








	http_server::http_server() noexcept
			: m_pimpl(std::make_unique<pimpl>())
	{ }



	auto http_server::setupWorkDirectory(path _work_directory) noexcept -> void
	{
		impl()->setupWorkDirectory(std::move(_work_directory));
	}



	auto http_server::registrateURLHandler(const std::string& _url, url_handler_t _handler) noexcept -> bool
	{
		return impl()->registrateURLHandler(_url, std::move(_handler));
	}



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