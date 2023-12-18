#include <engine/net/http/string_body.hpp>



namespace engine::net::http
{
	string_body::string_body(std::string&& _data) noexcept
			: m_data(std::move(_data))
	{ }



	auto string_body::success() const noexcept -> bool
	{
		return true;
	}



	auto string_body::get() const & noexcept -> const std::string&
	{
		return m_data;
	}



	auto string_body::get() && noexcept -> std::string&&
	{
		return std::move(m_data);
	}



	string_body::operator std::string() const noexcept
	{
		return m_data;
	}
}