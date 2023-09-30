#pragma once

#include <engine/error/application_error.hpp>

#include <engine/util/nocopyeble.hpp>

#include <memory>
#include <optional>
#include <filesystem>



namespace engine::window
{
	class basic_window;
	class basic_window_context;
}



namespace engine
{
	using std::filesystem::path;

	class application: private util::nocopyeble
	{
	public:
		
		using app_error = std::optional<error::application_error>;
		using window_ptr = std::shared_ptr<window::basic_window>;
		using window_context_ptr = std::shared_ptr<window::basic_window_context>;

		static application& instance() noexcept;

		void setConfig(const path& _path_to_config_file) noexcept;

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

	private:

		window_context_ptr m_window_context = nullptr;

	protected:

		bool m_is_closed = true;
		std::optional<path> m_path_to_config;

		window_ptr m_window_ptr = nullptr;

	};
}