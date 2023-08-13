#pragma once

#include <engine/error.hpp>

#include <iostream>
#include <optional>



namespace engine
{
	class basic_window
	{
	public:

		basic_window(const std::string_view& _title);
		virtual ~basic_window() = default;

		basic_window(const basic_window&) = delete;
		basic_window(basic_window&&) noexcept = delete;
		basic_window& operator=(const basic_window&) = delete;
		basic_window& operator=(basic_window&&) noexcept = delete;

		std::uint16_t getWidth() const noexcept;
		std::uint16_t getHeight() const noexcept;
		const std::string& getTitle() const noexcept;

		virtual std::optional<error::window_error> create(std::uint16_t _width, std::uint16_t _height) noexcept = 0;
		virtual void shutdown() noexcept = 0;
		virtual void onUpdate() noexcept {};

	public:

		struct WindowData
		{
			std::uint16_t width = 0;
			std::uint16_t height = 0;
			std::string title;
		} m_window_data_;

	};
}