#pragma once

#include <engine/util/nocopyeble.hpp>
#include <engine/error/error.hpp>

#include <iostream>
#include <optional>
#include <memory>



namespace engine
{
	class window_gui;

	class Application: private util::nocopyeble
	{
	public:

		using window_ptr = std::shared_ptr<window_gui>;



		virtual ~Application();

		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) noexcept = delete;

		static Application create(std::uint16_t _width, std::uint16_t _height,
								  const std::string_view& _application_name);

		std::optional<error::app_error> start() noexcept;

	private:

		Application(std::uint16_t _width, std::uint16_t _height,
					const std::string_view& _application_name);

		virtual void onUpdate() const noexcept;

	protected:

		bool m_is_closed = false;
		window_ptr m_window_ptr = nullptr;

	};
}