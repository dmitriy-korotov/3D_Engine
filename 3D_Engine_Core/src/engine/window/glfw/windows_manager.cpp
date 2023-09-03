#include <engine/window/glfw/windows_manager.hpp>

#include <engine/logging/log.hpp>



namespace engine::window::glfw
{
	std::pair<window::window_data&, const CallBackStorage&>
	windows_manager::getWindowDataAndCBS(const window_ptr& _window_ptr) noexcept
	{
		return std::make_pair(std::ref(_window_ptr->m_window_data_),
							  std::cref(_window_ptr->m_window_call_backs_));
	}



	std::pair<window::window_data&, const CallBackStorage&>
	windows_manager::getWindowDataAndCBS(GLFWwindow* _window_ptr)
	{
		auto& window_ = getWindowFromRawPtr(_window_ptr);
		if (window_ == nullptr)
		{
			LOG_ERROR("[Windows Manager ERROR] Window is not found in windows collector.");
			throw std::exception("Window is not found in windows collector.");
		}
		return std::make_pair(std::ref(window_->m_window_data_),
							  std::cref(window_->m_window_call_backs_));
	}
}