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



	WindowImpl application_settings::getWindowImpl() const noexcept
	{
		return m_window_impl;
	}



	RendererImpl application_settings::getRendererImpl() const noexcept
	{
		return m_renderer_impl;
	}



	UIModuleImpl application_settings::getUIModuleImpl() const noexcept
	{
		return m_UI_modele_impl;
	}



	OpenMode application_settings::getOpenMode() const noexcept
	{
		return m_open_mode;
	}



	std::optional<path> application_settings::getPathToWindowIcon() const noexcept
	{
		return m_path_to_window_icon;
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



	void application_settings::setOpenMode(OpenMode _open_mode) noexcept
	{
		m_open_mode = _open_mode;
	}



	void application_settings::setWindowImpl(WindowImpl _window_impl) noexcept
	{
		m_window_impl = _window_impl;
	}



	void application_settings::setRendererImpl(RendererImpl _renderer_impl) noexcept
	{
		m_renderer_impl = _renderer_impl;
	}



	void application_settings::setUIModuleImpl(UIModuleImpl _UI_module_impl) noexcept
	{
		m_UI_modele_impl = _UI_module_impl;
	}



	void application_settings::setPathToWindowIcon(path _path_to_window_icon) noexcept
	{
		m_path_to_window_icon = std::move(_path_to_window_icon);
	}
}