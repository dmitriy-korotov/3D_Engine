#pragma once

#include <string>



namespace engine::error
{
	using error_code = std::int64_t;

	struct no_error_t {};

	class error
	{
	public:

		error(no_error_t _no_error) noexcept;
		explicit error(std::string _error_message, error_code _code = 0) noexcept;

		const std::string& message() const & noexcept;
		std::string&& message() && noexcept;
		error_code code() const noexcept;

		operator bool() const noexcept;

	private:

		bool m_has_error = true;
		std::string m_message;
		error_code m_code;

	};
}