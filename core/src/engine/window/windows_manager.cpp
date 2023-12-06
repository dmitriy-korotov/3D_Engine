#include <engine/window/windows_manager.hpp>

#include <engine/logging/log.hpp>



namespace engine::window
{
	auto windows_manager::instance() noexcept -> windows_manager&
	{
		static windows_manager instance;
		return instance;
	}



	auto windows_manager::getWindow(window_id_t _window_id) const noexcept -> window_ptr_t
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