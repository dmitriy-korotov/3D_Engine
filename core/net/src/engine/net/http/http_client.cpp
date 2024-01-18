#include <engine/net/http/http_client.hpp>

#include <engine/logging/log.hpp>



namespace engine::net::http
{
	http_client::http_client(asio::io_context& _context) noexcept
			: m_socket(_context)
	{ }
	


	auto http_client::connect(const tcp::endpoint& _host_address) noexcept-> asio::awaitable<void>
	{
		if (m_socket.is_open())
			m_socket.close();
		co_await m_socket.async_connect(_host_address, asio::use_awaitable);
	}



	auto http_client::disconnect() noexcept -> void
	{
		m_socket.close();
	}



	auto http_client::sendRequest(const request_t& _request) noexcept -> asio::awaitable<response_t>
	{
		if (!m_socket.is_open())
			throw std::runtime_error("Unconnected client, please connect to host");

		auto bytes_sended = co_await m_socket.async_send(asio::buffer(_request.build()), asio::use_awaitable);

		char buffer[1024] = {};
		auto bytes_recived = co_await m_socket.async_read_some(asio::buffer(buffer), asio::use_awaitable);

		response_parser<string_body> parser;
		parser.parse(std::string(buffer));

		auto response = std::move(parser).get();

		co_return response;
	}
}