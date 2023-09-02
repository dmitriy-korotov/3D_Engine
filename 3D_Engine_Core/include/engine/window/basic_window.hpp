#pragma once

#include <engine/util/nocopyeble.hpp>
#include <engine/util/nomoveble.hpp>
#include <engine/error/error.hpp>

#include <engine/window/events_data.hpp>

#include <string>
#include <optional>
#include <array>



namespace engine
{
	class windows_manger;

	class basic_window: private util::nocopyeble, private util::nomoveble
	{
	public:

		friend windows_manager;

		using bg_color = std::array<float, 4>;

		basic_window(const std::string_view& _title);
		virtual ~basic_window() = default;

		uint16_t getWidth() const noexcept;
		uint16_t getHeight() const noexcept;
		const std::string& getTitle() const noexcept;

		void setBackgroundColor(uint16_t _red, uint16_t _green, uint16_t _blue, float _alpha) noexcept;

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

		window::CallBackStorage m_window_call_backs_;
		bg_color m_bg_color_ = { 0.f, 0.f, 0.f, 0.f };
	};
}