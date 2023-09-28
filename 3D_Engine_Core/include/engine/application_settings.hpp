#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/window/common_types.hpp>

#include <string>
#include <optional>
#include <filesystem>



namespace engine
{
	using std::filesystem::path;
	using window::OpenMode;
	using window::WindowImpl;

	class application_settings : private util::nocopyeble
	{
	public:

		static application_settings& instance() noexcept;

		uint16_t getWidth() const noexcept;
		uint16_t getHeight() const noexcept;
		const std::string& getTitle() const noexcept;
		WindowImpl getWindowImpl() const noexcept;
		OpenMode getOpenMode() const noexcept;
		std::optional<path> getPathToWindowIcon() const noexcept;

		void setWidth(uint16_t _width) noexcept;
		void setHeight(uint16_t _height) noexcept;
		void setTitle(std::string _title) noexcept;
		void setWindowImpl(WindowImpl _window_impl) noexcept;
		void setPathToWindowIcon(path _path_to_window_icon) noexcept;

		void enableFullScreenMode() noexcept;
		void disableFullScreenMode() noexcept;

	protected:

		application_settings() = default;
		virtual ~application_settings() = default;

	protected:

		WindowImpl m_window_impl = WindowImpl::GLFW;

		std::string m_title = "Application";
		std::optional<path> m_path_to_window_icon;
		
		uint16_t m_width = 1024;
		uint16_t m_height = 720;

#ifdef NDEBUG
		OpenMode m_open_mode = OpenMode::FullScreen;
#else
		OpenMode m_open_mode = OpenMode::InWindow;
#endif // NDEBUG

	};
}