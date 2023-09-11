#pragma once

#include <engine/window/basic_window.hpp>
#include <engine/window/glfw/events_data.hpp>

#include <glm/vec2.hpp>

#include <filesystem>
#include <array>



struct GLFWwindow;

namespace engine::window::glfw
{
	class windows_manager;

	class window : public std::enable_shared_from_this<window>,
		public basic_window
	{
	public:

		friend windows_manager;

		window(const std::string_view& _title);
		~window() override;

		std::optional<error::window_error> create(uint16_t _width, uint16_t _height, bool _is_full_screen_mode = false) noexcept override;
		void shutdown() noexcept override;
		void onUpdate() noexcept override;

		glm::dvec2 getCurrentCursorPosition() const noexcept;

		template<Events _event_type, typename CallBackFunction>
		void addEventListener(CallBackFunction _call_back) noexcept;

		void setupIcon(const std::filesystem::path& _path_to_icon) const noexcept;

	private:

		void setWindowResizeCallBack() const noexcept;
		void setWindowCloseCallBack() const noexcept;
		void setKeyboardInputCallBack() const noexcept;
		void setMouseInputCallBack() const noexcept;

		std::optional<error::window_error> __glfwInit() const noexcept;
		std::optional<error::window_error> __createGlfwWindow(bool _is_full_screen_mode = false) noexcept;

	protected:

		GLFWwindow* m_window_ptr = nullptr;
		window::CallBackStorage m_window_call_backs_;

	};

}





template<engine::window::glfw::Events _event_type, typename CallBackFunction>
void engine::window::glfw::window::addEventListener(CallBackFunction _call_back) noexcept
{
	if constexpr (_event_type == Events::Resize)
	{
		m_window_call_backs_.resize_call_back = std::move(_call_back);
		setWindowResizeCallBack();
	}
	if constexpr (_event_type == Events::Close)
	{
		m_window_call_backs_.close_call_back = std::move(_call_back);
		setWindowCloseCallBack();
	}
	if constexpr (_event_type == Events::KeyboardInput)
	{
		m_window_call_backs_.keyboard_input_call_back = std::move(_call_back);
		setKeyboardInputCallBack();
	}
	if constexpr (_event_type == Events::MouseInput)
	{
		m_window_call_backs_.mouse_input_call_back = std::move(_call_back);
		setMouseInputCallBack();
	}
}