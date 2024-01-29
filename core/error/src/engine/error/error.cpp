#include <engine/error/error.hpp>



namespace engine::error
{
	error::error(no_error_t _no_error) noexcept
			: m_has_error(false)
	{ }


	error::error(std::string _error_message, error_code _code = 0) noexcept
			: m_message(std::move(_error_message))
			, m_code(_code)
	{ }



	auto error::message() const& noexcept -> const std::string&
	{
		return m_message;
	}
	

	
	auto error::message() && noexcept -> std::string&&
	{
		return std::move(m_message);
	}
	
	
	auto error::code() const noexcept -> error_code
	{
		return m_code;
	}



	error::operator bool() const noexcept
	{
		return m_has_error;
	}
}