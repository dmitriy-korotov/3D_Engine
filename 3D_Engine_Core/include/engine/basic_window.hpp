#pragma once

#include <engine/error.hpp>

#include <iostream>
#include <optional>



namespace engine
{
	class basic_window
	{
	public:

		basic_window(std::uint16_t _width, std::uint16_t _height,
					 const std::string_view& _title);
		virtual ~basic_window();

		basic_window(const basic_window&) = delete;
		basic_window(basic_window&&) noexcept = delete;
		basic_window& operator=(const basic_window&) = delete;
		basic_window& operator=(basic_window&&) noexcept = delete;

		virtual std::uint16_t getWidth() const noexcept = 0;
		virtual std::uint16_t getHeight() const noexcept = 0;

	private:

		virtual std::optional<error::window_error> init() noexcept = 0;
		virtual void shutdown() noexcept = 0;

		
	private:

		std::uint16_t m_width = 0;
		std::uint16_t m_height = 0;
		std::string m_title;
	
	};
}