#include <engine/net/http/http_client.hpp>

#include <engine/logging/log.hpp>



namespace engine::net::http
{
	http_client::http_client(asio::io_context& _context) noexcept
			: m_socket(_context)
	{ }
	


	auto http_client::connect(const host& _host) noexcept -> void
	{
		m_host = tcp::endpoint(address::from_string(_host.getAddress()), _host.getPort());
		m_is_connected = true;
	}



	auto http_client::disconnect() noexcept -> void
	{
		m_host = tcp::endpoint();
		m_is_connected = false;
	}



	auto http_client::isConnected() const noexcept -> bool
	{
		return m_is_connected;
	}



	auto http_client::getHost() const -> host
	{
		if (!isConnected())
			throw std::runtime_error("Client in not connected to host");

		return host(m_host.address().to_string(), m_host.port());
	}



	auto http_client::request(const request_t& _request) const -> asio::awaitable<response_t>
	{
		if (!m_is_connected)
			throw std::runtime_error("Client is unconnected, please connect to host");

		co_await m_socket.async_connect(m_host, asio::use_awaitable);

		auto bytes_sended = co_await m_socket.async_send(asio::buffer(_request.build()), asio::use_awaitable);

		char buffer[1024] = {};
		auto bytes_recived = co_await m_socket.async_read_some(asio::buffer(buffer), asio::use_awaitable);

		m_socket.close();

		response_parser<string_body> parser;
		parser.parse(std::string(buffer));

		auto response = std::move(parser).get();

		co_return response;
	}



	auto http_client::GET(url _url, const request_t::headers_t& _headers) const -> asio::awaitable<response_t>
	{
		request_t request;
		request.setMethod(request_method::Get);
		request.setURL(std::move(_url));
		request.emplaceHeaders(_headers);
		auto response = co_await this->request(request);
		co_return response;
	}



	auto http_client::POST(url _url, std::string _data, const request_t::headers_t& _headers) const ->asio::awaitable<response_t>
	{
		request_t request;
		request.setMethod(request_method::Post);
		request.setURL(std::move(_url));
		request.emplaceHeaders(_headers);
		request.setBody(std::move(_data));
		auto response = co_await this->request(request);
		co_return response;
	}



	auto http_client::PUT(url _url, std::string _data, const request_t::headers_t& _headers) const -> asio::awaitable<response_t>
	{
		request_t request;
		request.setMethod(request_method::Put);
		request.setURL(std::move(_url));
		request.emplaceHeaders(_headers);
		request.setBody(std::move(_data));
		auto response = co_await this->request(request);
		co_return response;
	}
}