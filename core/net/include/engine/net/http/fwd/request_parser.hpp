#pragma once

#include <engine/net/http/fwd/basic_http_message.hpp>



namespace engine::net::http
{
	template <http_body T>
	class request_parser;
}