#pragma once

#include <engine/window/basic_window.hpp>
#include <engine/window/events_data.hpp>

#include <array>



struct GLFWwindow;

namespace engine
{
	class windows_manager;

	class glfw_window : public std::enable_shared_from_this<glfw_window>,
					    public basic_window
	{
	public:

		friend windows_manager;


			
		using bg_color = std::array<float, 4>;

		glfw_window(const std::string_view& _title);
		~glfw_window();

		std::optional<error::window_error> create(std::uint16_t _width, std::uint16_t _height) noexcept override;
		void shutdown() noexcept override;
		void onUpdate() noexcept override;

		template<window::Events _event_type, typename _CallBackFunction>
		void addEventListener(_CallBackFunction _call_back) noexcept;

	private:

		std::optional<error::window_error> __glfwInit() const noexcept;

	protected:

		GLFWwindow* m_window_ptr = nullptr;
		window::CallBackStorage m_window_call_backs_;

		 bg_color m_bg_color_ = { 0.f, 0.f, 0.f, 0.f };

	};
}



#include <engine/window/windows_manager.hpp>
#include <engine/logging/log.hpp>



template<engine::window::Events _event_type, typename _CallBackFunction>
void engine::glfw_window::addEventListener(_CallBackFunction _call_back) noexcept
{
	if constexpr (_event_type == window::Events::Resize)
	{
		m_window_call_backs_.resize_call_back_ = std::move(_call_back);
		glfwSetWindowSizeCallback(m_window_ptr,
			[](GLFWwindow* _window_ptr, int _width, int _height) -> void
			{
				try
				{
					auto [window_data, call_backs] = windows_manager::getWindowDataAndCBS(_window_ptr);
					window_data.height = _height;
					window_data.width = _width;

					window::ResizeEventData resize_data = { window_data.height, window_data.width };
					call_backs.resize_call_back_(resize_data);
				}
				catch (const std::exception& ex_)
				{
					LOG_ERROR("Window catched exception when handeled event: " + std::string(ex_.what()));
				}
			});
	}
	if constexpr (_event_type == window::Events::Close)
	{
		m_window_call_backs_.close_call_back_ = std::move(_call_back);
		glfwSetWindowCloseCallback(m_window_ptr,
			[](GLFWwindow* _window_ptr) -> void
			{
				try
				{
					auto [window_data, call_backs] = windows_manager::getWindowDataAndCBS(_window_ptr);
					call_backs.close_call_back_();
				}
				catch (const std::exception& ex_)
				{
					LOG_ERROR("Window catched exception when handeled event: " + std::string(ex_.what()));
				}
			});
	}
}