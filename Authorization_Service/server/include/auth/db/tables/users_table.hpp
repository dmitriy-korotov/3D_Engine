#pragma once

#include <engine/util/noconstructible.hpp>

#include <string>



namespace auth::tables
{
	class users_table : private engine::util::noconstructible
	{
	public:

		enum class confirm_method : uint8_t
		{
			Phone,
			Email,
			Unknown
		};

		// table name
		static constexpr std::string_view table_name = "users";

		// table columns titles
		static constexpr std::string_view user_id_field = "user_id";
		static constexpr std::string_view username_field = "username";
		static constexpr std::string_view email_field = "email";
		static constexpr std::string_view phone_field = "phone";
		static constexpr std::string_view confirm_method_field = "confirm_method";
		static constexpr std::string_view password_field = "password";

	private:



	};



	std::string toString(users_table::confirm_method _confirm_method) noexcept;

	users_table::confirm_method toConfimMethodEnum(std::string_view _str_confirm_method) noexcept;

}