#pragma once

#include <engine/net/http/fwd/basic_http_message.hpp>



namespace engine::net::http
{
	template <typename message_type, http_body T>
	class basic_http_message_parser;
}