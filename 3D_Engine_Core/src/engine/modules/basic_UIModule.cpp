#include <engine/modules/basic_UIModule.hpp>

#include <engine/logging/log.hpp>



namespace engine::modules
{
	void basic_UIModule::setWindowImpl(WindowImpl _window_impl) noexcept
	{
		m_window_impl = _window_impl;
	}



	void basic_UIModule::setRendererImpl(RendererImpl _render_impl) noexcept
	{
		m_render_impl = _render_impl;
	}



	WindowImpl basic_UIModule::getWindowImpl() const noexcept
	{
		return m_window_impl;
	}



	RendererImpl basic_UIModule::getRendererImpl() const noexcept
	{
		return m_render_impl;
	}



	void basic_UIModule::createDockSpace() const noexcept
	{
		LOG_WARN("[Basic UIModule WARN] Method 'createDockSpace' is not implemented.");
	}
}