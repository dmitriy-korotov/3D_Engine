#pragma once

#include <engine/util/noconstructible.hpp>

#include <auth/user.hpp>



namespace editor::controllers
{
	class registration_controller : engine::util::noconstructible
	{
	public:

		static bool registrateUser(const auth::user& _user) noexcept;

	};
}