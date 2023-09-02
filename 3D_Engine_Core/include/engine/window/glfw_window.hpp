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

		std::optional<error::window_error> create(uint16_t _width, uint16_t _height) noexcept override;
		void shutdown() noexcept override;
		void onUpdate() noexcept override;

		template<window::Events _event_type, typename CallBackFunction>
		void addEventListener(CallBackFunction _call_back) noexcept;

	private:

		void setWindowResizeCallBack() const noexcept;
		void setWindowCloseCallBack() const noexcept;

		std::optional<error::window_error> __glfwInit() const noexcept;

	protected:

		GLFWwindow* m_window_ptr = nullptr;
		window::CallBackStorage m_window_call_backs_;

		 bg_color m_bg_color_ = { 0.f, 0.f, 0.f, 0.f };

	};
}





template<engine::window::Events _event_type, typename CallBackFunction>
void engine::glfw_window::addEventListener(CallBackFunction _call_back) noexcept
{
	if constexpr (_event_type == window::Events::Resize)
	{
		m_window_call_backs_.resize_call_back = std::move(_call_back);
		setWindowResizeCallBack();
	}
	if constexpr (_event_type == window::Events::Close)
	{
		m_window_call_backs_.close_call_back = std::move(_call_back);
		setWindowCloseCallBack();
	}
}