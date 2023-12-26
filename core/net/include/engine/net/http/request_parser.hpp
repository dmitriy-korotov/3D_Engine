#pragma once

#include <engine/net/http/basic_http_message_parser.hpp>
#include <engine/net/http/request.hpp>
#include <engine/net/http/url_decoder.hpp>
#include <engine/net/http/url.hpp>

#include <sstream>



namespace engine::net::http
{
	template <http_body T>
	class request_parser : public basic_http_message_parser<T, request<T>>
	{
	private:

		void parseFirstLine(std::string_view _line) override;

	};



	template <http_body T>
	auto request_parser<T>::parseFirstLine(std::string_view _line) -> void
	{
		std::istringstream line(_line.data());

		std::string method;
		line >> method;
		this->m_message.setMethod(fromString(method));

		std::string url;
		line >> url;
		if (url.empty())
			throw std::runtime_error("Empty url in request");

		this->m_message.setURL(url::fromString(url_decoder::decode(url)));

		std::string version;
		line >> version;

		this->parseVersion(version);
	}
}