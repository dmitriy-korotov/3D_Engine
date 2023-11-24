#include <engine/modules/ui/basic_UIModule.hpp>

#include <engine/logging/log.hpp>



namespace engine::modules::ui
{
	auto basic_UIModule::setWindowImpl(WindowImpl _window_impl) noexcept -> void
	{
		m_window_impl = _window_impl;
	}



	auto basic_UIModule::setRendererImpl(RendererImpl _render_impl) noexcept -> void
	{
		m_render_impl = _render_impl;
	}



	auto basic_UIModule::isInitialized() const noexcept -> bool
	{
		return m_is_inited;
	}



	auto basic_UIModule::getWindowImpl() const noexcept -> WindowImpl
	{
		return m_window_impl;
	}



	auto basic_UIModule::getRendererImpl() const noexcept -> RendererImpl
	{
		return m_render_impl;
	}
}