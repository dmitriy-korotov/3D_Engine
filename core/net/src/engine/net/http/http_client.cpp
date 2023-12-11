#include <engine/net/http/http_client.hpp>

#include <engine/logging/log.hpp>

#include <asio/use_awaitable.hpp>



namespace engine::net::http
{
	http_client::http_client() noexcept
			: m_socket(m_execution_cxt)
	{ }



	auto http_client::sendGetRequest(const std::string& _request, std::string_view _address, uint16_t _port) noexcept -> asio::awaitable<std::string>
	{
		auto endpoint = tcp::endpoint(address_v4::from_string(_address.data()), _port);
		co_await m_socket.async_connect(endpoint, asio::use_awaitable);
		
		auto bytes_sended = co_await m_socket.async_send(asio::buffer(_request), asio::use_awaitable);

		std::string buffer(1024, '\0');

		auto bytes_recived = co_await m_socket.async_read_some(asio::buffer(buffer), asio::use_awaitable);

		m_socket.close();

		co_return buffer;
	}



	auto http_client::getContext() noexcept -> asio::io_context&
	{
		return m_execution_cxt;
	}
}