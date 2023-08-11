#pragma once

#include <engine/window/windows_collector.hpp>
#include <engine/window/glfw_window.hpp>



namespace engine
{
	class windows_manager: public windows_collector
	{
	public:

		static std::pair<glfw_window::WindowData&, const window::CallBackStorage&>
		getWindowDataAndCBS(const std::shared_ptr<glfw_window>& _window_ptr) noexcept;

		static std::pair<glfw_window::WindowData&, const window::CallBackStorage&>
		getWindowDataAndCBS(GLFWwindow* _window_ptr) noexcept;

	private:

		static const std::shared_ptr<glfw_window>& __getWindowFromRawPtr(GLFWwindow* _window_raw_ptr) noexcept;

	};
}