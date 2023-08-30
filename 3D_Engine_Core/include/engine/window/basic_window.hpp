#pragma once

#include <engine/util/nocopyeble.hpp>
#include <engine/error.hpp>

#include <iostream>
#include <optional>



namespace engine
{
	class basic_window: private util::nocopyeble
	{
	public:

		basic_window(const std::string_view& _title);
		virtual ~basic_window() = default;

		basic_window(basic_window&&) noexcept = delete;
		basic_window& operator=(basic_window&&) noexcept = delete;

		uint16_t getWidth() const noexcept;
		uint16_t getHeight() const noexcept;
		const std::string& getTitle() const noexcept;

		virtual std::optional<error::window_error> create(uint16_t _width, uint16_t _height) noexcept = 0;
		virtual void shutdown() noexcept = 0;
		virtual void onUpdate() noexcept {}

	protected:

		struct window_data
		{
			uint16_t width = 0;
			uint16_t height = 0;
			std::string title;
		} m_window_data_;

	};
}