#pragma once

#include <engine/net/net.hpp>

#include <asio/ip/tcp.hpp>



namespace engine::net::utility
{
	std::string toString(asio::ip::tcp::endpoint _endpoint) noexcept;
}