#include <engine/window/windows_manager.hpp>



namespace engine
{
	std::pair<glfw_window::WindowData&, const window::CallBackStorage&>
	windows_manager::getWindowDataAndCBS(const std::shared_ptr<glfw_window>& _window_ptr) noexcept
	{
		return std::make_pair(std::ref(_window_ptr->m_window_data_),
							  std::cref(_window_ptr->m_window_call_backs_));
	}



	std::pair<glfw_window::WindowData&, const window::CallBackStorage&>
	windows_manager::getWindowDataAndCBS(GLFWwindow* _window_ptr) noexcept
	{
		auto& window_ = __getWindowFromRawPtr(_window_ptr);
		return std::make_pair(std::ref(window_->m_window_data_),
							  std::cref(window_->m_window_call_backs_));
	}



	const std::shared_ptr<glfw_window>& windows_manager::__getWindowFromRawPtr(GLFWwindow* _window_raw_ptr) noexcept
	{
		for (auto& window_ : s_windows_storage_)
		{
			if (window_->m_window_ptr_ == _window_raw_ptr)
			{
				return window_;
			}
		}
		return nullptr;
	}
}