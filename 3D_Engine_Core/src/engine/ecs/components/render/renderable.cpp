#include <engine/ecs/components/render/renderable.hpp>

#include <engine/Engine.hpp>

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



	bool renderable::putOnUI() noexcept
	{
		bool is_clicked = false;

		const auto& UI_module = Engine::getApplicationUIModule();

		static int current_version = 3;
		if (UI_module->putRadioButton("Line", current_version, 0))
		{
			m_drawing_mode = DrawingMode::Line;
			is_clicked = true;
		}
		UI_module->sameLine();
		if (UI_module->putRadioButton("LineStrip", current_version, 1))
		{
			m_drawing_mode = DrawingMode::LineStrip;
			is_clicked = true;
		}
		UI_module->sameLine();
		if (UI_module->putRadioButton("Trianle", current_version, 3))
		{
			m_drawing_mode = DrawingMode::Triangle;
			is_clicked = true;
		}
		if (UI_module->putRadioButton("TriangleStrip", current_version, 4))
		{
			m_drawing_mode = DrawingMode::TriangleStrip;
			is_clicked = true;
		}
		UI_module->sameLine();
		if (UI_module->putRadioButton("Point", current_version, 5))
		{
			m_drawing_mode = DrawingMode::Point;
			is_clicked = true;
		}

		return is_clicked;
	}
}