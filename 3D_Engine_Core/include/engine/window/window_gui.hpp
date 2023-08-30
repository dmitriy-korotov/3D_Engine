#pragma once

#include <engine/window/glfw_window.hpp>



namespace engine
{
	class window_gui final: public glfw_window
	{
	public:

		window_gui(const std::string_view& _title);

		std::optional<error::window_error> create(std::uint16_t _width, std::uint16_t _height) noexcept override;

		void onUpdate() noexcept override;

	};
}