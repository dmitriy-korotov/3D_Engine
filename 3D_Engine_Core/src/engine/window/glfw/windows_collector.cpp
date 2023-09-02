#include <engine/window/glfw/windows_collector.hpp>

#include <engine/window/glfw/glfw_window.hpp>

#include <algorithm>



namespace engine::window::glfw
{
	windows_collector::windows_storage windows_collector::s_windows_storage_;





	void windows_collector::addNewWindow(window_ptr _window_ptr)
	{
		s_windows_storage_.push_back(std::move(_window_ptr));
	}



	void windows_collector::closeAllWindows() noexcept
	{
		std::for_each(s_windows_storage_.begin(), s_windows_storage_.end(),
			[](window_ptr& _window_ptr) -> void
			{
				_window_ptr->shutdown();
			});
		s_windows_storage_.clear();
	}
}