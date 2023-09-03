#pragma once

#include <engine/window/glfw/windows_collector.hpp>
#include <engine/window/glfw/glfw_window.hpp>



namespace engine::window::glfw
{
	class windows_manager : public windows_collector
	{
	public:

		using WindowDataAndCBS = std::pair<window::window_data&, const CallBackStorage&>;

		static WindowDataAndCBS getWindowDataAndCBS(const window_ptr& _window_ptr) noexcept;
		static WindowDataAndCBS	getWindowDataAndCBS(GLFWwindow* _window_ptr);

	private:

		static window_ptr __getWindowFromRawPtr(GLFWwindow* _window_raw_ptr) noexcept;

	};
}