#pragma once

#include <engine/util/noconstructible.hpp>

#include <unordered_set>
#include <memory>



struct GLFWwindow;

namespace engine::window::glfw
{
	class window;

	class windows_collector : private util::noconstructible
	{
	public:

		using window_ptr = std::shared_ptr<window>;
		using windows_storage = std::unordered_set<window_ptr>;

		static void addNewWindow(window_ptr _window_ptr);
		static void removeWindow(const window_ptr& _window_ptr) noexcept;
		static void removeWindow(GLFWwindow* _window_ptr) noexcept;
		static void closeAllWindows() noexcept;

		static size_t getWindowsCount() noexcept;

	protected:

		static window_ptr getWindowFromRawPtr(GLFWwindow* _window_raw_ptr) noexcept;

	protected:

		static windows_storage s_windows_storage_;

	};
}