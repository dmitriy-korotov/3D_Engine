#pragma once

#include <string>



namespace engine::net::db
{
	struct connection_data
	{

		std::string toString() const noexcept;

		std::string dbname;
		std::string hostaddr;
		std::string user;
		std::string password;

	};
}