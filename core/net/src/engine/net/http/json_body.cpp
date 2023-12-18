#include <engine/net/http/json_body.hpp>



namespace engine::net::http
{
	json_body::json_body(std::string&& _data) noexcept
		: m_data(json_t::parse(_data))
	{ }



	auto json_body::success() const noexcept -> bool
	{
		return true;
	}



	auto json_body::get() const& noexcept -> const json_t&
	{
		return m_data;
	}



	auto json_body::get() && noexcept -> json_t&&
	{
		return std::move(m_data);
	}



	json_body::operator std::string() const noexcept
	{
		return m_data.dump();
	}
}