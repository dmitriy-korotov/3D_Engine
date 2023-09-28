#pragma once 

#include <string>



namespace engine
{
	static constexpr std::string_view TITLE_SETTING_NAME = "title";
	static constexpr std::string_view WIDTH_SETTING_NAME = "width";
	static constexpr std::string_view HEIGHT_SETTING_NAME = "height";
	static constexpr std::string_view PATH_TO_WINDOW_ICON_NAME = "path_to_window_icon";

	static constexpr std::string_view WINDOW_IMPL_SETTING_NAME = "window_impl";
	static constexpr std::string_view GLFW_IMPLE = "GLFW";
	static constexpr std::string_view SDL_IMPL = "SDL";
	static constexpr std::string_view SFML_IMPL = "SFML";

	static constexpr std::string_view OPEN_MODE_SETTING_NAME = "open_mode";
	static constexpr std::string_view FULL_SCREEN_OPEN_MODE = "full_srceen";
	static constexpr std::string_view IN_WINDOW_OPEN_MODE = "in_window";
}