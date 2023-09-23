#include <engine/application_settings.hpp>



namespace engine
{
	application_settings& application_settings::instance() noexcept
	{
		static application_settings app_settings;
		return app_settings;
	}



	uint16_t application_settings::getWidth() const noexcept
	{
		return m_width;
	}



	uint16_t application_settings::getHeight() const noexcept
	{
		return m_height;
	}



	const std::string& application_settings::getTitle() const noexcept
	{
		return m_title;
	}



	void application_settings::setWidth(uint16_t _width) noexcept
	{
		m_width = _width;
	}



	void application_settings::setHeight(uint16_t _height) noexcept
	{
		m_height = _height;
	}



	void application_settings::setTitle(std::string _title) noexcept
	{
		m_title = std::move(_title);
	}



	void application_settings::enableFullScreenMode() noexcept
	{
		m_open_mode = OpenMode::FullScreen;
	}



	void application_settings::disableFullScreenMode() noexcept
	{
		m_open_mode = OpenMode::InWindow;
	}
}