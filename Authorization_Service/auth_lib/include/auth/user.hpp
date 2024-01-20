#pragma once

#include <string>



namespace auth
{
	enum class confirmation_method : uint8_t
	{
		Phone,
		Email
	};

	struct email_t
	{
		std::string email;
	};

	struct phone_t
	{
		std::string phone;
	};



	class user
	{
	public:

		user() = default;
		user(std::string _login, email_t _email, std::string _password) noexcept;
		user(std::string _login, phone_t _phone, std::string _password) noexcept;
		~user();

		void setLogin(std::string _login) noexcept;
		void setPhone(phone_t _phone) noexcept;
		void setEmail(email_t _email) noexcept;
		void setPassword(std::string _password) noexcept;

		const std::string& getLogin() const noexcept;
		const std::string& getPhone() const;
		const std::string& getEmail() const;
		const std::string& getPassword() const noexcept;

		confirmation_method getConfirmationMethod() const noexcept;

	private:

		user(std::string _login, std::string _password, confirmation_method _method) noexcept;

	private:

		union
		{
			std::string m_email;
			std::string m_phone_number;
		};

		confirmation_method m_method = confirmation_method::Email;

		std::string m_login;
		std::string m_password;
	};
}