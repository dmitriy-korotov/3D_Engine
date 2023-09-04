#include <engine/window/glfw/windows_collector.hpp>

#include <engine/window/glfw/glfw_window.hpp>

#include <algorithm>



namespace engine::window::glfw
{
	windows_collector::windows_storage windows_collector::s_windows_storage_;





	void windows_collector::addNewWindow(window_ptr _window_ptr)
	{
		s_windows_storage_.insert(std::move(_window_ptr));
	}



	void windows_collector::removeWindow(const window_ptr& _window_ptr) noexcept
	{
		if (!s_windows_storage_.empty())
		{
			s_windows_storage_.erase(_window_ptr);
		}
	}



	size_t windows_collector::getWindowsCount() noexcept
	{
		return s_windows_storage_.size();
	}



	void windows_collector::closeAllWindows() noexcept
	{
		std::for_each(s_windows_storage_.begin(), s_windows_storage_.end(),
			[](auto& _window_ptr) -> void
			{
				_window_ptr->shutdown();
			});
		s_windows_storage_.clear();
	}
}