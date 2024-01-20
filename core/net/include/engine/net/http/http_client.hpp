#pragma once

#include <engine/net/net.hpp>

#include <engine/util/nocopyeble.hpp>

#include <engine/net/http/request.hpp>
#include <engine/net/http/response.hpp>
#include <engine/net/http/response_parser.hpp>
#include <engine/net/http/string_body.hpp>
#include <engine/net/http/host.hpp>

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/awaitable.hpp>
#include <asio/use_awaitable.hpp>



namespace engine::net::http
{
	using namespace asio::ip;

	using request_t = request<string_body>;
	using response_t = response<string_body>;

	class http_client
	{
	public:

		http_client(asio::io_context& _context) noexcept;

		void connect(const host& _host) noexcept;
		void disconnect() noexcept;

		bool isConnected() const noexcept;

		asio::awaitable<response_t> request(const request_t& _request);
		asio::awaitable<response_t> GET(url _url, const request_t::headers_t& _headers = {});
		asio::awaitable<response_t> POST(url _url, std::string _data, const request_t::headers_t& _headers = {});
		asio::awaitable<response_t> PUT(url _url, std::string _data, const request_t::headers_t& _headers = {});

	private:

		bool m_is_connected = false;
		tcp::endpoint m_host;
		tcp_socket_t m_socket;

	};
}