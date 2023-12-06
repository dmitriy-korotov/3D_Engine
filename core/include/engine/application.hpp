#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/error/application_error.hpp>
#include <engine/application_settings.hpp>

#include <engine/window/fwd/basic_window.hpp>
#include <engine/window/fwd/basic_window_context.hpp>

#include <memory>
#include <optional>
#include <filesystem>



namespace engine
{
	using std::filesystem::path;

	class application: private util::nocopyeble
	{
	public:
		
		using app_error_t = std::optional<error::application_error>;



		static application& instance() noexcept;



		void setConfig(const path& _path_to_config_file) noexcept;
		const std::optional<path>& getPathToConfig() const noexcept;

		app_error_t start() noexcept;
		void close() noexcept;

		bool isClosed() const noexcept;

		application_settings& getSettings() noexcept;

	protected:

		application() = default;
		virtual ~application() = default;

		virtual app_error_t loadConfig() noexcept;

		virtual void onStart() noexcept;
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

		using window_ptr_t = window::window_sptr_t;
		using window_context_ptr_t = std::shared_ptr<window::basic_window_context>;

		app_error_t createWindow() noexcept;
		app_error_t setupRenderer() noexcept;
		app_error_t setupUIModule() noexcept;
		void setWindowEventHandlers() noexcept;

	private:

		bool m_is_closed = true;

		window_context_ptr_t m_window_context = nullptr;
		window_ptr_t m_window_ptr = nullptr;

		std::optional<path> m_path_to_config;

	};
}