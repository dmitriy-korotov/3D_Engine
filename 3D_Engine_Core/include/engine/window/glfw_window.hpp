#pragma once

#include <engine/window/basic_window.hpp>
#include <engine/window/events_data.hpp>

#include <vector>



struct GLFWwindow;

namespace engine
{
	class glfw_window final : public basic_window
	{
	public:

		friend std::pair<WindowData&, const window::CallBackStorage&> __getWindowDataAndCallBackStorage(glfw_window& _window) noexcept;
		friend glfw_window* getWindow(GLFWwindow* _window_ptr);



		glfw_window(std::uint16_t _width, std::uint16_t _height,
					const std::string_view& _title);
		~glfw_window();

		void onUpdate() noexcept override;

		template<window::Events _event_type, typename _CallBackFunction>
		void addEventListener(_CallBackFunction _call_back) noexcept;

	private:

		std::optional<error::window_error> create() noexcept override;
		void shutdown() noexcept override;
		
		std::optional<error::window_error> __glfwInit() const noexcept;
		const GLFWwindow* const __getRawPtr() const noexcept;

	private:

		GLFWwindow* m_window_ptr = nullptr;
		window::CallBackStorage m_window_call_backs_;

	private:

		static std::vector<glfw_window*> s_all_windows_;

	};





	template<window::Events _event_type, typename _CallBackFunction>
	void glfw_window::addEventListener(_CallBackFunction _call_back) noexcept
	{
		if constexpr (_event_type == window::Events::Resize)
		{
			m_window_call_backs_.resize_call_back_ = std::move(_call_back);
			glfwSetWindowSizeCallback(m_window_ptr,
				[](GLFWwindow* _window_ptr, int _width, int _height) -> void
				{
					auto [window_data, call_backs] = __getWindowDataAndCallBackStorage(*getWindow(_window_ptr));
					window_data.height = _height;
					window_data.width = _width;

					window::ResizeEventData resize_data = { window_data.height, window_data.width };
					call_backs.resize_call_back_(resize_data);
				});
		}
		if constexpr (_event_type == window::Events::Close)
		{
			m_window_call_backs_.close_call_back_ = std::move(_call_back);
			glfwSetWindowCloseCallback(m_window_ptr,
				[](GLFWwindow* _window_ptr) -> void
				{
					auto [window_data, call_backs] = __getWindowDataAndCallBackStorage(*getWindow(_window_ptr));
					call_backs.close_call_back_();
				});
		}
	}
}