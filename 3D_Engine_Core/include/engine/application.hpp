#pragma once

#include <engine/error.hpp>

#include <iostream>
#include <optional>



namespace engine
{
	class Application
	{
	public:

		virtual ~Application() = default;

		Application(const Application&) = delete;
		Application(Application&&) noexcept = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) noexcept = delete;

		static Application create();

		std::optional<error::app_error> start(std::uint16_t _width, std::uint16_t _height,
											  const std::string_view& _application_name) noexcept;

		virtual void onUpdate() const noexcept;

	private:

		Application() = default;

	private:

		static bool m_is_created;

	};
}