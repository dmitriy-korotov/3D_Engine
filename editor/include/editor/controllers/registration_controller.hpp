#pragma once

#include <engine/util/noconstructible.hpp>

#include <engine/error/error.hpp>

#include <auth/user.hpp>

#include <asio/awaitable.hpp>



namespace editor::controllers
{
	class registration_controller : engine::util::noconstructible
	{
	public:

		static asio::awaitable<engine::error::error> onClickRegistrateButton(const auth::user& _user) noexcept;

	};
}