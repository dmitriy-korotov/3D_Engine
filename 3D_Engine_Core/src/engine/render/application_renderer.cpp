#include <engine/render/application_renderer.hpp>

#include <engine/render/basic_renderer.hpp>

#include <cassert>



namespace engine::render
{
	auto application_renderer::instance() noexcept -> application_renderer&
	{
		static application_renderer instance;
		return instance;
	}



	auto application_renderer::setupRenderer(renderer_ptr_t _renderer) noexcept -> void
	{
		m_renderer = std::move(_renderer);
	}



	auto application_renderer::getRenderer() const noexcept -> const renderer_ptr_t&
	{
		assert(m_renderer != nullptr);
		return m_renderer;
	}
}