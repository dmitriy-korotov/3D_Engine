#include <engine/render/application_renderer.hpp>

#include <engine/render/basic_renderer.hpp>

#include <cassert>



namespace engine::render
{
	application_renderer& application_renderer::instance() noexcept
	{
		static application_renderer instance;
		return instance;
	}



	void application_renderer::setupRenderer(renderer_ptr _renderer) noexcept
	{
		m_renderer = std::move(_renderer);
	}



	const application_renderer::renderer_ptr& application_renderer::getRenderer() const noexcept
	{
		assert(m_renderer != nullptr);
		return m_renderer;
	}
}