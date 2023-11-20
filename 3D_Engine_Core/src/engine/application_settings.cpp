#include <engine/application_settings.hpp>



namespace engine
{
	auto application_settings::instance() noexcept -> application_settings&
	{
		static application_settings app_settings;
		return app_settings;
	}



	auto application_settings::getWidth() const noexcept -> uint16_t
	{
		return m_width;
	}



	auto application_settings::getHeight() const noexcept -> uint16_t
	{
		return m_height;
	}



	auto application_settings::getTitle() const noexcept -> const std::string&
	{
		return m_title;
	}



	auto application_settings::getWindowImpl() const noexcept -> WindowImpl
	{
		return m_window_impl;
	}



	auto application_settings::getRendererImpl() const noexcept -> RendererImpl
	{
		return m_renderer_impl;
	}



	auto application_settings::getUIModuleImpl() const noexcept -> UIModuleImpl
	{
		return m_UI_modele_impl;
	}



	auto application_settings::getOpenMode() const noexcept -> OpenMode
	{
		return m_open_mode;
	}



	auto application_settings::getPathToWindowIcon() const noexcept -> const std::optional<path>&
	{
		return m_path_to_window_icon;
	}



	auto application_settings::setWidth(uint16_t _width) noexcept -> void
	{
		m_width = _width;
	}



	auto application_settings::setHeight(uint16_t _height) noexcept -> void
	{
		m_height = _height;
	}



	auto application_settings::setTitle(std::string _title) noexcept -> void
	{
		m_title = std::move(_title);
	}



	auto application_settings::setOpenMode(OpenMode _open_mode) noexcept -> void
	{
		m_open_mode = _open_mode;
	}



	auto application_settings::setWindowImpl(WindowImpl _window_impl) noexcept -> void
	{
		m_window_impl = _window_impl;
	}



	auto application_settings::setRendererImpl(RendererImpl _renderer_impl) noexcept -> void
	{
		m_renderer_impl = _renderer_impl;
	}



	auto application_settings::setUIModuleImpl(UIModuleImpl _UI_module_impl) noexcept -> void
	{
		m_UI_modele_impl = _UI_module_impl;
	}



	auto application_settings::setPathToWindowIcon(path _path_to_window_icon) noexcept -> void
	{
		m_path_to_window_icon = std::move(_path_to_window_icon);
	}
}