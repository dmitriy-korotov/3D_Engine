#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/window/window.hpp>
#include <engine/window/fwd/basic_window.hpp>

#include <unordered_map>
#include <memory>



namespace engine::window
{
	class windows_collector: private util::nocopyeble
	{
	public:

		using window_ptr_t = std::shared_ptr<basic_window>;
		using windows_storage_t = std::unordered_map<window_id_t, window_ptr_t>;

		void addNewWindow(window_id_t _window_id, window_ptr_t _window);
		bool removeWindow(window_id_t _window_id) noexcept;
		void closeAllWindows() noexcept;

		size_t getWindowsCount() noexcept;

	protected:

		windows_collector() = default;
		virtual ~windows_collector() = default;

	protected:

		windows_storage_t m_windows_storage;

	};
}