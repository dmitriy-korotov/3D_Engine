#pragma once

#include <engine/ecs/components/basic_component.hpp>
#include <engine/render/common_types.hpp>

#include <memory>



namespace engine::render
{
	class basic_shader_program;
}



namespace engine::ecs::components
{
	using namespace render;

	class render_component: public basic_component
	{
	public:

		static constexpr std::string_view component_name = "render_component";



		using shader_program_ptr = std::unique_ptr<basic_shader_program>;

		render_component(shader_program_ptr _shader_program, DrawingMode _drawing_mode = DrawingMode::Triangle) noexcept;

		const shader_program_ptr& getShaderProgram() const noexcept;
		DrawingMode getDrawingMode() const noexcept;

	private:

		shader_program_ptr m_shader_program = nullptr;
		DrawingMode m_drawing_mode = DrawingMode::Triangle;

	};
}