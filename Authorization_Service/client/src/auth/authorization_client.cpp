#include <auth/authorization_client.hpp>

#include <nlohmann/json.hpp>



using namespace nlohmann;

namespace auth
{
	authorization_client::authorization_client(asio::io_context& _context) noexcept
			: m_client(_context)
	{ }



	auto authorization_client::registrateUser(const user& _user) const -> asio::awaitable<bool>
	{
		json json_user;
		json_user["login"] = _user.getLogin();
		json_user["password"] = _user.getPassword();
		if (_user.getConfirmationMethod() == confirmation_method::Phone)
		{
			json_user["confirmation_method"] = "phone";
			json_user["phone"] = _user.getPhone();
		}
		else
		{
			json_user["confirmation_method"] = "email";
			json_user["email"] = _user.getEmail();
		}
		auto response = co_await m_client.POST(url::fromString("/api/v1/users"), json_user.dump());
		
		co_return response.getStatus() == response_status::ok;
	}



	auto authorization_client::autorizateUser(const std::string& _user_login, const std::string& _password) const -> asio::awaitable<bool>
	{
		json data;
		data["login"] = _user_login;
		data["password"] = _password;
		
		auto response = co_await m_client.POST(url::fromString("/api/v1/users/" + _user_login), data.dump());

		co_return response.getStatus() == response_status::ok;
	}
}