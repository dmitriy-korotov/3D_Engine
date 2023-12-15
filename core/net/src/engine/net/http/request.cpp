#include <engine/net/http/request.hpp>

#include <cassert>



namespace engine::net::http
{
	constexpr std::string toString(request_method _method) noexcept
	{
		switch (_method)
		{
		case request_method::Get:				return "GET";
		case request_method::Post:				return "POST";
		case request_method::Delete:			return "DELETE";
		case request_method::Put:				return "PUT";
		case request_method::Trace:				return "TRACE";
		default:
			assert(false);
		}
		return "";
	}
}