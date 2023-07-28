#pragma once
#include <iostream>



namespace engine
{
	class Application
	{
	public:

		virtual ~Application();

		Application(const Application&) = delete;
		Application(Application&&) noexcept = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) noexcept = delete;

		

	private:

		Application(std::uint16_t _width, std::uint16_t _height, const std::string_view& _application_name) noexcept;

	private:

		bool is_created = false;

	};
}