#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/net/http/basic_http_message.hpp>

#include <tuple>



namespace engine::net::http
{
	template <typename T, typename U>
	concept http_message = std::is_base_of_v<basic_http_message<U>, T> && std::is_default_constructible_v<T>;



	template <http_body T, http_message<T> U>
	class basic_http_message_parser: private util::nocopyeble
	{
	public:

		using message_t = U;

		basic_http_message_parser() = default;
		
		void parse(const std::string& _http_message);

		message_t&& get() && noexcept;
		const message_t& get() const & noexcept;

	protected:

		virtual void parseFirstLine(std::string_view _line) = 0;
		void parseVersion(std::string_view _version_string);

	private:

		using header_t = std::pair<std::string, std::string>;

		size_t parseHeaders(const std::string& _http_message, size_t _pos);
		std::tuple<header_t, int> parseHeader(const std::string& _http_message, size_t _pos) const noexcept;
		size_t parseBody(const std::string& _http_message, size_t _pos);

	protected:

		message_t m_message;

	};





	template <http_body T, http_message<T> U>
	auto basic_http_message_parser<T, U>::parse(const std::string& _http_message) -> void
	{
		auto first_line_end = _http_message.find_first_of("\r\n");
		if (first_line_end == std::string::npos)
			throw std::runtime_error("Invalid http message format: can't find '\\r\\n'");

		parseFirstLine(std::string_view(_http_message.begin(), _http_message.begin() + first_line_end));

		auto headers_end_pos = parseHeaders(_http_message, first_line_end + 2);
		
		auto parse_end_pos = parseBody(_http_message, headers_end_pos);
	}



	template <http_body T, http_message<T> U>
	auto basic_http_message_parser<T, U>::parseVersion(std::string_view _version_string) -> void
	{
		auto start = _version_string.find('/');
		if (start == std::string::npos)
			throw std::runtime_error("Invalid http version format: expected '/'");

		auto point_pos = _version_string.find('.', start);
		if (point_pos == std::string::npos)
			throw std::runtime_error("Invalid http version format: expected '.'");

		auto major = std::atoi(std::string_view(_version_string.begin() + start + 1,
												_version_string.begin() + point_pos).data());
		auto minor = std::atoi(std::string_view(_version_string.begin() + point_pos + 1,
												_version_string.end()).data());

		m_message.setHttpVersion(http_version{ .major = static_cast<uint8_t>(major),
											   .minor = static_cast<uint8_t>(minor) });
	}



	template <http_body T, http_message<T> U>
	auto basic_http_message_parser<T, U>::parseHeaders(const std::string& _http_message, size_t _pos) -> size_t
	{
		for (;;)
		{
			auto [header, line_size] = parseHeader(_http_message, _pos);
			auto& [key, value] = header;

			if (line_size == -1) // error line parsing
				throw std::runtime_error("Error request headers parsing");

			if (line_size == 0)
				break;

			m_message.emplaceHeader(std::move(key), std::move(value));

			_pos += line_size;
		}

		return _pos + 2;
	}



	template <http_body T, http_message<T> U>
	auto basic_http_message_parser<T, U>::parseHeader(const std::string& _http_message, size_t _pos) const noexcept -> std::tuple<header_t, int>
	{
		if (_pos + 1 >= _http_message.size())
			return { {}, -1 };

		if (_http_message[_pos] == '\r' && _http_message[_pos + 1] == '\n')
			return { {}, 0 };



		header_t header;

		size_t count = 0;
		for (;; _pos++, count++)
		{
			if (_pos == _http_message.size())
				return { {}, -1 };

			if (_http_message[_pos] == ':')
			{
				count++;
				break;
			}

			header.first.push_back(_http_message[_pos]);
		}

		while (_pos + 1 < _http_message.length() && std::isspace(_http_message[++_pos]))
			count++;

		for (;; _pos++, count++)
		{
			if (_pos + 1 >= _http_message.size())
				return { {}, -1 };

			if (_http_message[_pos] == '\r' && _http_message[_pos + 1] == '\n')
				break;

			header.second.push_back(_http_message[_pos]);
		}

		return { header, count + 2 };
	}



	template <http_body T, http_message<T> U>
	auto basic_http_message_parser<T, U>::parseBody(const std::string& _http_message, size_t _pos) -> size_t
	{
		auto all_message_size = _http_message.size();
		if (_http_message[all_message_size - 2] != '\r' || _http_message[all_message_size - 1] != '\n')
			throw std::runtime_error("Expected '\\r\\n' after body");

		std::string string_body = _http_message.substr(_pos, _http_message.size() - _pos - 2);
		auto size = string_body.size();
		auto body = T(std::move(string_body));
		m_message.setBody(std::move(body).get());
		return size;
	}



	template <http_body T, http_message<T> U>
	auto basic_http_message_parser<T, U>::get() && noexcept -> message_t&&
	{
		return std::move(m_message);
	}



	template <http_body T, http_message<T> U>
	auto basic_http_message_parser<T, U>::get() const& noexcept -> const message_t&
	{
		return m_message;
	}
}