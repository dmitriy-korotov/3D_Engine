#include <engine/ecs/components/render_component.hpp>

#include <engine/render/open_gl/shader_program.hpp>



namespace engine::ecs::components
{
	render_component::render_component(shader_program_ptr _shader_program, renderer::DrawingMode _drawing_mode) noexcept
			: m_shader_program(std::move(_shader_program))
			, m_drawing_mode(_drawing_mode)
	{ }
}