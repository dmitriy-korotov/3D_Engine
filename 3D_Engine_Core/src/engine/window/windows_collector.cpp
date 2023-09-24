#include <engine/window/windows_collector.hpp>

#include <engine/window/basic_window.hpp>

#include <algorithm>



namespace engine::window
{
	void windows_collector::addNewWindow(window_id_t _window_id, window_ptr _window_ptr)
	{
		m_windows_storage.emplace(_window_id, std::move(_window_ptr));
	}



	void windows_collector::removeWindow(window_id_t _window_id) noexcept
	{
		if (!m_windows_storage.empty())
		{
			m_windows_storage.erase(_window_id);
		}
	}



	size_t windows_collector::getWindowsCount() noexcept
	{
		return m_windows_storage.size();
	}



	void windows_collector::closeAllWindows() noexcept
	{
		std::for_each(m_windows_storage.begin(), m_windows_storage.end(),
			[](auto& _window_ptr) -> void
			{
				_window_ptr.second->shutdown();
			});
		m_windows_storage.clear();
	}
}