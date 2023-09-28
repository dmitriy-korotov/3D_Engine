#pragma once

#include <engine/window/basic_window.hpp>
#include <engine/window/events_data.hpp>



struct GLFWwindow;

namespace engine::window::glfw
{
	class glfw_window: public std::enable_shared_from_this<glfw_window>,
					   public basic_window
	{
	public:

		using glfw_window_ptr_t = GLFWwindow*;

		~glfw_window() override;

		window_err create(const std::string_view& _title, uint16_t _width,
						  uint16_t _height, OpenMode _open_mode = OpenMode::InWindow) noexcept override;

		void shutdown() noexcept override;
		void onUpdate() noexcept override;

		glm::dvec2 getCurrentCursorPosition() const noexcept override;

		void setupIcon(const path& _path_to_icon) const noexcept override;

	private:

		void setWindowResizeCallBack() const noexcept override;
		void setWindowCloseCallBack() const noexcept override;
		void setKeyboardInputCallBack() const noexcept override;
		void setMouseInputCallBack() const noexcept override;

		window_err createWindow(OpenMode _open_mode) noexcept;

	protected:

		glfw_window_ptr_t m_window_ptr = nullptr;

	};
}