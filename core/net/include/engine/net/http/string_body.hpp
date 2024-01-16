#pragma once

#include <string>



namespace engine::net::http
{
	class string_body
	{
	public:

		using body_t = std::string;

		string_body() = default;
		string_body(std::string&& _data) noexcept;
		string_body(const std::string& _data) noexcept;
		string_body(const string_body&) = default;
		string_body(string_body&&) = default;
		string_body& operator=(const string_body&) = default;
		string_body& operator=(string_body&&) = default;

		bool success() const noexcept;

		const std::string& get() const & noexcept;
		std::string&& get() && noexcept;

		operator std::string() const noexcept;

	private:

		std::string m_data;

	};
}