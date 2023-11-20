#include <engine/window/windows_collector.hpp>

#include <engine/window/basic_window.hpp>

#include <algorithm>



namespace engine::window
{
	auto windows_collector::addNewWindow(window_id_t _window_id, window_ptr_t _window_ptr) -> void
	{
		m_windows_storage.emplace(_window_id, std::move(_window_ptr));
	}



	auto windows_collector::removeWindow(window_id_t _window_id) noexcept -> bool
	{
		if (!m_windows_storage.empty())
			return m_windows_storage.erase(_window_id);
		return false;
	}



	auto windows_collector::getWindowsCount() noexcept -> size_t
	{
		return m_windows_storage.size();
	}



	auto windows_collector::closeAllWindows() noexcept -> void
	{
		std::for_each(m_windows_storage.begin(), m_windows_storage.end(),
			[](auto& _window_ptr) -> void
			{
				_window_ptr.second->shutdown();
			});
		m_windows_storage.clear();
	}
}