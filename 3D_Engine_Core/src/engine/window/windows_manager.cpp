#include <engine/window/windows_manager.hpp>

#include <engine/logging/log.hpp>



namespace engine
{
	std::pair<glfw_window::window_data&, const window::CallBackStorage&>
	windows_manager::getWindowDataAndCBS(const std::shared_ptr<glfw_window>& _window_ptr) noexcept
	{
		return std::make_pair(std::ref(_window_ptr->m_window_data_),
							  std::cref(_window_ptr->m_window_call_backs_));
	}



	std::pair<glfw_window::window_data&, const window::CallBackStorage&>
	windows_manager::getWindowDataAndCBS(GLFWwindow* _window_ptr)
	{
		auto& window_ = __getWindowFromRawPtr(_window_ptr);
		if (window_ == nullptr)
		{
			LOG_ERROR("Window not found in windows collector.");
			throw std::exception("Window not found in windows collector.");
		}
		return std::make_pair(std::ref(window_->m_window_data_),
							  std::cref(window_->m_window_call_backs_));
	}



	std::shared_ptr<glfw_window> windows_manager::__getWindowFromRawPtr(GLFWwindow* _window_raw_ptr) noexcept
	{
		for (const auto& window_ : s_windows_storage_)
		{
			if (window_->m_window_ptr == _window_raw_ptr)
			{
				return window_;
			}
		}
		return nullptr;
	}
}