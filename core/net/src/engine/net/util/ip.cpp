#include <engine/net/util/ip.hpp>

#include <sstream>



namespace engine::net::utility
{
	auto toString(asio::ip::tcp::endpoint _endpoint) noexcept -> std::string
	{
		std::ostringstream out;
		out << _endpoint;
		return out.str();
	}
}