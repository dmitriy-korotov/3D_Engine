#include <engine/net/http/http_client.hpp>

#include <asio/use_awaitable.hpp>



namespace engine::net::http
{
	http_client::http_client() noexcept
			: m_socket(m_execution_cxt)
	{ }



	auto http_client::sendGetRequest(std::string_view _address, uint16_t _port) noexcept -> asio::awaitable<std::string>
	{
		m_socket.open(tcp::v4());
		co_await m_socket.async_connect(tcp::endpoint(address_v4::from_string(_address.data()), _port), asio::use_awaitable);
		
		auto buffer = std::string("GET REQUEST");

		//auto bytes_sended = co_await m_socket.async_send(asio::buffer(buffer), asio::use_awaitable);

		//auto bytes_recived = co_await m_socket.async_read_some(asio::buffer(buffer), asio::use_awaitable);

		co_return buffer;
	}



	auto http_client::getContext() noexcept -> asio::io_context&
	{
		return m_execution_cxt;
	}
}