#pragma once

#include <engine/util/nocopyeble.hpp>
#include <engine/util/nomoveble.hpp>

#include <engine/error/window_error.hpp>

#include <string>
#include <optional>
#include <array>



namespace engine
{

	class basic_window: private util::nocopyeble, private util::nomoveble
	{
	public:

		using bg_color = std::array<float, 4>;

		basic_window(const std::string_view& _title);
		virtual ~basic_window() = default;

		uint16_t getWidth() const noexcept;
		uint16_t getHeight() const noexcept;
		const std::string& getTitle() const noexcept;
		const bg_color& getBackgroundColor() const noexcept;

		void setBackgroundColor(float _red, float _green, float _blue, float _alpha) noexcept;

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

		bg_color m_bg_color_ = { 0.f, 0.f, 0.f, 1.f };
	};
}