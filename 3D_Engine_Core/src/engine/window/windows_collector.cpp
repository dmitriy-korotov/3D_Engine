#include <engine/window/windows_collector.hpp>

#include <engine/window/glfw_window.hpp>

#include <algorithm>



namespace engine
{
	void windows_collector::addNewWindow(std::shared_ptr<glfw_window> _window_ptr)
	{
		s_windows_storage_.push_back(std::move(_window_ptr));
	}



	void windows_collector::closeAllWindows() noexcept
	{
		std::for_each(s_windows_storage_.begin(), s_windows_storage_.end(),
			[](std::shared_ptr<glfw_window>& _window_ptr) -> void
			{
				_window_ptr->shutdown();
			});
		s_windows_storage_.clear();
	}
}