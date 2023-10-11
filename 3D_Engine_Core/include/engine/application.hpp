#pragma once

#include <engine/error/application_error.hpp>

#include <engine/util/nocopyeble.hpp>

#include <engine/window/window_fwd.hpp>

#include <memory>
#include <optional>
#include <filesystem>



namespace engine
{
	using std::filesystem::path;

	class application: private util::nocopyeble
	{
	public:
		
		using app_error = std::optional<error::application_error>;

		static application& instance() noexcept;

		void setConfig(const path& _path_to_config_file) noexcept;
		const std::optional<path>& getPathToConfig() const noexcept;

		app_error start() noexcept;
		void close() noexcept;

		bool isClosed() const noexcept;

	protected:

		application() = default;
		virtual ~application() = default;

		virtual void onStart() noexcept;
		virtual app_error loadConfig() noexcept;
		virtual void onUpdate() noexcept;
		virtual void onDrawUI() noexcept;
		virtual void onClose() noexcept;

		virtual void onWindowResize() noexcept;
		virtual void onWindowClose() noexcept;
		virtual void onWindowMove() noexcept;
		virtual void onMouseMove() noexcept;
		virtual void onMouseInput() noexcept;
		virtual void onKeyboardInput() noexcept;

	private:

		using window_ptr = std::shared_ptr<window::basic_window>;
		using window_context_ptr = std::shared_ptr<window::basic_window_context>;

		app_error createWindow() noexcept;
		app_error setupRenderer() noexcept;
		void setWindowEventHandlers() noexcept;

	private:

		bool m_is_closed = true;

		window_context_ptr m_window_context = nullptr;
		window_ptr m_window_ptr = nullptr;

		std::optional<path> m_path_to_config;

	};
}