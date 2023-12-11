#include <engine/net/http/session.hpp>

#include <engine/logging/log.hpp>

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/buffer.hpp>



namespace engine::net::http
{
	session::session(tcp_socket_t&& _socket) noexcept
			: m_socket(std::move(_socket))
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

		auto bytes_sended = co_await m_socket.async_write_some(asio::buffer(answer), asio::use_awaitable);
	}
}