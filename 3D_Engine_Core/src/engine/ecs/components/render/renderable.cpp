#include <engine/ecs/components/render/renderable.hpp>

#include <engine/render/basic_shader_program.hpp>



namespace engine::ecs::components
{
	renderable::renderable(shader_program_ptr _shader_program, DrawingMode _drawing_mode) noexcept
			: m_shader_program(std::move(_shader_program))
			, m_drawing_mode(_drawing_mode)
	{ }



	void renderable::setShaderProgram(shader_program_ptr _shader_program) noexcept
	{
		m_shader_program = std::move(_shader_program);
	}



	const renderable::shader_program_ptr& renderable::getShaderProgram() const noexcept
	{
		return m_shader_program;
	}



	void renderable::setDrawingMode(DrawingMode _drawing_mode) noexcept
	{
		m_drawing_mode = _drawing_mode;
	}



	DrawingMode renderable::getDrawingMode() const noexcept
	{
		return m_drawing_mode;
	}
}