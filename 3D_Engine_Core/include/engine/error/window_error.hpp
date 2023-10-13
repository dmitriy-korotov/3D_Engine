#pragma once

#include <cstdint>



namespace engine::error
{
	enum class window_error : uint8_t
	{
		can_not_create,
		can_not_init_GLFW,
		can_not_init_SDL,
		can_not_init_SFML,
		can_not_add_new_window,
		window_already_exists
	};
}