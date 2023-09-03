#pragma once



namespace engine::error
{
	enum class window_error
	{
		can_not_create,
		can_not_init_glfw,
		can_not_add_new_window,
		window_already_exists
	};
}