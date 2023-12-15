#include <engine/net/http/response.hpp>

#include <cassert>



namespace engine::net::http
{
	constexpr std::string toString(response_status _status) noexcept
	{
		switch (_status)
		{
		case response_status::ok:				return "OK";
		case response_status::not_found:		return "Not found";
		case response_status::forbidden:		return "Forbidden";
		case response_status::badgetway:		return "Bad getway";
		default:
			assert(false);
		}
		return "";
	}
}