#include <engine/net/http/http_server.hpp>

#include <engine/logging/log.hpp>

#include <engine/net/util/ip.hpp>
#include <engine/util/conventions.hpp>

#include <engine/net/http/session.hpp>

#include <asio/io_context.hpp>
#include <asio/signal_set.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/awaitable.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/static_thread_pool.hpp>

#include <thread>
#include <sstream>



namespace engine::net::http
{
	size_t http_server::s_default_threads_count = std::thread::hardware_concurrency();





	class http_server::pimpl
	{
	public:

		pimpl(size_t _threads_count) noexcept;
		~pimpl() = default;

		void listen(std::string_view _address, uint16_t _port);

		void setupWorkDirectory(path _work_directory) noexcept;

		bool registrateURLHandler(const std::string& _url, request_method _method, url_handler_t _handler) noexcept;

		size_t threadsCount() const noexcept;

	private:

		void setupSignals() noexcept;
		void bindAcceptor(std::string_view _address, uint16_t _port);

		asio::awaitable<void> accept();

	private:

		asio::io_context m_execution_cxt;
		asio::signal_set m_signals;

		tcp_acceptor_t m_acceptor;

		hcontext_sptr_t m_handlers_context = nullptr;

		size_t m_threads_count = 0;
		asio::static_thread_pool m_thread_pool;

	};





	http_server::pimpl::pimpl(size_t _threads_count) noexcept
			: m_acceptor(m_execution_cxt)
			, m_signals(m_execution_cxt, SIGTERM, SIGINT)
			, m_handlers_context(std::make_shared<handlers_context>())
			, m_threads_count(_threads_count)
			, m_thread_pool(_threads_count)
	{ }



	auto http_server::pimpl::setupWorkDirectory(path _work_directory) noexcept -> void
	{
		m_handlers_context->work_directory = std::move(_work_directory);
	}



	auto http_server::pimpl::registrateURLHandler(const std::string& _url, request_method _method, url_handler_t _handler) noexcept -> bool
	{
		if (m_handlers_context->handlers.contains(_method))
			return m_handlers_context->handlers[_method].emplace(_url, std::move(_handler)).second;
		
		std::unordered_map<std::string, url_handler_t> handlers_storage = { {_url, std::move(_handler)} };
		return m_handlers_context->handlers.emplace(_method, std::move(handlers_storage)).second;
	}



	auto http_server::pimpl::listen(std::string_view _address, uint16_t _port) -> void
	{
		setupSignals();
		bindAcceptor(_address, _port);

		LOG_INFO("[Http server INFO] [Threads count '{0}'] Server is started on address '{1}'",
				 m_threads_count,
				 utility::toString(m_acceptor.local_endpoint()));
		
		asio::co_spawn(m_execution_cxt, accept(), asio::detached);

		for (size_t i = 0; i < threadsCount(); i++)
		{
			asio::post(m_thread_pool,
				[this]() -> void
				{
					m_execution_cxt.run();
				});
		}
		m_thread_pool.join();
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

			LOG_INFO("[Http server INFO] [Thread ID '{0}'] Accepted address '{1}'",
					 util::toString(std::this_thread::get_id()),
					 utility::toString(socket.remote_endpoint()));
			
			std::make_shared<session>(std::move(socket), m_handlers_context)->start();
		}
	}



	auto http_server::pimpl::threadsCount() const noexcept -> size_t
	{
		return m_threads_count;
	}








	http_server::http_server(size_t _amount_threads) noexcept
			: m_pimpl(std::make_unique<pimpl>(_amount_threads))
	{ }



	auto http_server::setupWorkDirectory(path _work_directory) noexcept -> void
	{
		impl()->setupWorkDirectory(std::move(_work_directory));
	}



	auto http_server::registrateURLHandler(const std::string& _url, request_method _method, url_handler_t _handler) noexcept -> bool
	{
		return impl()->registrateURLHandler(_url, _method, std::move(_handler));
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