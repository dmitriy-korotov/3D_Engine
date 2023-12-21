#include <engine/net/http/basic_http_message.hpp>

#include <cassert>



namespace engine::net::http
{
	auto toString(http_header _header) noexcept -> std::string
	{
		switch (_header)
		{
		case http_header::content_lenth:			return "Content-Length";
		case http_header::host:						return "Host";
		case http_header::content_type:				return "Content-Type";
		case http_header::connection:				return "Connection";
		case http_header::cookie:					return "Cookie";
		case http_header::encoding:					return "Accept-Encoding";
		case http_header::date:						return "Date";
		case http_header::server:					return "Server";
		case http_header::keep_alive:				return "Keep-Alive";
		case http_header::accept:					return "Accept";
		default:
			assert(false);
		}
		return {};
	}



	auto isValidHttpVersion(http_version _version) noexcept -> bool
	{
		if (_version.major > 3)
			return false;

		if (_version.minor > 9)
			return false;

		return true;
	}
}