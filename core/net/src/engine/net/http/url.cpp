#include <engine/net/http/url.hpp>

#include <sstream>



namespace engine::net::http
{
	auto toString(const url::query_t& _query_string) noexcept -> std::string
	{
		std::stringstream buffer;
		for (const auto& [key, value] : _query_string)
			buffer << key << "=" << value << '&';

		auto result = buffer.str();

		if (!_query_string.empty())
			result.pop_back();

		return result;
	}





	auto url::from_string(const std::string& _url_string) -> url
	{
		std::string absolute_path;
		url::query_t query;

		size_t position = 0;
		bool is_query_pairs_exists = false;
		for (; position < _url_string.size(); position++)
		{
			if (_url_string[position] == '?')
			{
				is_query_pairs_exists = true;
				position++;
				break;
			}
			absolute_path.push_back(_url_string[position]);
		}

		while (is_query_pairs_exists)
		{
			std::string key;
			std::string value;

			while (position < _url_string.size() && _url_string[position] != '=')
				key.push_back(_url_string[position++]);

			position++;

			while (position < _url_string.size() && _url_string[position] != '&')
				value.push_back(_url_string[position++]);

			position++;

			query.emplace(std::move(key), std::move(value));

			if (position >= _url_string.size())
				break;
		}

		return url(std::move(absolute_path), std::move(query));
	}





	url::url(url_path_t _url) noexcept
			: m_absolute_path(std::move(_url))
	{ }



	url::url(url_path_t _url, query_t _query_string) noexcept
			: m_absolute_path(std::move(_url))
			, m_query_string(std::move(_query_string))
	{ }



	auto url::setQueryString(query_t _query_string) noexcept -> void
	{
		m_query_string = std::move(_query_string);
	}



	auto url::getQueryString() const& -> const query_t&
	{
		return m_query_string.value();
	}



	auto url::getQueryString() && -> query_t&&
	{
		return std::move(m_query_string.value());
	}



	auto url::getAbsolutePath() const noexcept -> std::string
	{
		return m_absolute_path.generic_string();
	}



	url::operator std::string() const noexcept
	{
		std::stringstream buffer;
		buffer << m_absolute_path;
		
		if (m_query_string.has_value())
			buffer << '?' << toString(m_query_string.value());
		
		return buffer.str();
	}
}