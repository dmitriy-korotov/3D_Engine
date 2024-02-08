#include <auth/db/tables/users_table.hpp>

#include <cassert>



static constexpr std::string_view phone_confirm_method = "phone";
static constexpr std::string_view email_confirm_method = "email";



namespace auth::tables
{
	auto toString(users_table::confirm_method _confirm_method) noexcept -> std::string
	{
		switch (_confirm_method)
		{
		case users_table::confirm_method::Phone:
			return phone_confirm_method.data();
		case users_table::confirm_method::Email:
			return email_confirm_method.data();
		case users_table::confirm_method::Unknown:
			return "unknown";
		default:
			assert(0);
		}
		return {};
	}



	auto toConfimMethodEnum(std::string_view _str_confirm_method) noexcept -> users_table::confirm_method
	{
		if (_str_confirm_method == phone_confirm_method)
			return users_table::confirm_method::Phone;
		else if (_str_confirm_method == email_confirm_method)
			return users_table::confirm_method::Email;
		else
			return users_table::confirm_method::Unknown;
	}
}