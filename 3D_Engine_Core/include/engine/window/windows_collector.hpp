#pragma once

#include <vector>
#include <memory>



namespace engine
{
	class basic_window;

	class windows_collector
	{
	public:

		using window_ptr = std::shared_ptr<basic_window>;
		using windows_storage = std::vector<window_ptr>;

		windows_collector() = delete;

		static void addNewWindow(window_ptr _window_ptr);
		static void closeAllWindows() noexcept;

	protected:

		static windows_storage s_windows_storage_;

	};
}