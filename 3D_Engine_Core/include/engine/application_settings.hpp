#pragma once

#include <engine/util/nocopyeble.hpp>

#include <string>



namespace engine
{
	class application_settings : private util::nocopyeble
	{
	public:

		static application_settings& instance() noexcept;

		uint16_t getWidth() const noexcept;
		uint16_t getHeight() const noexcept;
		const std::string& getTitle() const noexcept;

		void setWidth(uint16_t _width) noexcept;
		void setHeight(uint16_t _height) noexcept;
		void setTitle(std::string _title) noexcept;

		void enableFullScreenMode() noexcept;
		void disableFullScreenMode() noexcept;

	protected:

		application_settings() = default;
		virtual ~application_settings() = default;

	protected:

		std::string m_title = "Application";
		
		uint16_t m_width = 1024;
		uint16_t m_height = 720;

#ifdef NDEBUG
		bool m_is_full_screen_mode = true;
#else
		bool m_is_full_screen_mode = false;
#endif // NDEBUG

	};
}