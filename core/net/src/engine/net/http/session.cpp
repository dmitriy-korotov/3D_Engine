#include <engine/net/http/session.hpp>

#include <engine/logging/log.hpp>

#include <engine/net/http/response.hpp>

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/buffer.hpp>



namespace engine::net::http
{
	session::session(tcp_socket_t&& _socket, hcontext_sptr_t _handlers_context) noexcept
			: m_socket(std::move(_socket))
			, m_handlers_context(std::move(_handlers_context))
	{ }



	auto session::start() noexcept -> void
	{
		asio::co_spawn(m_socket.get_executor(), startSession(shared_from_this()), asio::detached);
	}



	auto session::startSession(session_ptr_t _session) noexcept -> asio::awaitable<void>
	{
		char buffer[BUFFER_SIZE] = {};

		auto bytes_readed = co_await m_socket.async_read_some(asio::buffer(buffer), asio::use_awaitable);
		if (bytes_readed == 0)
			LOG_WARN("[Http session WARN] recived zero bytes");

		auto answer = std::string(buffer);

		std::stringstream address;
		address << m_socket.remote_endpoint();

		LOG_INFO("[Http session INFO] {0}: {1}", address.str(), answer);


		response<string_body> response;
		response.emplaceHeader(http_header::host, "Engine");
		response.setBody("<html><h1 style=\"color: green;\">Hello, world!</h1></html>");


		auto bytes_sended = co_await m_socket.async_write_some(asio::buffer(response.build()), asio::use_awaitable);
	}
}