#include <auth/db/auth_db_settings.hpp>

#include <engine/logging/log.hpp>

#include <engine/util/system.hpp>



namespace auth
{
namespace __detail
{
	auto auth_db_settings::instance() noexcept -> auth_db_settings&
	{
		static auth_db_settings instance;
		return instance;
	}



	auto auth_db_settings::getDataBaseName() const noexcept -> const std::string&
	{
		if (m_db_name.empty())
			m_db_name = getDataBaseVariableFromEnvironment("AUTH_DB_NAME");
		return m_db_name;
	}



	auto auth_db_settings::getDataBaseHostaddr() const noexcept -> const std::string&
	{
		if (m_db_hostaddr.empty())
			m_db_hostaddr = getDataBaseVariableFromEnvironment("AUTH_DB_HOSTADDR");
		return m_db_hostaddr;
	}



	auto auth_db_settings::getDataBaseUser() const noexcept -> const std::string&
	{
		if (m_db_user.empty())
			m_db_user = getDataBaseVariableFromEnvironment("AUTH_DB_USER");
		return m_db_user;
	}



	auto auth_db_settings::getDataBaseUserPassword() const noexcept -> const std::string&
	{
		if (m_db_user_password.empty())
			m_db_user_password = getDataBaseVariableFromEnvironment("AUTH_DB_USER_PASSWORD");
		return m_db_user_password;
	}



	auto auth_db_settings::getDataBaseVariableFromEnvironment(std::string_view _variable_name) noexcept -> std::string try
	{
		return engine::util::GetEnvVariable(_variable_name);
	}
	catch (const std::exception& _ex)
	{
		LOG_ERROR("[Authorization data base settings ERROR] Exception: '{0}'", std::string(_ex.what()));
		return {};
	}
}


	auto GetSettingAuthDB() noexcept -> __detail::auth_db_settings&
	{
		return __detail::auth_db_settings::instance();
	}
}