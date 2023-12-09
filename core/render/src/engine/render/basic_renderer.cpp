#include <engine/render/basic_renderer.hpp>



namespace engine::render
{
	auto basic_renderer::isInited() const noexcept -> bool
	{
		return m_is_inited;
	}
}