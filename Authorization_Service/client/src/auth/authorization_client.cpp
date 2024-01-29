#include <auth/authorization_client.hpp>

#include <nlohmann/json.hpp>



using namespace nlohmann;

namespace auth
{
	static auto fillJSONUserData(const user& _user) noexcept -> json
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
		return json_user;
	}





	authorization_client::authorization_client(asio::io_context& _context) noexcept
			: m_client(_context)
	{ }



	authorization_client::authorization_client(asio::io_context& _context, const host& _host) noexcept
		: m_client(_context)
	{ 
		m_client.connect(_host);
	}



	auto authorization_client::connect(const host& _host) noexcept -> void
	{
		if (m_client.isConnected())
		{
			auto host = m_client.getHost();
			LOG_WARN("[Authorization client WARN] Client already connected to host '{0}:{1}'",
					 host.getAddress(), host.getPort());
			return;
		}
		m_client.connect(_host);
	}



	auto authorization_client::disconnect() noexcept -> void
	{
		m_client.disconnect();
	}



	auto authorization_client::registrateUser(const user& _user) const -> asio::awaitable<error>
	{
		if (!m_client.isConnected())
			throw std::runtime_error("Client is not connected to host");

		auto json_user = fillJSONUserData(_user);

		auto response = co_await m_client.POST(url::fromString("/api/v1/users"), json_user.dump());
		
		if (response.getStatus() == response_status::ok)
			co_return no_error;

		try
		{
			auto json_error = json::parse(std::move(response).getBody());
			int64_t code = json_error["code"];
			std::string message = json_error["message"];

			co_return error(std::move(message), code);
		}
		catch (const std::exception& _ex)
		{
			LOG_ERROR("[Authorization client ERROR] Unexpected fields in server response body");
			LOG_ERROR("[Authorization client ERROR] {0}", std::string(_ex.what()));
		}
		co_return error("Unexpected server error");
	}



	auto authorization_client::autorizateUser(const std::string& _user_login, const std::string& _password) const -> asio::awaitable<error>
	{
		json data;
		data["login"] = _user_login;
		data["password"] = _password;
		
		auto response = co_await m_client.POST(url::fromString("/api/v1/users/" + _user_login), data.dump());

		co_return no_error;
	}
}