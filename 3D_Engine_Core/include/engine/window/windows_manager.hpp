#pragma once

#include <engine/window/windows_collector.hpp>
#include <engine/window/basic_window.hpp>



struct GLFWwindow;

namespace engine
{
	class windows_manager: public windows_collector
	{
	public:

		using WindowDataAndCBS = std::pair<basic_window::window_data&, const window::CallBackStorage&>;

		static WindowDataAndCBS getWindowDataAndCBS(const window_ptr& _window_ptr) noexcept;
		static WindowDataAndCBS	getWindowDataAndCBS(GLFWwindow* _window_ptr);

	private:

		static const window_ptr& __getWindowFromRawPtr(GLFWwindow* _window_raw_ptr) noexcept;

	};
}