#pragma once

#include <engine/util/nocopyeble.hpp>

#include <string>



namespace auth
{
namespace __detail
{
	class auth_db_settings : private engine::util::nocopyeble
	{
	public:

		static auth_db_settings& instance() noexcept;

		const std::string& getDataBaseName() const noexcept;
		const std::string& getDataBaseHostaddr() const noexcept;
		const std::string& getDataBaseUser() const noexcept;
		const std::string& getDataBaseUserPassword() const noexcept;

	private:

		auth_db_settings() = default;

		static std::string getDataBaseVariableFromEnvironment(std::string_view _variable_name) noexcept;

	private:

		mutable std::string m_db_name;
		mutable std::string m_db_hostaddr;
		mutable std::string m_db_user;
		mutable std::string m_db_user_password;

	};
}
	
	__detail::auth_db_settings& GetSettingAuthDB() noexcept;

}