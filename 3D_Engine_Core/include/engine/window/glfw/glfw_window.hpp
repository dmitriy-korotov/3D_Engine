#pragma once

#include <engine/window/basic_window.hpp>
#include <engine/window/glfw/events_data.hpp>

#include <array>



struct GLFWwindow;

namespace engine::window::glfw
{
	class windows_collector;
	class windows_manager;

	class window : public std::enable_shared_from_this<window>,
				   public basic_window
	{
	public:
		
		friend windows_collector;
		friend windows_manager;

		window(const std::string_view& _title);
		~window() override;

		std::optional<error::window_error> create(uint16_t _width, uint16_t _height) noexcept override;
		void shutdown() noexcept override;
		void onUpdate() noexcept override;

		template<Events _event_type, typename CallBackFunction>
		void addEventListener(CallBackFunction _call_back) noexcept;

	private:

		void setWindowResizeCallBack() const noexcept;
		void setWindowCloseCallBack() const noexcept;

		std::optional<error::window_error> __glfwInit() const noexcept;

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
}