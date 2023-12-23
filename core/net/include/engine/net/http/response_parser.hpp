#pragma once

#include <engine/net/http/basic_http_message_parser.hpp>
#include <engine/net/http/response.hpp>

#include <sstream>



namespace engine::net::http
{
	template <http_body T>
	class response_parser : public basic_http_message_parser<T, response<T>>
	{
	private:

		void parseFirstLine(std::string_view _line) override;

	};



	template <http_body T>
	auto response_parser<T>::parseFirstLine(std::string_view _line) -> void
	{
		std::istringstream line(_line.data());

		std::string version;
		line >> version;

		this->parseVersion(version);

		uint16_t status = 0;
		line >> status;
		this->m_message.setStatus(static_cast<response_status>(status));
	}
}