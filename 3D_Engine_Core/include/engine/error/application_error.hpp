#pragma once



namespace engine::error
{
	enum class application_error
	{
		can_not_create,
		can_not_setup_renderer,
		can_not_setup_UIModule,
		can_not_create_window,
		application_already_exists,
		can_not_load_config
	};
}