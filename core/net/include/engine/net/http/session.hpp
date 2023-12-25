#pragma once

#include <engine/net/net.hpp>

#include <engine/util/nocopyeble.hpp>

#include <engine/net/http/handlers_context.hpp>

#include <asio/awaitable.hpp>

#include <memory>



namespace engine::net::http
{
	class session: public std::enable_shared_from_this<session>, private util::nocopyeble
	{
	public:

		using session_ptr_t = std::shared_ptr<session>;

		session(tcp_socket_t&& _socket, hcontext_sptr_t _handlers_context) noexcept;

		void start() noexcept;

	private:

		asio::awaitable<void> startSession(session_ptr_t _session) noexcept;

		response<string_body> handleRequest(const request<string_body>& _request) noexcept;

	private:

		enum { BUFFER_SIZE = 1024 };
		tcp_socket_t m_socket;
		hcontext_sptr_t m_handlers_context = nullptr;

	};
}