#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/net/http/fwd/basic_http_message.hpp>

#include <optional>
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
		
		bool parse(const std::string& _http_message) noexcept;

		message_t&& get() && noexcept;
		const message_t& get() const & noexcept;

	protected:

		virtual bool parseFirstLine(std::string_view _line) const = 0;

	private:

		using header_t = std::pair<std::string, std::string>;

		std::optional<size_t> parseHeaders(const std::string& _http_message, size_t _pos) noexcept;
		std::tuple<header_t, int> parseHeader(const std::string& _http_message, size_t _pos) const noexcept;
		std::optional<size_t> parseBody(const std::string& _http_message, size_t _pos) noexcept;

	protected:

		message_t m_message;

	};





	template <http_body T, http_message<T> U>
	auto basic_http_message_parser<T, U>::parse(const std::string& _http_message) noexcept -> bool
	{
		auto first_line_end = _http_message.find_first_of("\r\n");
		if (first_line_end == std::string::npos)
			return false;

		if (!parseFirstLine(std::string_view(_http_message.begin(), _http_message.begin() + first_line_end)))
			return false;

		auto headers_end_pos = parseHeaders(_http_message, first_line_end + 2);
		if (!headers_end_pos.has_value())
			return false;

		auto parse_end_pos = parseBody(_http_message, headers_end_pos.value());
		if (!parse_end_pos.has_value())
			return false;

		return true;
	}



	template <http_body T, http_message<T> U>
	auto basic_http_message_parser<T, U>::parseHeaders(const std::string& _http_message, size_t _pos) noexcept -> std::optional<size_t>
	{
		for (;;)
		{
			auto [key, value, line_size] = parseHeader(_http_message, _pos);

			if (line_size == -1) // error line parsing
				return std::nullopt;

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
				return false;

			if (_http_message[_pos] == ':')
				break;

			header.first.push_back(_http_message[_pos]);
		}

		while (_pos + 1 < _http_message.length() && std::isspace(++_pos))
		{
			count++;
		}

		for (;; _pos++, count++)
		{
			if (_pos + 1 >= _http_message.size())
				return false;

			if (_http_message[_pos] == '\r' && _http_message[_pos + 1] == '\n')
				break;

			header.first.push_back(_http_message[_pos]);
		}

		return { header, count + 2 };
	}



	template <http_body T, http_message<T> U>
	auto basic_http_message_parser<T, U>::parseBody(const std::string& _http_message, size_t _pos) noexcept -> std::optional<size_t>
	{
		std::string string_body = _http_message.substr(_pos, _http_message.size() - _pos);
		T::body_t body;
		if (!body.parse(std::move(string_body)))
			return std::nullopt;

		m_message.setBody(std::move(body));

		return string_body.size();
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