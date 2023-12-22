#pragma once

#include <unordered_map>
#include <optional>
#include <filesystem>
#include <exception>



namespace engine::net::http
{
	class url
	{
	public:

		using url_path_t = std::filesystem::path;
		using query_t = std::unordered_map<std::string, std::string>;

		static url from_string(const std::string& _url_string);

		url(url_path_t _url) noexcept;
		url(url_path_t _url, query_t _query_string) noexcept;

		void setQueryString(query_t _query_string) noexcept;

		const query_t& getQueryString() const &;
		query_t&& getQueryString() &&;

		std::string getAbsolutePath() const noexcept;

		operator std::string() const noexcept;

	private:

		url_path_t m_absolute_path;
		std::optional<query_t> m_query_string;

	};
}