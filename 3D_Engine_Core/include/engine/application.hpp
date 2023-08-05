#pragma once

#include <engine/error.hpp>

#include <engine/window/glfw_window.hpp>

#include <iostream>
#include <optional>
#include <memory>



namespace engine
{
	class Application
	{
	public:

		using Window = glfw_window;



		virtual ~Application();

		Application(const Application&) = delete;
		Application(Application&&) noexcept = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) noexcept = delete;

		static Application create(std::uint16_t _width, std::uint16_t _height,
								  const std::string_view& _application_name);

		std::optional<error::app_error> start() noexcept;

	private:

		Application(std::uint16_t _width, std::uint16_t _height,
					const std::string_view& _application_name);

		void init();
		virtual void onUpdate() const noexcept;

	protected:

		static bool m_is_created;

	protected:

		std::unique_ptr<Window> m_window_ptr;

	};
}