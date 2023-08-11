#pragma once

#include <vector>
#include <memory>



namespace engine
{
	class glfw_window;



	class windows_collector
	{
	public:

		using windows_storage = std::vector<std::shared_ptr<glfw_window>>;

		windows_collector() = delete;

		static void addNewWindow(std::shared_ptr<glfw_window> _window_ptr);
		static void closeAllWindows() noexcept;

	protected:

		static windows_storage s_windows_storage_;

	};
}