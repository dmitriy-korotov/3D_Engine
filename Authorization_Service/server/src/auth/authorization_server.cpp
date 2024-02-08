#include <auth/authorization_server.hpp>

#include <engine/logging/log.hpp>

#include <engine/net/db/connection_data.hpp>

#include <auth/db/auth_db_settings.hpp>
#include <auth/db/tables/users_table.hpp>

#include <nlohmann/json.hpp>

#include <pqxx/pqxx>

#include <format>





using namespace nlohmann;

namespace auth
{
	auto makeErrorResponse(http::response_status _response_status, int64_t _error_code,
						   std::string_view _error_message) noexcept -> http::response_t
	{
		http::response_t response;
		response.setStatus(_response_status);

		json body;
		body["code"] = _error_code;
		body["message"] = _error_message;

		response.setBody(body.dump());

		return response;
	}





	class authorization_server::authorization_server_impl
	{
	public:

		using connection_ptr_t = std::unique_ptr<pqxx::connection>;

		bool connectToDataBase(const db::connection_data& _connection_data) noexcept;

		const connection_ptr_t& getConnectionHandle() const noexcept;

	private:

		connection_ptr_t m_connection = nullptr;

	};



	auto authorization_server::authorization_server_impl::connectToDataBase(const db::connection_data& _connection_data) noexcept -> bool
	{
		try
		{
			m_connection = std::make_unique<pqxx::connection>(_connection_data.toString());
		}
		catch (const std::exception& _ex)
		{
			LOG_CRITICAL("[Authorization server CRITICAL] Can't connect to data base, "
						 "was throwed exception: '{0}'", std::string(_ex.what()));
			return false;
		}
		
		return m_connection->is_open();
	}



	auto authorization_server::authorization_server_impl::getConnectionHandle() const noexcept -> const connection_ptr_t&
	{
		return m_connection;
	}





	authorization_server::authorization_server() noexcept
			: m_pimpl(std::make_unique<authorization_server_impl>())
	{ }



	authorization_server::~authorization_server()
	{ }



	auto authorization_server::pimpl() const noexcept -> const pimpl_ptr_t&
	{
		return m_pimpl;
	}



	auto authorization_server::startOn(std::string_view _address, uint16_t _port) -> bool
	{
		registrateAPI();

		if (!connectToDataBase())
			return false;

		listen(_address, _port);

		return true;
	}



	auto authorization_server::registrateAPI() noexcept -> void
	{
		registrateURLHandler("/api/v1/users",
							 http::request_method::Post,
							 std::bind(&authorization_server::createUserHandler, this, std::placeholders::_1));
	}



	auto authorization_server::connectToDataBase() noexcept -> bool
	{
		db::connection_data conn_data
		{
			.dbname = GetSettingAuthDB().getDataBaseName(),
			.hostaddr = GetSettingAuthDB().getDataBaseHostaddr(),
			.user = GetSettingAuthDB().getDataBaseUser(),
			.password = GetSettingAuthDB().getDataBaseUserPassword()
		};
		auto connected = pimpl()->connectToDataBase(conn_data);
		if (!connected)
		{
			LOG_ERROR("[Authorization server ERROR] Can't connect to database");
			return false;
		}
		LOG_INFO("[Authorization server INFO] Successfully connect to data base");
		return true;
	}



	auto authorization_server::createUserHandler(http::request_t& _request) noexcept -> http::response_t
	{
		static std::string insert_query_first_line = std::format("INSERT INTO {} ({}, {}, {}, {}, {})",
																  tables::users_table::table_name,
																  tables::users_table::email_field,
																  tables::users_table::phone_field,
																  tables::users_table::confirm_method_field,
																  tables::users_table::username_field,
																  tables::users_table::password_field);



		LOG_INFO("[Authorization server INFO] POST '/api/v1/users' handler started");

		pqxx::work transaction(*pimpl()->getConnectionHandle());

		try
		{
			auto user_data = json::parse(std::move(_request).getBody());

			std::string confirm_method = std::move(user_data[tables::users_table::confirm_method_field]);
			std::string username = std::move(user_data[tables::users_table::username_field]);
			std::string password = std::move(user_data[tables::users_table::password_field]);
			std::string email_or_phone;



			auto enum_confirm_method = tables::toConfimMethodEnum(confirm_method);

			if (enum_confirm_method == tables::users_table::confirm_method::Phone)
				email_or_phone = std::move(user_data[tables::users_table::phone_field]);
			else if (enum_confirm_method == tables::users_table::confirm_method::Email)
				email_or_phone = std::move(user_data[tables::users_table::email_field]);
			else
			{
				std::string error_message = std::format("Invalid confirmation method '{}'", confirm_method);
				return makeErrorResponse(http::response_status::bad_getway, 1, error_message);
			}



			std::string query;

			if (enum_confirm_method == tables::users_table::confirm_method::Phone)
			{
				query = std::format("{} VALUES (NULL, '{}', '{}', '{}', '{}');",
									insert_query_first_line, email_or_phone,
									confirm_method, username, password);
			}
			else if (enum_confirm_method == tables::users_table::confirm_method::Email)
			{
				query = std::format("{} VALUES ('{}', NULL, '{}', '{}', '{}');",
									insert_query_first_line, email_or_phone,
									confirm_method, username, password);
			}

			

			auto result = transaction.exec(query);
			transaction.commit();

			if (result.affected_rows() == 1)
				LOG_INFO("[Authorization server INFO] User successfully registrated");
			else
			{
				LOG_ERROR("[Authorization server ERROR] Can't registrate user");
				return makeErrorResponse(http::response_status::bad_getway, 2, "Can't registrate user, repeat request again");
			}
		}
		catch (const std::exception& _ex)
		{
			transaction.commit();

			LOG_ERROR("[Authorization server ERROR] Throwed exception, "
					  "while processed user registration: {0}", std::string(_ex.what()));

			return makeErrorResponse(http::response_status::bad_getway, 3, "Unexpected input data");
		}

		LOG_INFO("[Authorization server INFO] POST '/api/v1/users' handler ended");

		return {};
	}
}