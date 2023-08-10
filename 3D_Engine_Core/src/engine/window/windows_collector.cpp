#include <engine/window/windows_collector.hpp>

#include <algorithm>



namespace engine
{
	windows_collector::windows_storage windows_collector::s_windows_storage;



	void windows_collector::addNewWindow(std::shared_ptr<glfw_window> _window_ptr)
	{
		s_windows_storage.push_back(std::move(_window_ptr));
	}



	void windows_collector::closeAllWindows() noexcept
	{
		std::for_each(s_windows_storage.begin(), s_windows_storage.end(),
			[](std::shared_ptr<glfw_window>& _window_ptr)
			{
				_window_ptr->shutdown();
			});
		s_windows_storage.clear();
	}
}