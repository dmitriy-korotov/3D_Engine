#include <engine/net/http/basic_http_message.hpp>

#include <cassert>



namespace engine::net::http
{
	std::string toString(http_header _header) noexcept
	{
		switch (_header)
		{
		case http_header::content_lenth:			return "Content-Length";
		case http_header::host:						return "Host";
		case http_header::content_type:				return "Content-Type";
		case http_header::connection:				return "Connection";
		case http_header::cookie:					return "Cookie";
		case http_header::encoding:					return "Accept-Encoding";
		case http_header::date:						return "Cookie";
		default:
			assert(false);
		}
		return {};
	}



	bool isValidHttpVersion(http_version _version) noexcept
	{
		if (_version.major > 3)
			return false;

		if (_version.minor > 9)
			return false;

		return true;
	}
}