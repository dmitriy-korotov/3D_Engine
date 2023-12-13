#include <engine/net/http/basic_http_message.hpp>

#include <cassert>



namespace engine::net::http
{
	std::string toString(http_header _header) noexcept
	{
		switch (_header)
		{
		case http_header::content_lenth:			return "Content-length";
		case http_header::host:						return "Host";
		case http_header::content_type:				return "Content-type";
		case http_header::keep_alive:				return "Keep-alive";
		case http_header::cookie:					return "Cookie";
		default:
			assert(false);
		}
		return {};
	}
}