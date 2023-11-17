#include <engine/ecs/components/render/renderable.hpp>

#include <engine/logging/log.hpp>

#include <engine/Engine.hpp>

#include <engine/resource_manager.hpp>

#include <engine/render/basic_shader_program.hpp>

#include <cassert>



namespace engine::ecs::components
{
	renderable::renderable(std::string_view _shader_program_name, DrawingMode _drawing_mode) noexcept
			: m_shader_program_name(_shader_program_name)
			, m_drawing_mode(_drawing_mode)
	{
		setShaderProgram(_shader_program_name);
	}



	bool renderable::setShaderProgram(std::string_view _shader_program_name) noexcept
	{
		m_shader_program_name = _shader_program_name;


		auto shader_program = GetResourceManager().getShaderProgram(m_shader_program_name);
		if (shader_program == nullptr)
		{
			LOG_ERROR("[Renderable component ERROR] Can't find shader program with this name: {0}", m_shader_program_name);
			disable();
			return false;
		}

		m_shader_program = std::move(shader_program);

		enable();

		return true;
	}



	const renderable::shader_program_ptr_t& renderable::getShaderProgram() const noexcept
	{
		assert(m_shader_program != nullptr);
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

		static int current_version = static_cast<int>(m_drawing_mode);
		if (UI_module->putRadioButton("Point", current_version, 0))
		{
			m_drawing_mode = DrawingMode::Point;
			is_clicked = true;
		}
		UI_module->sameLine();
		if (UI_module->putRadioButton("Triangle", current_version, 1))
		{
			m_drawing_mode = DrawingMode::Triangle;
			is_clicked = true;
		}
		UI_module->sameLine();
		if (UI_module->putRadioButton("TrianleStrip", current_version, 2))
		{
			m_drawing_mode = DrawingMode::TriangleStrip;
			is_clicked = true;
		}
		if (UI_module->putRadioButton("Line", current_version, 3))
		{
			m_drawing_mode = DrawingMode::Line;
			is_clicked = true;
		}
		UI_module->sameLine();
		if (UI_module->putRadioButton("LineStrip", current_version, 4))
		{
			m_drawing_mode = DrawingMode::LineStrip;
			is_clicked = true;
		}

		return is_clicked;
	}



	auto renderable::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = basic_component::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["program_name"] = m_shader_program_name;
		serialized_view["drawing_mode"] = static_cast<int>(m_drawing_mode);

		return serialized_view;
	}



	void renderable::deserializeFrom(const serialized_view_t& _serialized_view) noexcept
	{
		basic_component::deserializeFrom(_serialized_view);

		setShaderProgram(_serialized_view.at("program_name"));
		_serialized_view.at("drawing_mode").get_to(m_drawing_mode);
	}
}