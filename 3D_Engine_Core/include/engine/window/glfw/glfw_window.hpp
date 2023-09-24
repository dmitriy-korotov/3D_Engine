#pragma once

#include <engine/window/basic_window.hpp>
#include <engine/window/events_data.hpp>

#include <filesystem>
#include <array>



struct GLFWwindow;

namespace engine::window::glfw
{
	using std::filesystem::path;

	class glfw_window : public std::enable_shared_from_this<glfw_window>,
				   public basic_window
	{
	public:

		~glfw_window() override;

		window_err create(const std::string_view& _title, uint16_t _width,
						  uint16_t _height, OpenMode _open_mode = OpenMode::InWindow) noexcept override;

		void shutdown() noexcept override;
		void onUpdate() noexcept override;

		glm::dvec2 getCurrentCursorPosition() const noexcept override;

		void setupIcon(const path& _path_to_icon) const noexcept;

	private:

		void setWindowResizeCallBack() const noexcept override;
		void setWindowCloseCallBack() const noexcept override;
		void setKeyboardInputCallBack() const noexcept override;
		void setMouseInputCallBack() const noexcept override;

		window_err __glfwInit() const noexcept;
		window_err __createGlfwWindow(OpenMode _open_mode) noexcept;

	protected:

		GLFWwindow* m_window_ptr = nullptr;

	};
}