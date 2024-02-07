#include <auth/authorization_server.hpp>

#include <engine/logging/log.hpp>

#include <nlohmann/json.hpp>

#include <pqxx/pqxx>

#include <format>





using namespace nlohmann;

namespace auth
{
	authorization_server::authorization_server() noexcept
	{ 
		registrateAPI();
	}



	auto authorization_server::startOn(std::string_view _address, uint16_t _port) -> void
	{
		listen(_address, _port);
	}



	auto authorization_server::registrateAPI() noexcept -> void
	{
		registrateURLHandler("/api/v1/users",
							 request_method::Post,
							 std::bind(&authorization_server::createUserHandler, this, std::placeholders::_1));
	}



	response_t authorization_server::createUserHandler(const request_t& _request)
	{
		LOG_INFO("[Authorization server INFO] POST '/api/v1/users' handler started");

		pqxx::connection conn("dbname=users hostaddr=127.0.0.1 user=dmitriy password=Votorok228");
		if (conn.is_open())
		{
			LOG_INFO("Connection to database succesful!");
		}
		else
		{
			LOG_ERROR("Something went wrong... oops");
			return {};
		}
		pqxx::work w(conn);

		engine::net::http::response<string_body> response;

		try
		{
			auto user_data = json::parse(_request.getBody());

			auto result = w.exec(std::format("INSERT INTO users (email, phone, confirm_method, username, password)"
				"VALUES ('{0}', '{1}', '{2}', '{3}', '{4}')",
				std::string(user_data["email"]), std::string(user_data["phone"]),
				std::string(user_data["confirm_method"]), std::string(user_data["username"]),
				std::string(user_data["password"])));

			if (result.affected_rows() == 1)
				LOG_INFO("[Authorization server INFO] User successfully registrated");
			else
				LOG_INFO("[Authorization server INFO] Can't registrate user");

			pqxx::result res = w.exec("SELECT * from users");

			for (const auto& row : res)
			{
				LOG_INFO("user_id '{0}', email '{1}', phone '{2}', username '{3}', password '{4}', conf_method '{5}'",
					row["user_id"].as<std::string>(),
					row["email"].as<std::string>(),
					row["phone"].as<std::string>(),
					row["username"].as<std::string>(),
					row["password"].as<std::string>(),
					row["confirm_method"].as<std::string>());
			}

			w.commit();
		}
		catch (const std::exception& _ex)
		{
			LOG_ERROR("[Authorization server INFO] Exception: {0}", std::string(_ex.what()));
			response.setStatus(response_status::bad_getway);
			response.setBody("{code:500, message:\"Server error\"}");
			return response;
		}


		response.setBody("<html><h1>New user created!</h1></html>");
		return response;
	}
}