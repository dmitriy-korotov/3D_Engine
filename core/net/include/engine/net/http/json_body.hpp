#pragma once

#include <nlohmann/json.hpp>

#include <string>



namespace engine::net::http
{
	using json_t = nlohmann::json;

	class json_body
	{
	public:

		using body_t = json_t;

		json_body() = default;
		json_body(std::string&& _data) noexcept;
		json_body(json_t&& _data) noexcept;
		json_body(const json_t& _data) noexcept;
		json_body(const json_body&) = default;
		json_body(json_body&&) = default;
		json_body& operator=(const json_body&) = default;
		json_body& operator=(json_body&&) = default;

		bool success() const noexcept;

		const json_t& get() const& noexcept;
		json_t&& get() && noexcept;

		operator std::string() const noexcept;

	private:

		json_t m_data;

	};
}