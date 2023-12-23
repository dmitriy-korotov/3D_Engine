#include <engine/net/http/request.hpp>

#include <format>
#include <cassert>



namespace engine::net::http
{
	static std::unordered_map<std::string, request_method> s_mappping_from_string =
	{
		{ "GET", request_method::Get },
		{ "POST", request_method::Post },
		{ "DELETE", request_method::Delete },
		{ "PUT", request_method::Put },
		{ "TRACE", request_method::Trace },
	};



	auto toString(request_method _method) noexcept -> std::string
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



	auto fromString(const std::string& _method_str) -> request_method
	{
		auto result = s_mappping_from_string.find(_method_str);
		if (result == s_mappping_from_string.end())
			throw std::runtime_error(std::format("Uncknowed request method '{0}'", _method_str));
		return result->second;
	}
}