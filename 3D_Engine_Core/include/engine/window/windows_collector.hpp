#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/window/common_types.hpp>

#include <unordered_map>
#include <memory>



namespace engine::window
{
	class basic_window;

	class windows_collector : private util::nocopyeble
	{
	public:

		using window_ptr = std::shared_ptr<basic_window>;
		using windows_storage = std::unordered_map<window_id_t, window_ptr>;

		void addNewWindow(window_id_t _window_id, window_ptr _window);
		void removeWindow(window_id_t _window_id) noexcept;
		void closeAllWindows() noexcept;

		size_t getWindowsCount() noexcept;

	protected:

		windows_collector() = default;
		virtual ~windows_collector() = default;

	protected:

		windows_storage m_windows_storage;

	};
}