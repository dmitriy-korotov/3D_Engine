#include <auth/user.hpp>

#include <stdexcept>



namespace auth
{
	user::user(std::string _login, std::string _password, confirmation_method _method) noexcept
			: m_login(std::move(_login))
			, m_password(std::move(_password))
			, m_method(_method)
			, m_email()
	{ }



	user::user(std::string _login, email_t _email, std::string _password) noexcept
			: user(std::move(_login), std::move(_password), confirmation_method::Email)
	{ 
		m_email = std::move(_email.email);
	}



	user::user(std::string _login, phone_t _phone, std::string _password) noexcept
			: user(std::move(_login), std::move(_password), confirmation_method::Phone)
	{ 
		m_phone_number = std::move(_phone.phone);
	}



	user::~user()
	{
		m_email.~basic_string();
	}



	void user::setLogin(std::string _login) noexcept
	{
		m_login = std::move(_login);
	}



	void user::setPhone(phone_t _phone) noexcept
	{
		m_phone_number = std::move(_phone.phone);
		m_method = confirmation_method::Phone;
	}



	void user::setEmail(email_t _email) noexcept
	{
		m_email = std::move(_email.email);
		m_method = confirmation_method::Email;
	}



	void user::setPassword(std::string _password) noexcept
	{
		m_password = std::move(_password);
	}



	const std::string& user::getLogin() const noexcept
	{
		return m_login;
	}



	const std::string& user::getPhone() const
	{
		if (m_method == confirmation_method::Email)
			throw std::runtime_error("Invalid confirmation method (current is 'email')");
		return m_phone_number;
	}



	const std::string& user::getEmail() const
	{
		if (m_method == confirmation_method::Phone)
			throw std::runtime_error("Invalid confirmation method (current is 'phone')");
		return m_email;
	}



	const std::string& user::getPassword() const noexcept
	{
		return m_password;
	}



	confirmation_method user::getConfirmationMethod() const noexcept
	{
		return m_method;
	}
}