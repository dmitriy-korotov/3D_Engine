#pragma once



namespace engine::error
{
	enum class window_error
	{
		can_not_create,
		window_already_exists
	};

	enum class app_error
	{
		can_not_create,
		app_already_exists
	};
}