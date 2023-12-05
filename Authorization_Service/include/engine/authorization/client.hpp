#pragma once

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>



namespace engine::authorization
{
	using asio::ip::tcp;

	class client
	{
	public:

		client(std::string_view _address, uint16_t _port);

		bool connectTo(std::string_view _address, uint16_t _port);

	private:

		asio::io_context m_excution_cxt;

		tcp::socket m_socket;

	};
}