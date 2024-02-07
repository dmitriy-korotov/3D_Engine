#include <engine/net/db/connection_data.hpp>

#include <sstream>



namespace engine::net::db
{
	auto connection_data::toString() const noexcept -> std::string
	{
		std::stringstream out;

		bool out_is_empty = dbname.empty();

		if (!dbname.empty())
			out << "dbname=" << dbname;

		if (!hostaddr.empty())
		{
			if (!out_is_empty)
				out << " ";
			out_is_empty = false;

			out << "hostaddr=" << hostaddr;
		}

		if (!user.empty())
		{
			if (!out_is_empty)
				out << " ";
			out_is_empty = false;

			out << "user=" << user;
		}

		if (!password.empty())
		{
			if (!out_is_empty)
				out << " ";
			out_is_empty = false;

			out << "password=" << password;
		}

		return out.str();
	}
}