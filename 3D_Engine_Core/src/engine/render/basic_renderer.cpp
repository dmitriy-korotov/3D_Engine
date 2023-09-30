#include <engine/render/basic_renderer.hpp>



namespace engine::render
{
	bool basic_renderer::isInited() const noexcept
	{
		return m_is_inited;
	}
}