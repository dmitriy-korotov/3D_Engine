#pragma once

#include <engine/net/net.hpp>

#include <engine/util/nocopyeble.hpp>

#include <engine/net/http/request.hpp>
#include <engine/net/http/response.hpp>
#include <engine/net/http/response_parser.hpp>

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/awaitable.hpp>
#include <asio/use_awaitable.hpp>



namespace engine::net::http
{
	using namespace asio::ip;

	class http_client
	{
	public:

		http_client() noexcept;

		template <http_body T>
		asio::awaitable<response<T>> sendRequest(const request<T>& _request, const tcp::endpoint& _host_address) noexcept;

		asio::io_context& getContext() noexcept;

	private:

		asio::io_context m_execution_cxt;

		tcp_socket_t m_socket;

	};





	template <http_body T>
	auto http_client::sendRequest(const request<T>& _request, const tcp::endpoint& _host_address) noexcept -> asio::awaitable<response<T>>
	{
		co_await m_socket.async_connect(_host_address, asio::use_awaitable);

		auto bytes_sended = co_await m_socket.async_send(asio::buffer(_request.build()), asio::use_awaitable);

		char buffer[1024] = {};

		auto bytes_recived = co_await m_socket.async_read_some(asio::buffer(buffer), asio::use_awaitable);

		response_parser<T> parser;
		parser.parse(std::string(buffer));

		auto response = std::move(parser).get();

		m_socket.close();

		co_return response;
	}
}