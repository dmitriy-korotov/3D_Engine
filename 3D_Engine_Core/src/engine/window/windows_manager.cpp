#include <engine/window/windows_manager.hpp>

#include <engine/logging/log.hpp>



namespace engine::window
{
	windows_manager& windows_manager::instance() noexcept
	{
		static windows_manager instance;
		return instance;
	}



	windows_manager::window_ptr windows_manager::getWindow(window_id_t _window_id) const noexcept
	{
		auto window_iter = m_windows_storage.find(_window_id);
		if (window_iter == m_windows_storage.end())
		{
			LOG_ERROR("[Windows manager ERROR] Can't find window (window_id: {0})", _window_id);
			return nullptr;
		}
		return window_iter->second;
	}
}