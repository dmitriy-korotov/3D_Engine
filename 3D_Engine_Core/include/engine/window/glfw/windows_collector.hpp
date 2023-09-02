#pragma once

#include <engine/util/noconstructible.hpp>

#include <vector>
#include <memory>



namespace engine::window::glfw
{
	class window;

	class windows_collector : private util::noconstructible
	{
	public:

		using window_ptr = std::shared_ptr<window>;
		using windows_storage = std::vector<window_ptr>;

		static void addNewWindow(window_ptr _window_ptr);
		static void closeAllWindows() noexcept;

	protected:

		static windows_storage s_windows_storage_;

	};
}