#pragma once

#include <engine/util/nocopyeble.hpp>

#include <string>
#include <optional>
#include <memory>
#include <stdint.h>



namespace engine
{
	namespace window::glfw
	{
		class window;
	}

	class application: private util::nocopyeble
	{
	public:

		using window_ptr = std::shared_ptr<window::glfw::window>;

		application(uint16_t _width, uint16_t _height,
				    const std::string_view& _application_name);
		virtual ~application() = default;

		application(application&&) noexcept = default;
		application& operator=(application&&) noexcept = default;

		void start() noexcept;
		void close() noexcept;

	protected:

		void checkIsNotAlreadyCreated();
		virtual void onUpdate() noexcept;

	protected:

		static bool s_is_created;
		static bool s_is_closed;
		window_ptr m_window_ptr = nullptr;

	};
}