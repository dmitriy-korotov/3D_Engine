#pragma once 

#include <engine/window/common_types.hpp>
#include <engine/render/common_types.hpp>
#include <engine/modules/basic_UIModule.hpp>

#include <string>



namespace engine
{
	static constexpr std::string_view TITLE_SETTING_NAME =				"title";
	static constexpr std::string_view WIDTH_SETTING_NAME =				"width";
	static constexpr std::string_view HEIGHT_SETTING_NAME =				"height";
	static constexpr std::string_view PATH_TO_WINDOW_ICON_NAME =		"path_to_window_icon";

	static constexpr std::string_view WINDOW_IMPL_SETTING_NAME =		"window_impl";
	static constexpr std::string_view GLFW_IMPLE =						"GLFW";
	static constexpr std::string_view SDL_IMPL =						"SDL";
	static constexpr std::string_view SFML_IMPL =						"SFML";

	static constexpr std::string_view OPEN_MODE_SETTING_NAME =			"open_mode";
	static constexpr std::string_view FULL_SCREEN_OPEN_MODE =			"full_srceen";
	static constexpr std::string_view IN_WINDOW_OPEN_MODE =				"in_window";

	static constexpr std::string_view RENDERER_IMPL_SETTING_NAME =		"renderer_impl";

	static constexpr std::string_view OPEN_GL_IMPL =					"OpenGL";
	static constexpr std::string_view DIRECT_X_IMPL =					"DirectX";
	static constexpr std::string_view DIRECT_3D_IMPL =					"Direct3D";
	static constexpr std::string_view VULCAN_IMPL =						"Vulcan";

	static constexpr std::string_view UI_MODULE_IMPL_SETTING_NAME =		"UI_module_impl";

	static constexpr std::string_view IMGUI_IMPL =					"ImGui";
	static constexpr std::string_view QT_IMPL =						"Qt";
	static constexpr std::string_view JUCE_IMPL =					"Juce";
	static constexpr std::string_view GTK_PLUS_IMPL =					"GTK+";



	window::WindowImpl toWindowImpl(const std::string_view& _str_window_impl) noexcept;
	window::OpenMode toOpenMode(const std::string_view& _str_open_mode) noexcept;
	render::RendererImpl toRendererImpl(const std::string_view& _str_renderer_impl) noexcept;
	modules::UIModuleImpl toUIModuleImpl(const std::string_view& _str_UI_module_impl) noexcept;
}