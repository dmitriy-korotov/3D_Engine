#include <engine/ecs/components/render/render_component.hpp>

#include <engine/render/basic_shader_program.hpp>



namespace engine::ecs::components
{
	render_component::render_component(shader_program_ptr _shader_program, DrawingMode _drawing_mode) noexcept
			: m_shader_program(std::move(_shader_program))
			, m_drawing_mode(_drawing_mode)
	{ }



	const render_component::shader_program_ptr& render_component::getShaderProgram() const noexcept
	{
		return m_shader_program;
	}



	DrawingMode render_component::getDrawingMode() const noexcept
	{
		return m_drawing_mode;
	}
}